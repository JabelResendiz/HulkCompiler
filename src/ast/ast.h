// ast.h

#ifndef AST_H
#define AST_H

#include "type.h"
#include "../scope/scope.h"

extern int line_num;

typedef enum {
    AST_NUM,
    AST_VAR,
    AST_STRING,
    AST_BOOLEAN,
    AST_BINARY_OP,
    AST_IF,
    AST_ASSIGNMENT,
    AST_PROGRAM,
    AST_BLOCK,
    AST_LET,
    AST_CALL_FUNC
} ASTNodeType;

typedef struct  ASTNode ASTNode;

typedef struct ASTNode
{
    int line;                       // Linea del codigo fuente
    int checked;
    ASTNodeType type;               // Tipo del nodo
    TypeValue* computed_type;       // Tipo del valor del nodo
    Scope* scope;

    union 
    {
        double number_value;
        char* string_value;
        char* var_name;

        // Operaciones Binarias
        // Asignacion de Variables
        struct 
        {
            Operator op;
            char* name_op;
            ASTNode* left;
            ASTNode* right;
        }binary_op;

        // lista de sentencias

        struct 
        {
            ASTNode** statements;
            int count;
        }program;
        
        // IF_ElSE

        struct 
        {
            ASTNode* cond;
            ASTNode* body;
            ASTNode* else_branch;
            
        }conditional;
        
        // LET_IN

        struct {
            char* name;
            struct ASTNode** args;
            int arg_count;
            struct ASTNode *body;
        } func_node;
        

    }data;

}ASTNode;





ASTNode* create_program_node(ASTNode** statements, int count,ASTNodeType type);
ASTNode* create_num_node(double value);
ASTNode* create_var_node(char* name, char* type);
ASTNode* create_string_node(char* value);
ASTNode* create_boolean_node(char* value);

ASTNode* create_binary_op_node(Operator op, 
                               char* op_name, 
                               ASTNode* left, 
                               ASTNode* right, 
                               TypeValue* return_type);

ASTNode* create_let_in_node(ASTNode** bindings,
                            int dec_count,
                            ASTNode* body);

ASTNode* create_assignment_node(char* name,
                                ASTNode*value,
                                char* type_name,
                                ASTNodeType type);

                
ASTNode* create_conditional_node(ASTNode* cond,
                                 ASTNode* body,
                                 ASTNode* else_branch);

ASTNode*  create_call_function_node(char* name, ASTNode** args, int arg_count);

void print_ast(ASTNode* node, int indent);


void free_ast(ASTNode* node);

#endif
