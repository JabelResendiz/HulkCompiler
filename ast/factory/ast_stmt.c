// #include "ast_factory.h"

// //ASTNode* create_program_node(ASTNode** statements, int count, NodeType type);
// // ASTNode* create_assignment_node(char* var, ASTNode* value, char* type_name, NodeType type);
// // ASTNode* create_let_in_node(ASTNode** declarations, int dec_count, ASTNode* body);
// // ASTNode* create_conditional_node(ASTNode* condition, ASTNode* body_true, ASTNode* body_false);
// // ASTNode* create_q_conditional_node(ASTNode* exp, ASTNode* body_true, ASTNode* body_false);
// // ASTNode* create_loop_node(ASTNode* condition, ASTNode* body);
// // ASTNode* create_for_loop_node(char* var_name, ASTNode** params, ASTNode* body, int count);

// ASTNode *create_program_node(ASTNode **statements, int count, NodeType type)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = type;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.program_node.statements = malloc(sizeof(ASTNode *) * count);
//     for (int i = 0; i < count; i++)
//     {
//         node->data.program_node.statements[i] = statements[i];
//     }
//     node->data.program_node.count = count;
//     node->derivations = NULL;
//     return node;
// }

// ASTNode *create_assignment_node(char *var, ASTNode *value, char *type_name, NodeType type)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->checked = 0;
//     node->type = type;
//     node->return_type = &TYPE_VOID;
//     node->dynamic_type = &TYPE_VOID;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.op_node.left = create_variable_node(var, NULL, 0);
//     node->data.op_node.left->static_type = type_name;
//     node->data.op_node.right = value;
//     node->derivations = add_node_list(value, NULL);
//     return node;
// }


// // method to create let-in node
// ASTNode *create_let_in_node(ASTNode **declarations, int dec_count, ASTNode *body)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_LET_IN;
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.func_node.name = "";
//     node->data.func_node.args = malloc(sizeof(ASTNode *) * dec_count);
//     for (int i = 0; i < dec_count; i++)
//     {
//         node->data.func_node.args[i] = declarations[i];
//     }
//     node->data.func_node.arg_count = dec_count;
//     node->data.func_node.body = body;
//     node->derivations = add_node_list(body, NULL);
//     return node;
// }



// // method to create conditional (if) node
// ASTNode *create_conditional_node(ASTNode *condition, ASTNode *body_true, ASTNode *body_false)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_CONDITIONAL;
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->derivations = add_node_list(body_true, NULL);
//     node->derivations = add_node_list(body_false, node->derivations);
//     node->data.cond_node.cond = condition;
//     node->data.cond_node.body_true = body_true;
//     node->data.cond_node.body_false = body_false;
//     node->data.cond_node.stm = 1;
//     return node;
// }

// // method to create q-conditional (if?) node
// ASTNode *create_q_conditional_node(ASTNode *exp, ASTNode *body_true, ASTNode *body_false)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_Q_CONDITIONAL;
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->derivations = add_node_list(body_true, NULL);
//     node->derivations = add_node_list(body_false, node->derivations);
//     node->data.cond_node.cond = exp;
//     node->data.cond_node.body_true = body_true;
//     node->data.cond_node.body_false = body_false;
//     node->data.cond_node.stm = 1;
//     return node;
// }

// // method to create loop node (while loop)
// ASTNode *create_loop_node(ASTNode *condition, ASTNode *body)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_LOOP;
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.op_node.left = condition;
//     node->data.op_node.right = body;
//     node->derivations = add_node_list(body, NULL);
//     return node;
// }

// // method to create for loop node
// ASTNode *create_for_loop_node(char *var_name, ASTNode **params, ASTNode *body, int count)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_FOR_LOOP;
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.func_node.name = var_name;
//     node->checked = 0;
//     node->data.func_node.args = malloc(sizeof(ASTNode *) * count);
//     for (int i = 0; i < count; i++)
//     {
//         node->data.func_node.args[i] = params[i];
//     }
//     node->data.func_node.arg_count = count;
//     node->data.func_node.body = body;
//     node->derivations = NULL;
//     return node;
// }