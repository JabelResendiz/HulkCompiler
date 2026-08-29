// #include "ast.h"

// // ASTNode* create_type_dec_node(
// //     char* name, ASTNode** params, int param_count, char* parent_name,
// //     ASTNode** p_params, int p_param_count, ASTNode* body_block, int p_constructor
// // );
// // ASTNode* create_type_instance_node(char* name, ASTNode** args, int arg_count);
// // ASTNode* create_test_casting_type_node(ASTNode* exp, char* type_name, int test);



// // method to create type testing node or type downcasting node
// ASTNode *create_test_casting_type_node(ASTNode *exp, char *type_name, int test)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = test ? NODE_TEST_TYPE : NODE_CAST_TYPE;
//     node->return_type = test ? &TYPE_BOOLEAN : &TYPE_OBJECT;
//     node->dynamic_type = test ? &TYPE_BOOLEAN : &TYPE_OBJECT;
//     node->data.cast_test.type_name = type_name;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.cast_test.exp = exp;
//     node->derivations = NULL;
//     return node;
// }

// // method to create type declaration node
// ASTNode *create_type_dec_node(
//     char *name, ASTNode **params, int param_count, char *parent_name,
//     ASTNode **p_params, int p_param_count, ASTNode *body_block, int p_constructor)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_TYPE_DEC;
//     node->return_type = &TYPE_VOID;
//     node->dynamic_type = &TYPE_VOID;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.type_node.name = name;
//     node->data.type_node.parent_name = parent_name;
//     // node->data.type_node.parent = &TYPE_OBJECT;
//     node->data.type_node.p_args = malloc(sizeof(ASTNode *) * p_param_count);
//     for (int i = 0; i < p_param_count; i++)
//     {
//         node->data.type_node.p_args[i] = p_params[i];
//     }
//     node->data.type_node.p_arg_count = p_param_count;
//     node->data.type_node.args = malloc(sizeof(ASTNode *) * param_count);
//     for (int i = 0; i < param_count; i++)
//     {
//         node->data.type_node.args[i] = params[i];
//     }
//     node->data.type_node.arg_count = param_count;

//     int count = body_block->data.program_node.count;
//     node->data.type_node.definitions = malloc(sizeof(ASTNode *) * count);
//     for (int i = 0; i < count; i++)
//     {
//         node->data.type_node.definitions[i] = body_block->data.program_node.statements[i];
//     }
//     node->data.type_node.parent_instance = NULL;
//     node->data.type_node.def_count = count;
//     node->data.type_node.id = 0;
//     node->data.type_node.p_constructor = p_constructor;
//     node->derivations = NULL;

//     return node;
// }

// // method to create type instance node
// ASTNode *create_type_instance_node(char *name, ASTNode **args, int arg_count)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_TYPE_INST;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.type_node.name = name;
//     node->data.type_node.args = malloc(sizeof(ASTNode *) * arg_count);
//     for (int i = 0; i < arg_count; i++)
//     {
//         node->data.type_node.args[i] = args[i];
//     }
//     node->data.type_node.parent_instance = NULL;
//     node->data.type_node.arg_count = arg_count;
//     node->derivations = NULL;

//     return node;
// }
