#ifndef ASt_FACTORY_H
#define ASt_FACTORY_H

#include "ast_node.h"
#include "ast_types.h"

/* literals */
ASTNode* create_number_node(double value);
ASTNode* create_string_node(char* value);
ASTNode* create_boolean_node(char* value);
ASTNode* create_variable_node(char* name, char* type, int is_param);

/* expressions */
ASTNode* create_binary_op_node(Operator op, char* op_name, ASTNode* left, ASTNode* right, Type* return_type);
ASTNode* create_unary_op_node(Operator op, char* op_name, ASTNode* operand, Type* return_type);

/* statements */
ASTNode* create_program_node(ASTNode** statements, int count, NodeType type);
ASTNode* create_assignment_node(char* var, ASTNode* value, char* type_name, NodeType type);
ASTNode* create_let_in_node(ASTNode** declarations, int dec_count, ASTNode* body);
ASTNode* create_conditional_node(ASTNode* condition, ASTNode* body_true, ASTNode* body_false);
ASTNode* create_q_conditional_node(ASTNode* exp, ASTNode* body_true, ASTNode* body_false);
ASTNode* create_loop_node(ASTNode* condition, ASTNode* body);
ASTNode* create_for_loop_node(char* var_name, ASTNode** params, ASTNode* body, int count);

/* functions */
ASTNode* create_func_call_node(char* name, ASTNode** args, int arg_count);
ASTNode* create_func_dec_node(char* name, ASTNode** args, int arg_count, ASTNode* body, char* ret_type); 
ASTNode* create_base_func_node(ASTNode** args, int arg_count);


/* types / OOP */
ASTNode* create_attr_getter_node(ASTNode* instance, ASTNode* member);
ASTNode* create_attr_setter_node(ASTNode* instance, ASTNode* member, ASTNode* value);
ASTNode* create_type_dec_node(
    char* name, ASTNode** params, int param_count, char* parent_name,
    ASTNode** p_params, int p_param_count, ASTNode* body_block, int p_constructor
);
ASTNode* create_type_instance_node(char* name, ASTNode** args, int arg_count);
ASTNode* create_test_casting_type_node(ASTNode* exp, char* type_name, int test);


/* debug */
void print_ast(ASTNode* node, int indent);


#endif