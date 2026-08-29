// #include "ast_factory.h"

// // ASTNode* create_func_call_node(char* name, ASTNode** args, int arg_count);
// // ASTNode* create_func_dec_node(char* name, ASTNode** args, int arg_count, ASTNode* body, char* ret_type); 
// // ASTNode* create_base_func_node(ASTNode** args, int arg_count);



// // method to create function call node
// ASTNode *create_func_call_node(char *name, ASTNode **args, int arg_count)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_FUNC_CALL;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->data.func_node.name = name;
//     node->checked = 0;
//     node->data.func_node.args = malloc(sizeof(ASTNode *) * arg_count);
//     for (int i = 0; i < arg_count; i++)
//     {
//         node->data.func_node.args[i] = args[i];
//     }
//     node->data.func_node.arg_count = arg_count;
//     node->derivations = NULL;
//     return node;
// }

// // method to create function declaration node
// ASTNode *create_func_dec_node(char *name, ASTNode **args, int arg_count, ASTNode *body, char *ret_type)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_FUNC_DEC;
//     node->return_type = &TYPE_VOID;
//     node->dynamic_type = &TYPE_VOID;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->static_type = ret_type;
//     node->data.func_node.name = name;
//     node->checked = 0;
//     node->data.func_node.args = malloc(sizeof(ASTNode *) * arg_count);
//     for (int i = 0; i < arg_count; i++)
//     {
//         node->data.func_node.args[i] = args[i];
//     }
//     node->data.func_node.arg_count = arg_count;
//     node->data.func_node.body = body;
//     node->derivations = NULL;
//     return node;
// }



// // method to create 'base' function node
// ASTNode *create_base_func_node(ASTNode **args, int arg_count)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_BASE_FUNC;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->checked = 0;
//     node->data.func_node.args = malloc(sizeof(ASTNode *) * arg_count);
//     for (int i = 0; i < arg_count; i++)
//     {
//         node->data.func_node.args[i] = args[i];
//     }
//     node->data.func_node.arg_count = arg_count;
//     node->derivations = NULL;
//     return node;
// }