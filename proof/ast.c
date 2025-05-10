

#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

ASTNode *create_num_node(int value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_NUM;
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

ASTNode *create_op_node(ASTNodeType type,
                        ASTNode *left,
                        ASTNode *right)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    node->left= left;
    node->right = right;
    return node;
}

void free_ast(ASTNode* node){
    if(!node) return ;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

void print_ast(ASTNode* node)
{
    if(!node)return;
    if (node->type == AST_NUM)
    {
        printf("%d", node->value);
    }
    else 
    {
        printf("(");
        print_ast(node->left);
        switch (node->type)
        {
        case AST_ADD: printf(" + "); break;
        case AST_SUB: printf(" - "); break;
        case AST_MUL: printf(" * "); break;
        case AST_DIV: printf(" / "); break;
        
        default:
            break;
        }

        print_ast(node->right);
        printf(")");
    }
}