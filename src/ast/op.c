

#include <stdio.h>
#include "ast.h"
#include <stdlib.h>

ASTNode *create_binary_op_node(Operator op,
                               char *name_op,
                               ASTNode *left,
                               ASTNode *right,
                               TypeValue *type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_BINARY_OP;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->computed_type = type;
    node->data.binary_op.name_op = name_op;
    node->data.binary_op.op = op; 
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;

    return node;
}

ASTNode *create_let_in_node(ASTNode **bindings,
                            int dec_count,
                            ASTNode *body)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_LET;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->computed_type = &TYPE_OBJ;
    node->data.func_node.name = "";
    node->data.func_node.args = malloc(sizeof(ASTNode *) * dec_count);

    for (int i = 0; i < dec_count; i++)
    {
        node->data.func_node.args[i] = bindings[i];
    }

    node->data.func_node.arg_count = dec_count;
    node->data.func_node.body = body;
    node->usages = add_usages(body,NULL);
    return node;
}

ASTNode *create_assignment_node(char *name, ASTNode *value, char *type_name, ASTNodeType type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->checked =0;
    node->type = type;
    node->computed_type = &TYPE_VOID;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->data.binary_op.left = create_var_node(name, NULL, 0);
    node->data.binary_op.right = value;
    node->data.binary_op.left->static_type = type_name;
    // agregar los usages nuevos
    node->usages = add_usages(value,NULL);
    return node;
}