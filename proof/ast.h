// ast.h

#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUM,
    AST_VAR,
    AST_STRING,
    AST_ADD, AST_SUB, AST_MUL, AST_DIV, AST_CONCAT,
    AST_GT, AST_LT, AST_EQ, AST_GE, AST_LE,
    AST_PRINT,
    AST_IF,
    AST_SEQ,
    AST_LET,
    AST_BINDING
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    int ref_count; // SE PODRA BORRAR DESPUES
    union {
        int value;
        char* var_name;
        char* string_value;
    };
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* condition;
    struct ASTNode* else_branch;
    struct VarBinding* bindings;
} ASTNode;


typedef struct VarBinding
{
    char* name;
    ASTNode* value;
    struct VarBinding* next;
}VarBinding;

ASTNode* create_num_node(int value);
ASTNode* create_var_node(char* name);
ASTNode* create_string_node(char* value);
ASTNode* create_op_node(ASTNodeType type, ASTNode* left, ASTNode* right);
ASTNode* create_print_node(ASTNode* expr);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* create_seq_node(ASTNode* first,ASTNode* second);


ASTNode* create_let_node(VarBinding* bindings, ASTNode* body);
VarBinding* append_binding_list(VarBinding* list,VarBinding* new_binding);
VarBinding* create_binding(char* name, ASTNode* value);


void free_ast(ASTNode* node);
void free_bindings(VarBinding* bindings);
void print_ast(ASTNode* node, int indent); 


void retain(ASTNode* node);
void release(ASTNode* node);

#endif
