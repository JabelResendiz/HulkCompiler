
// check_semantic.c

#include "check_semantic.h"
#include "../ast/ast.h"
#include "../visitor/visitor.h"
#include "../scope/env.h"
#include "../error/error.h"
#include <stdio.h>
#include <string.h>


int make_checker(ASTNode *node)
{

    fprintf(stderr, "estamos en el checker make de check_semantic\n");

    ASTVisitor visitor =
        {
            .basic =
                {
                    .program = visit_program,
                    .number = visit_number,
                    .string = visit_string,
                    .boolean = visit_boolean,
                    .variable = visit_variable},
            .expr =
                {
                    .binary = visit_binary_op,
                    .assignment = visit_assignment,
                    .call_function = visit_call_function},
            .control =
                {
                    .block = visit_block,
                    .let_in = visit_let,
                    .conditional = visit_conditional,
                    .while_loop = visit_while_loop,
                    .dec_function = visit_dec_function},
            .types =
                {
                    .type_dec = visit_type_dec,
                    .type_instance = visit_type_instance,
                },
            .attrs =
                {
                    .getter = visit_getter,
                    .setter = visit_setter
                },
            .error_count = 0,
            .errors = NULL,
            .current_function = NULL,
            .current_type = NULL};

    accept(&visitor, node);
    
    ERROR* e = error_to_string(visitor.errors,visitor.error_count);

    print_error_structure(e);
    free_semantic_error(e);
    
    return visitor.error_count;
}


/// @brief Inicializa el entorno global
/// @param v
/// @param node EL nodo del programa
void initialize_program_environment(ASTVisitor *v, ASTNode *node)
{
    for (int i = 0; i < node->data.program.count; i++)
    {
        ASTNode *child = node->data.program.statements[i];

        switch (child->type)
        {
        case AST_DECL_FUNC:
            child->env->parent = node->env;
            child->scope->parent = node->scope;

            if (!create_env_item(node->env, child, child->data.func_node.name, 0))
            {
                fprintf(stderr, "Ya existe el entorno Item creado\n");
            }
            break;

        case AST_TYPE:
            child->env->parent = node->env;
            child->scope->parent = node->scope;

            if (!create_env_item(node->env, child, child->data.typeDef.name_type, 1))
            {
                fprintf(stderr, "Ya existe el entorno Item creado\n");
            }
            break;

        default:
            break;
        }
    }
}



