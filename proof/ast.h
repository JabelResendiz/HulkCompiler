// ast.h

#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUM,
    AST_ADD, AST_SUB, AST_MUL, AST_DIV,
    AST_GT, AST_LT, AST_EQ, AST_GE, AST_LE,
    AST_PRINT,
    AST_IF,
    AST_LET,
    AST_VAR,
    AST_STR,
    AST_CONCAT,
    AST_SEQ
} ASTNodeType;

struct ASTBinding;

typedef struct ASTNode {
    ASTNodeType type;
    int value; // solo para AST_NUM
    char* str; // solo para strings
    char* varname; // solo para variables
    struct ASTNode* left;
    struct ASTNode* right;

    struct ASTNode* condition;
    struct ASTNode* else_branch;

    struct ASTBinding* bindings;
    struct ASTNode* body;
} ASTNode;

typedef struct ASTBinding {
    char* name;
    ASTNode* value;
    struct ASTBinding* next;
}ASTBinding;


// Constructores de nodos
ASTNode* create_num_node(int value);
ASTNode* create_str_node(const char* str);
ASTNode* create_var_node(const char* name, ASTNode* value);

ASTNode* create_op_node(ASTNodeType type, ASTNode* left, ASTNode* right);
ASTNode* create_concat_node(ASTNode* left, ASTNode* right);
ASTNode* create_print_node(ASTNode* expr);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* create_seq_node(ASTNode* first,ASTNode* second);
ASTNode* create_let_node(ASTBinding* bindings,ASTNode* body);

ASTBinding* create_binding(const char* name, ASTNode* value);
ASTBinding* append_binding(ASTBinding* list, ASTBinding* new_binding);

void free_ast(ASTNode* node);
void print_ast(ASTNode* node, int indent); // Para depuración

#endif
