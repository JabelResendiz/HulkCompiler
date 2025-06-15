
//visitor.c

#include "visitor.h"

void accept(ASTVisitor* visitor,ASTNode* node)
{
       // fprintf(stderr,"VOY A LLAMAR AL VISITOR DE TYPE\n");
    if(!node) return;

        //fprintf(stderr,"VOY A LLAMAR AL VISITOR DE TYPE\n");
    switch (node->type)
    {
    case AST_PROGRAM:
        //fprintf(stderr,"VOY A LLAMAR AL VISITOR DE TYPE\n");
        visitor->basic.program(visitor,node);
        break;
    case AST_NUM:
        visitor->basic.number(visitor,node);
        break;
    case AST_STRING:
        visitor->basic.string(visitor,node);
        break;
    case AST_VAR:
        //fprintf(stderr,"VOY A LLAMAR AL VISITOR DE TYPE\n");
        visitor->basic.variable(visitor,node);
        break;
    case AST_BOOLEAN:
        visitor->basic.boolean(visitor,node);
        break;
    case AST_BINARY_OP:
        visitor->expr.binary(visitor,node);
        break;
    case AST_ASSIGNMENT:
    case AST_DESTRUCTOR:
        visitor->expr.assignment(visitor,node);
        break;
    case AST_CALL_FUNC:
        visitor->expr.call_function(visitor,node);
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
    case AST_WHILE:
        visitor->control.while_loop(visitor,node);
        break;
    case AST_DECL_FUNC:
    //fprintf(stderr,"VOY A LLAMAR AL METODO DE DECL_ FUNC\n");
        visitor->control.dec_function(visitor,node);
        break;

    case AST_TYPE:
    //fprintf(stderr,"VOY A LLAMAR AL VISITOR DE TYPE\n");
        visitor->types.type_dec(visitor,node);
        break;
    case AST_INSTANCE:
       // fprintf(stderr,"VOY A LLAMAR AL VISITOR DE TYPE\n");
        visitor->types.type_instance(visitor,node);
        break;
    
    case AST_GETTER:
       // fprintf(stderr,"VOY A LLAMAR AL VISITOR DE TYPE\n");
        visitor->attrs.getter(visitor,node);
        break;
    case AST_SETTER:
        visitor->attrs.setter(visitor,node);
        break;
        
    default:
        break;
    }

}

