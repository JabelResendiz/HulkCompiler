#include "ast_factory.h"

// method to create binary operation node
ASTNode *create_binary_op_node(Operator op, char *op_name, ASTNode *left, ASTNode *right, Type *return_type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = NODE_BINARY_OP;
    node->scope = create_scope(NULL);
    node->context = create_context(NULL);
    node->return_type = return_type;
    node->dynamic_type = return_type;
    node->data.op_node.op_name = op_name;
    node->data.op_node.op = op;
    node->data.op_node.left = left;
    node->data.op_node.right = right;
    node->derivations = NULL;
    return node;
}

// method to create unary operation node
ASTNode *create_unary_op_node(Operator op, char *op_name, ASTNode *operand, Type *return_type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = NODE_UNARY_OP;
    node->scope = create_scope(NULL);
    node->context = create_context(NULL);
    node->return_type = return_type;
    node->dynamic_type = return_type;
    node->data.op_node.op_name = op_name;
    node->data.op_node.op = op;
    node->data.op_node.left = operand;
    node->data.op_node.right = NULL;
    node->derivations = NULL;
    return node;
}