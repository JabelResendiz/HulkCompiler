// eval.c

#include <stdio.h>
#include <stdlib.h>
#include "eval.h"

ASTNode *eval(ASTNode *node, Env *env)
{
    if (!node)
        return NULL;

    switch (node->type)
    {
    case AST_NUM:
    case AST_STRING:
        retain(node);
        return node;

    case AST_VAR:
    {
        ASTNode *val = env_lookup(env, node->var_name);

        if (!val)
        {
            fprintf(stderr, " Undefined variable: %s\n", node->var_name);
            exit(1);
        }
        retain(val);
        return eval(val, env);
    }

    case AST_ADD:
    {
        ASTNode *left = eval(node->left, env);
        ASTNode *right = eval(node->right, env);
        ASTNode *result = create_num_node(left->value + right->value);
        release(left);
        release(right);
        return result;
    }

    case AST_SUB:
    {
        ASTNode *left = eval(node->left, env);
        ASTNode *right = eval(node->right, env);
        ASTNode *result = create_num_node(left->value - right->value);
        release(left);
        release(right);
        return result;
    }

    case AST_MUL:
    {
        ASTNode *left = eval(node->left, env);
        ASTNode *right = eval(node->right, env);
        ASTNode *result = create_num_node(left->value * right->value);
        release(left);
        release(right);
        return result;
    }

    case AST_DIV:
    {
        ASTNode *left = eval(node->left, env);
        ASTNode *right = eval(node->right, env);
        ASTNode *result = create_num_node(left->value / right->value);
        release(left);
        release(right);
        return result;
    }

    case AST_SEQ:
    {
        ASTNode *left = eval(node->left, env);
        release(left);
        ASTNode *right = eval(node->right, env);
        retain(right);
        return right;
    }

    case AST_PRINT:
    {
        ASTNode *val = eval(node->left, env);
        if (val->type == AST_STRING)
            printf("%s\n", val->string_value);
        else if (val->type == AST_NUM)
            printf("%d\n", val->value);
        else
            printf("Unsupported type for print\n");

        retain(val);
        return val;
    }

    case AST_LET:
    {
        Env *new_env = create_env(env);
        VarBinding *b = node->bindings;
        while (b)
        {
            ASTNode *val = eval(b->value, env);
            retain(val);
            env_add(new_env, b->name, val);
            release(val); 
            b = b->next;
        }
        ASTNode *result = eval(node->left, new_env);
        //free_env(new_env);
        return result; 
    }

    default:
        fprintf(stderr, "Unsupported AST node in eval\n");
        exit(1);
        
    }
}