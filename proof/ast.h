// ast.h

#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUM,
    AST_ADD, AST_SUB, AST_MUL, AST_DIV,
    AST_GT, AST_LT, AST_EQ, AST_GE, AST_LE,
    AST_PRINT,
    AST_IF,
    AST_SEQ
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    int value; // solo para AST_NUM
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* condition;
    struct ASTNode* else_branch;
} ASTNode;

ASTNode* create_num_node(int value);
ASTNode* create_op_node(ASTNodeType type, ASTNode* left, ASTNode* right);
ASTNode* create_print_node(ASTNode* expr);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* create_seq_node(ASTNode* first,ASTNode* second);

void free_ast(ASTNode* node);
void print_ast(ASTNode* node, int indent); // Para depuración

#endif
