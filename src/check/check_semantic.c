
// check_semantic.c

#include "check_semantic.h"


void make_checker(ASTNode* node)
{
    ASTVisitor visitor = 
    {
        .basic =
        {
            .program = visit_program,
            .number = visit_number,
            //.string = visit_string,
            .boolean = visit_boolean,
            //.variable = visit_variable
        },
        .expr =
        {
            .binary = visit_binary_op,
            .assignment = visit_assignment
        },
         .control =
         {
        //     .block = visit_block,
             .let_in = visit_let,
        //     .conditional = visit_conditional
         },
        .error_count =0,
        .errors = NULL,
        .current_function = NULL,
        .current_type = NULL
    };

    accept(&visitor,node);

}



ValueType resolve_node_type(ASTNode* node)
{
    ValueType type = node->computed_type;

    // cunado permita la creacion de tipos nuevos
    //Symbol* symbol = find_defined_type(node->scope,type);
    //if(symbol)return symbol->type;

    return type;

    
}