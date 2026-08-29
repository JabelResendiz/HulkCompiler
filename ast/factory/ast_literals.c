// #include "ast_factory.h"
// #include <stdlib.h>
// #include <string.h>


// // method to create number node
// ASTNode *create_number_node(double value)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_NUMBER;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->return_type = &TYPE_NUMBER;
//     node->dynamic_type = &TYPE_NUMBER;
//     node->data.number_value = value;
//     node->derivations = NULL;
//     return node;
// }

// // method to create string node
// ASTNode *create_string_node(char *value)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_STRING;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->return_type = &TYPE_STRING;
//     node->dynamic_type = &TYPE_STRING;
//     node->data.string_value = value;
//     node->derivations = NULL;
//     return node;
// }

// // method to create boolean node
// ASTNode *create_boolean_node(char *value)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->type = NODE_BOOLEAN;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->return_type = &TYPE_BOOLEAN;
//     node->dynamic_type = &TYPE_BOOLEAN;
//     node->data.string_value = value;
//     node->derivations = NULL;
//     return node;
// }

// // method to create variable node
// ASTNode *create_variable_node(char *name, char *type, int is_param)
// {
//     ASTNode *node = malloc(sizeof(ASTNode));
//     node->line = line_num;
//     node->is_param = is_param;
//     node->type = NODE_VARIABLE;
//     node->scope = create_scope(NULL);
//     node->context = create_context(NULL);
//     node->return_type = &TYPE_OBJECT;
//     node->dynamic_type = &TYPE_OBJECT;
//     node->data.variable_name = name;
//     node->derivations = NULL;

//     if (type)
//         node->static_type = type;

//     return node;
// }