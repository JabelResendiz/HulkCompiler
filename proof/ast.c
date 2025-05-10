
// ast.c

#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

ASTNode *create_num_node(int value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_NUM;
    node->value = value;
    node->left = node->right = node->condition = node->else_branch = NULL;
    return node;
}

ASTNode *create_op_node(ASTNodeType type,
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

ASTNode *create_print_node(ASTNode *expr)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->left = expr;
    node->right = NULL;
    node->condition = NULL;
    node->else_branch = NULL;
}
ASTNode *create_if_node(ASTNode *condition,
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

void free_ast(ASTNode *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

// void print_ast(ASTNode *node)
// {
//     if (!node)
//         return;
//     if (node->type == AST_NUM)
//     {
//         printf("%d", node->value);
//     }
//     else
//     {
//         printf("(");
//         print_ast(node->left);
//         switch (node->type)
//         {
//         case AST_ADD:
//             printf(" + ");
//             break;
//         case AST_SUB:
//             printf(" - ");
//             break;
//         case AST_MUL:
//             printf(" * ");
//             break;
//         case AST_DIV:
//             printf(" / ");
//             break;
        
//         case 

//         default:
//             break;
//         }

//         print_ast(node->right);
//         printf(")");
//     }
// }



// void print_ast(ASTNode* node) {
//     if (!node) return;

//     switch (node->type) {
//         case AST_NUM:
//             printf("%d", node->value); break;

//         case AST_ADD: case AST_SUB: case AST_MUL: case AST_DIV:
//             printf("(");
//             print_ast(node->left);
//             switch (node->type) {
//                 case AST_ADD: printf(" + "); break;
//                 case AST_SUB: printf(" - "); break;
//                 case AST_MUL: printf(" * "); break;
//                 case AST_DIV: printf(" / "); break;
//                 default: break;
//             }
//             print_ast(node->right);
//             printf(")");
//             break;

//         case AST_PRINT:
//             printf("print ");
//             print_ast(node->left);
//             printf(";");
//             break;

//         case AST_IF:
//             printf("if (");
//             print_ast(node->condition);
//             printf(") \n");
//             print_ast(node->left);
//             printf(" else ");
//             print_ast(node->else_branch);
//             break;

//         case AST_SEQ:
//             print_ast(node->left);
//             printf("\n");
//             print_ast(node->right);
//             break;
//     }
// }





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
    }
}
