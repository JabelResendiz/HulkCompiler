

#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

ASTNode *create_decl_function_node(char *name_func,
                                   ASTNode **args,
                                   int arg_count,
                                   ASTNode *body,
                                   char *return_type)
{

    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_DECL_FUNC;
    node->computed_type = &TYPE_VOID;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->static_type = return_type;
    node->data.func_node.name = name_func;
    node->checked = 0;
    node->data.func_node.arg_count = arg_count;
    node->data.func_node.args = malloc(sizeof(ASTNode *) * arg_count);

    for (int i = 0; i < arg_count; i++)
    {
        node->data.func_node.args[i] = args[i];
    }

    node->data.func_node.body = body;

    return node;
}

ASTNode *create_call_function_node(char *name, ASTNode **args, int arg_count)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_CALL_FUNC;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->computed_type = &TYPE_OBJ;
    node->data.func_node.name = name;
    node->data.func_node.args = malloc(sizeof(ASTNode *) * arg_count);

    node->checked = 0;
    for (int i = 0; i < arg_count; i++)
    {
        node->data.func_node.args[i] = args[i];
    }

    node->data.func_node.arg_count = arg_count;

    return node;
}