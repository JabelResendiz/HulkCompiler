#ifndef AST_H
#define AST_H

#include "ast_types.h"
#include "../../type/type.h"
#include "../../scope/scope.h"

extern int line_num;

typedef struct ASTNode {
    int line;
    int is_param;
    int checked;
    NodeType type;
    Type* return_type;
    Type* dynamic_type;
    char* static_type;
    Scope* scope;
    Context* context;
    NodeList* derivations;
    char* name_method_base ;
    union {
        double number_value;
        char* string_value;
        char* variable_name;
        struct {
            Operator op;
            char* op_name;
            struct ASTNode *left;
            struct ASTNode *right;
        } op_node;
        struct {
            struct ASTNode** statements;
            int count;
        } program_node;
        struct {
            char* name;
            struct ASTNode** args;
            int arg_count;
            struct ASTNode *body;
            int flag_overriden;
        } func_node;
        struct {
            struct ASTNode *cond;
            struct ASTNode *body_true;
            struct ASTNode *body_false;
            int stm;
        } cond_node;
        struct {
            char* name;
            char* parent_name;
            struct ASTNode** p_args;
            int p_arg_count;
            struct ASTNode** args;
            int arg_count;
            struct ASTNode** definitions;
            int def_count;
            struct ASTNode* parent_instance;
            int id;
            int p_constructor;
        } type_node;
        struct {
            char* type_name;
            Type* type;
            struct ASTNode* exp;
        } cast_test;

        struct
        {
            Type* current_class_type;
            char* original_method_name;
            char* current_method;

        }base_method;

    } data;
} ASTNode;


#endif