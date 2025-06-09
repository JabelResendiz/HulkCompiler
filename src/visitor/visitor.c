
//visitor.c

#include "visitor.h"

void accept(ASTVisitor* visitor,ASTNode* node)
{
    if(!node) return;

    switch (node->type)
    {
    case AST_PROGRAM:
        visitor->basic.program(visitor,node);
        break;
    case AST_NUM:
        visitor->basic.number(visitor,node);
        break;
    case AST_STRING:
        visitor->basic.string(visitor,node);
        break;
    case AST_VAR:
        visitor->basic.variable(visitor,node);
        break;
    case AST_BOOLEAN:
        visitor->basic.boolean(visitor,node);
        break;
    case AST_BINARY_OP:
        visitor->expr.binary(visitor,node);
        break;
    case AST_ASSIGNMENT:
        visitor->expr.assignment(visitor,node);
        break;
    case AST_BLOCK:
        visitor->control.block(visitor,node);
        break;
    case AST_LET:
        visitor->control.let_in(visitor,node);
        return;
    case AST_IF:
        visitor->control.conditional(visitor,node);
        break;
    default:
        break;
    }
}



// void get_context(ASTVisitor* visitor,ASTNode* node)
// {
//     fo
// }