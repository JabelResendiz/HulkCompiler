// #include "ast_factory.h"



// // method to create type attribute or method getter node
// ASTNode *create_attr_getter_node(ASTNode *instance, ASTNode *member)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_TYPE_GET_ATTR;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.op_node.left = instance;
//     node->data.op_node.right = member;
//     node->derivations = NULL;
//     return node;
// }

// // method to create type attribute setter node
// ASTNode *create_attr_setter_node(ASTNode *instance, ASTNode *member, ASTNode *value)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_TYPE_SET_ATTR;
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->data.cond_node.cond = instance;
//     node->data.cond_node.body_true = member;
//     node->data.cond_node.body_false = value;
//     node->derivations = NULL;
//     return node;
// }
