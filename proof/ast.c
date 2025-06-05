
// ast.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "types.h"
#include "visitor.h"

ASTNode *create_num_node(int value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_NUM;
    node->value = value;
    node->ref_count = 1;
    node->left = node->right = node->condition = node->else_branch = NULL;
    node->bindings = NULL;
    node->accept =  visit_num;
    return node;
}

ASTNode *create_var_node(char *name)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_VAR;
    node->var_name = strdup(name);
    node->ref_count = 1;
    node->left = node->right = node->condition = node->else_branch = NULL;
    node->bindings = NULL;
    node->accept =  visit_var;
    return node;
}

ASTNode *create_string_node(char *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_STRING;
    node->string_value = strdup(value);
    node->ref_count = 1;
    node->left = node->right = node->condition = node->else_branch = NULL;
    node->bindings = NULL;
    node->accept =  visit_string;
    return node;
}

ASTNode *create_op_node(ASTNodeType type,
                        ASTNode *left,
                        ASTNode *right)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->ref_count = 1;
    node->left = left;
    
    node->right = right;

    
    node->condition = node->else_branch = NULL;

    node->bindings = NULL;
    
    // fprintf(stderr,"el tipo es : %s\n",type);

    switch (type)
    {
    case AST_ADD: node->accept = visit_add;break;
    case AST_SUB: node->accept = visit_sub;break;
    case AST_MUL: node->accept = visit_mul;break;
    case AST_DIV: node->accept = visit_div;break;
    case AST_CONCAT: node->accept = visit_concat;break;
    default:  
        fprintf(stderr, "ERROR: Unrecognized ASTNodeType in create_op_node: %d\n", type);
        node->accept = NULL; 
        break;
    }


    return node;
}

ASTNode *create_print_node(ASTNode *expr)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->ref_count = 1;
    node->left = expr;
    node->right = NULL;
    node->condition = NULL;
    node->else_branch = NULL;
    node->bindings = NULL;
    node->accept = visit_print; 
    return node;
}

ASTNode *create_if_node(ASTNode *condition,
                        ASTNode *then_branch,
                        ASTNode *else_branch)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IF;
    node->ref_count = 1;
    node->condition = condition;
    node->left = then_branch;
    node->else_branch = else_branch;
    node->bindings = NULL;
    node->right = NULL;
    node->accept = visit_if;
    return node;
}

ASTNode *create_seq_node(ASTNode *first, ASTNode *second)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_SEQ;
    node->ref_count = 1;
    node->left = first;
    node->right = second;
    node->condition = NULL;
    node->else_branch = NULL;
    node->bindings = NULL;
    node->accept = visit_seq;
    return node;
}

ASTNode *create_let_node(VarBinding *bindings, ASTNode *body)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_LET;
    node->ref_count = 1;
    node->bindings = bindings;
    fprintf(stderr,"el valor es : %d\n ",bindings->value->type);

    node->left = body;
    fprintf(stderr,"el valor es : %d\n ",body->type);

    node->right = node->condition = node->else_branch = NULL;
    node->accept = visit_let;
    return node;
}

// Funciones para VarBindings

VarBinding *create_binding(char *name, ASTNode *value)
{
    VarBinding *binding = malloc(sizeof(VarBinding));
    binding->name = strdup(name);
    binding->value = value;
    binding->next = NULL;
    
    return binding;
}

VarBinding *append_binding_list(VarBinding *list, VarBinding *new_binding)
{
    if (!list)
        return new_binding;

    VarBinding *current = list;

    while (current->next)
        current = current->next;

    current->next = new_binding;

    return list;
}

// void free_ast(ASTNode *node)
// {
//     if (!node)
//         return;

//     if (node->type == AST_LET)
//     {
//         free_bindings(node->bindings);
//         free_ast(node->left);
//     }
//     else
//     {
//         free_ast(node->left);
//         free_ast(node->right);
//         free_ast(node->condition);
//         free_ast(node->else_branch);
//     }
//     free(node);
// }



void free_ast(ASTNode *node)
{
    if (!node)
        return;

    release(node->left);
    release(node->right);
    release(node->condition);
    release(node->else_branch);

    if (node->type == AST_STRING && node->string_value)
    {
        free(node->string_value);
    }

    if (node->type == AST_VAR && node->var_name)
    {
        free(node->var_name);
    }

    if (node->type == AST_LET || node->bindings)
    {
        VarBinding *b = node->bindings;
        while (b)
        {
            VarBinding *next = b->next;
            free(b->name);
            release(b->value);
            free(b);
            b = next;
        }
    }

    free(node);
}


void free_bindings(VarBinding *bindings)
{
    while (bindings)
    {
        VarBinding *next = bindings->next;
        free(bindings->name);
        free_ast(bindings->value);
        free(bindings);
        bindings = next;
    }
}

void print_bindings(VarBinding *bindings, int indent)
{
    VarBinding *copy_bindings = bindings;
    while (copy_bindings)
    {
        for (int i = 0; i < indent; i++)
            printf(" ");
        printf("Binding: %s = \n", copy_bindings->name);
        print_ast(copy_bindings->value, indent + 1);
        copy_bindings = copy_bindings->next;
    }
}

void print_ast(ASTNode *node, int indent)
{
    if (!node)
        return;

    for (int i = 0; i < indent; i++)
        printf("  ");

    switch (node->type)
    {
    case AST_NUM:
        printf("NUM: %d\n", node->value);
        break;

    case AST_VAR:
        printf("Variable: %s\n", node->var_name);
        break;

    case AST_STRING:
        printf("String : %s\n", node->string_value);
        break;

    case AST_ADD:
        printf("ADD\n");
        goto binary;

    case AST_SUB:
        printf("SUB\n");
        goto binary;

    case AST_CONCAT:
        printf("CONCAT\n");
        goto binary;

    case AST_MUL:
        printf("MUL\n");
        goto binary;

    case AST_DIV:
        printf("DIV\n");
        goto binary;

    case AST_GT:
        printf("GT\n");
        goto binary;

    case AST_LT:
        printf("LT\n");
        goto binary;

    case AST_EQ:
        printf("EQ\n");
        goto binary;

    case AST_GE:
        printf("GE\n");
        goto binary;

    case AST_LE:
        printf("LE\n");
        goto binary;

    case AST_PRINT:
        printf("PRINT\n");
        print_ast(node->left, indent + 1);
        break;

    case AST_IF:
        printf("IF\n");
        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Condition:\n");
        print_ast(node->condition, indent + 2);
        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Then:\n");
        print_ast(node->left, indent + 2);
        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Else:\n");
        print_ast(node->else_branch, indent + 2);
        break;

    case AST_SEQ:
        printf("SEQ\n");
        goto binary;

    case AST_LET:
        printf("LET:\n");
        print_bindings(node->bindings, indent + 1);
        for (int i = 0; i < indent; i++)
            printf("  ");
        printf("Body:\n");
        print_ast(node->left, indent + 1);
        break;

    binary:
        print_ast(node->left, indent + 1);
        print_ast(node->right, indent + 1);
        break;

    default:
        printf("Unknown AST node type\n");
    }
}

void retain(ASTNode *node)
{
    if (node)
        node->ref_count++;
}

void release(ASTNode *node)
{
    if (!node)
        return;

    if (node->ref_count <= 0) {
        // Ya fue liberado o es un error
        fprintf(stderr, "Warning: Trying to release an already freed node.\n");
        return;
    }

    node->ref_count--;

    if (node->ref_count == 0)
    {
        free_ast(node);
    }
}