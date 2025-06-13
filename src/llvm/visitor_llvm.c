
// visitor_llvm.c

#include "visitor_llvm.h"
#include <stdlib.h>

LLVMValueRef codegen_accept(LLVMVisitor *visitor, ASTNode *node)
{
    if (!node)
        return 0;

    switch (node->type)
    {
    case AST_PROGRAM:
        return visitor->basic.program(visitor, node);

    case AST_NUM:
        return visitor->basic.number(visitor, node);

    case AST_STRING:
        return visitor->basic.string(visitor, node);

    case AST_VAR:
        return visitor->basic.variable(visitor, node);

    case AST_BOOLEAN:
        return visitor->basic.boolean(visitor, node);

    case AST_BINARY_OP:
        return visitor->expr.binary(visitor, node);

    case AST_ASSIGNMENT:
        return visitor->expr.assignment(visitor, node);
    
    case AST_CALL_FUNC:
        return visitor->expr.call_function(visitor,node);

    // case AST_BLOCK:
    //     return visitor->control.block(visitor, node);

    case AST_LET:
        return visitor->control.let_in(visitor, node);

    case AST_IF:
        return visitor->control.conditional(visitor, node);
    
    case AST_WHILE:
        return visitor->control.while_loop(visitor,node);
       
    case AST_DECL_FUNC:
        return visitor->control.dec_function(visitor,node);
        
    default:
        exit(1);
    }
}