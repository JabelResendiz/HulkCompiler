

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

ASTNode *create_program_node(ASTNode **statements,
                             int count,
                             ASTNodeType type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = type;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->data.program.statements = malloc(sizeof(ASTNode *) * count);

    for (int i = 0; i < count; i++)
    {
        node->data.program.statements[i] = statements[i];
    }

    node->data.program.count = count;

    return node;
}

ASTNode *create_num_node(double value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_NUM;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->computed_type = &TYPE_NUM;
    node->data.number_value = value;

    return node;
}

ASTNode *create_var_node(char *name, char *type, int param)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_VAR;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->computed_type = &TYPE_OBJ;
    node->data.var_name = name;
    node->param = param;

    if(type)
        node->static_type = type;

    fprintf(stderr,"el nombre de la variable es %s y es un parametro %d\n", name,param);

    return node;
}

ASTNode *create_string_node(char *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_STRING;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->computed_type = &TYPE_STRING;
    node->data.string_value = value;

    return node;
}

ASTNode *create_boolean_node(char *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_BOOLEAN;
    node->scope = create_scope(NULL);
    node->env = create_env(NULL);
    node->computed_type = &TYPE_BOOLEAN;
    node->data.string_value = value;

    return node;
}