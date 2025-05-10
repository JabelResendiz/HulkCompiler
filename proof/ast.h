#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUM,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    int value; // solo para AST_NUM
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* create_num_node(int value);
ASTNode* create_op_node(ASTNodeType type, ASTNode* left, ASTNode* right);
void free_ast(ASTNode* node);
void print_ast(ASTNode* node); // Para depuración

#endif
