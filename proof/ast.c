
// ast.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

ASTNode* create_num_node(int value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_NUM;
    node->value = value;
    node->left = node->right = node->condition = node->else_branch = NULL;
    return node;
}

ASTNode* create_str_node(const char* str)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_STR;
    node->str = strdup(str);
    node->left = node->right = NULL;
    return node;
}

ASTNode* create_var_node(const char* name, ASTNode* value)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type= AST_VAR;
    node->varname= strdup(name);
    node->right = value;
    node->left = node->condition= node->else_branch = NULL;
    return node;
}

ASTNode* create_concat_node(ASTNode* left, ASTNode* right)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_CONCAT;
    node->left= left;
    node->right= right;
    return node;
}

ASTNode* create_op_node(ASTNodeType type,
                        ASTNode *left,
                        ASTNode *right)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->left = left;
    node->right = right;
    node->condition = node->else_branch = NULL;

    return node;
}

ASTNode* create_print_node(ASTNode *expr)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->left = expr;
    node->right = NULL;
    node->condition = NULL;
    node->else_branch = NULL;
}
ASTNode* create_if_node(ASTNode *condition,
                        ASTNode *then_branch,
                        ASTNode *else_branch)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IF;
    node->condition = condition;
    node->left = then_branch;
    node->else_branch = else_branch;
    return node;
}

ASTNode* create_seq_node(ASTNode* first,ASTNode* second)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_SEQ;
    node->left= first;
    node->right= second;
    return node;
}


ASTNode* create_let_node(ASTBinding* bindings, ASTNode* body)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type= AST_LET;
    node->bindings = bindings;
    node->body= body;
    return node;
}


ASTBinding* create_binding(const char* name, ASTNode* value)
{
    ASTBinding* binding = malloc(sizeof(ASTBinding));
    binding->name= strdup(name);
    binding->value = value;
    binding->next = NULL;
    return binding;
}

ASTBinding*  append_binding(ASTBinding* list, 
                            ASTBinding* new_binding)
{
    if(!list) return new_binding;
    ASTBinding* current = list;
    while (current->next)
        current = current->next;
    current->next = new_binding;
    return list;
}

void free_ast(ASTNode *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->condition);
    free_ast(node->else_branch);

    if (node->type == AST_VAR && node->varname)
        free(node->varname);

    free(node);
}


void print_ast(ASTNode* node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case AST_NUM:
            printf("NUM: %d\n", node->value);
            break;

        case AST_ADD:
            printf("ADD\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;

        case AST_SUB:
            printf("SUB\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;

        case AST_MUL:
            printf("MUL\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;

        case AST_DIV:
            printf("DIV\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        
        case AST_GT:
            printf("GT\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        
        case AST_LT:
            printf("LT\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        
        case AST_EQ:
            printf("EQ\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;

        case AST_GE:
            printf("GE\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;

        case AST_LE:
            printf("LE\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        
        case AST_PRINT:
            printf("PRINT\n");
            print_ast(node->left, indent + 1);
            break;

        case AST_IF:
            printf("IF\n");
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->condition, indent + 2);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Then:\n");
            print_ast(node->left, indent + 2);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Else:\n");
            print_ast(node->else_branch, indent + 2);
            break;

        case AST_SEQ:
            printf("SEQ\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        
        case AST_LET:
            printf("LET \n");
            for (int i=0;i<indent+1;i++) printf(" ");
            printf("Bindings: \n");
            print_ast(node->left,indent+2);
            for (int i=0;i<indent+1;i++) printf(" ");
            printf("IN: \n");
            print_ast(node->right,indent+2);
            break;
        
        case AST_VAR:
            printf("VAR: %s =\n", node->varname? node->varname: "(null)");
            print_ast(node->right, indent + 1);
            break;

        default: break;
    }
}
