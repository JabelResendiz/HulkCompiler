

// ast.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "type.h"

ASTNode *create_program_node(ASTNode **statements,
                             int count,
                             ASTNodeType type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = type;
    node->scope = create_scope(NULL);
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
    node->computed_type = &TYPE_NUM;

    node->data.number_value = value;

    return node;
}

ASTNode *create_var_node(char *name, char *type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_VAR;
    node->scope = create_scope(NULL);
    node->computed_type = &TYPE_OBJ;
    node->data.var_name = name;

    return node;
}

ASTNode *create_string_node(char *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_STRING;
    node->scope = create_scope(NULL);
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
    node->computed_type = &TYPE_BOOLEAN;
    node->data.string_value = value;

    return node;
}

ASTNode *create_binary_op_node(Operator op,
                               char *name_op,
                               ASTNode *left,
                               ASTNode *right,
                               TypeValue* type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_BINARY_OP;
    node->scope = create_scope(NULL);
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
    node->computed_type = &TYPE_OBJ;
    node->data.func_node.name = "";
    node->data.func_node.args = malloc(sizeof(ASTNode *) * dec_count);

    for (int i = 0; i < dec_count; i++)
    {
        node->data.func_node.args[i] = bindings[i];
    }

    node->data.func_node.arg_count = dec_count;
    node->data.func_node.body = body;

    return node;
}

ASTNode *create_assignment_node(char *name, ASTNode *value, char *type_name, ASTNodeType type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = type;
    node->computed_type = &TYPE_VOID;
    node->scope = create_scope(NULL);
    node->data.binary_op.left = create_var_node(name, NULL);
    node->data.binary_op.right = value;
    // node->data.binary_op.left->static_type = type_name;
    return node;
}

ASTNode *create_conditional_node(ASTNode *cond,
                                 ASTNode *body,
                                 ASTNode *else_branch)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    node->line = line_num;
    node->type = AST_IF;
    node->computed_type = &TYPE_OBJ;
    node->scope = create_scope(NULL);
    node->data.conditional.cond = cond;
    node->data.conditional.body = body;
    node->data.conditional.else_branch = else_branch;

    return node;
}

ASTNode *create_call_function_node(char *name, ASTNode **args, int arg_count)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->line = line_num;
    node->type = AST_CALL_FUNC;
    node->scope = create_scope(NULL);
    node->computed_type = &TYPE_OBJ;
    node->data.func_node.name = name;
    node->data.func_node.args = malloc(sizeof(ASTNode*) * arg_count);

    node->checked = 0;
    for(int i=0;i<arg_count;i++)
    {
        node->data.func_node.args[i] = args[i];
    }

    node->data.func_node.arg_count = arg_count;

    return node;
}

void free_ast(ASTNode *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_VAR:
        free(node->data.var_name);
        break;
    case AST_BINARY_OP:
    case AST_ASSIGNMENT:
        free_ast(node->data.binary_op.left);
        free_ast(node->data.binary_op.right);
        break;

    case AST_PROGRAM:
    case AST_BLOCK:
        for (int i = 0; i < node->data.program.count; i++)
            free_ast(node->data.program.statements[i]);
        free(node->data.program.statements);
        break;

    case AST_LET:
        for (int i = 0; i < node->data.func_node.arg_count; i++)
            free_ast(node->data.func_node.args[i]);
        free_ast(node->data.func_node.body);
        break;

    case AST_IF:
        free_ast(node->data.conditional.body);
        free_ast(node->data.conditional.else_branch);
        free_ast(node->data.conditional.cond);
        break;
    }

    free_scope(node->scope);
    free(node);
}

void print_ast(ASTNode *node, int indent)
{
    if (!node)
        return;

    for (int i = 0; i < indent; i++)
        printf("  ");

    switch (node->type)
    {
    case AST_PROGRAM:
        printf("Program:\n");
        for (int i = 0; i < node->data.program.count; i++)
        {
            print_ast(node->data.program.statements[i], indent + 1);
        }
        break;
    case AST_BLOCK:
        printf("Block:\n");
        for (int i = 0; i < node->data.program.count; i++)
        {
            print_ast(node->data.program.statements[i], indent + 1);
        }
        break;
    case AST_LET:
        printf("Let-in: %s\n", node->data.func_node.name);
        print_ast(node->data.func_node.body, indent + 1);
        break;
    case AST_NUM:
        printf("Number: %g\n", node->data.number_value);
        break;
    case AST_STRING:
        printf("String: %s\n", node->data.string_value);
        break;
    case AST_BOOLEAN:
        printf("Boolean: %s\n", node->data.string_value);
        break;
    case AST_VAR:
        printf("Variable: %s\n", node->data.var_name);
        break;
    case AST_BINARY_OP:
    {
        const char *op_str;
        switch (node->data.binary_op.op)
        {
        case OP_ADD:
            op_str = "+";
            break;
        case OP_SUB:
            op_str = "-";
            break;
        case OP_MULT:
            op_str = "*";
            break;
        case OP_DIV:
            op_str = "/";
            break;
        case OP_MOD:
            op_str = "%";
            break;
        case OP_POW:
            op_str = "^";
            break;
        case OP_AND:
            op_str = "&";
            break;
        case OP_OR:
            op_str = "|";
            break;
        case OP_CONCAT:
            op_str = "@";
            break;
        // case OP_DCONCAT: op_str = "@@"; break;
        case OP_EQ:
            op_str = "==";
            break;
        case OP_NEQ:
            op_str = "!=";
            break;
        case OP_GE:
            op_str = ">=";
            break;
        case OP_GT:
            op_str = ">";
            break;
        case OP_LE:
            op_str = "<=";
            break;
        case OP_LT:
            op_str = "<";
            break;
        default:
            op_str = "?";
            break;
        }
        printf("Binary Op: %s\n", op_str);
        print_ast(node->data.binary_op.left, indent + 1);
        print_ast(node->data.binary_op.right, indent + 1);
        break;
    }
    case AST_ASSIGNMENT:
        printf("Assignment:\n");
        print_ast(node->data.binary_op.left, indent + 1);
        print_ast(node->data.binary_op.right, indent + 1);
        break;
    case AST_IF:
        printf("Conditional:\n");
        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Condition:\n");
        print_ast(node->data.conditional.cond, indent + 2);
        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("If part:\n");
        print_ast(node->data.conditional.body, indent + 2);
        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("else part:\n");
        print_ast(node->data.conditional.else_branch, indent + 2);
        break;
    }
}