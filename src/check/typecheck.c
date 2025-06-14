

// typecheck.c

#include "check_semantic.h"
#include "../type_value/type.h"
#include "../scope/unifiedIndex.h"
#include "../scope/scope.h"
#include <string.h>

void visit_program(ASTVisitor *v, ASTNode *node)
{
    init(node->scope);
    initialize_program_environment(v, node); // Regsitra funciones/tipos en el contexto global

    for (int i = 0; i < node->data.program.count; i++)
    {
        ASTNode *child = node->data.program.statements[i];
        propagate_env_scope(node, child);
        accept(v, child);

        if (child->type == AST_ASSIGNMENT)
        {
            node->computed_type = &TYPE_ERROR;
            message_semantic_error(v, "Variable '%s' tiene que ser inicializada primero en un bloque 'let-in'. Line %d.",
                                   child->data.binary_op.left->data.var_name, child->line);
        }
    }
}

void visit_number(ASTVisitor *v, ASTNode *node) {}

void visit_boolean(ASTVisitor *v, ASTNode *node) {}

void visit_string(ASTVisitor *v, ASTNode *node)
{
    const char *str = node->data.string_value;
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            char next = str[i + 1];
            if (next == '\0' || !(
                                    str[i + 1] == 'n' ||
                                    str[i + 1] == 't' ||
                                    str[i + 1] == '\\' ||
                                    str[i + 1] == '\"'))
            {
                message_semantic_error(v, "Secuencia de escape invalida '\\%c'. Line %d", str[i + 1], node->line);
            }
            i++;
        }
        i++;
    }
}

void visit_binary_op(ASTVisitor *v, ASTNode *node)
{

    ASTNode *left = node->data.binary_op.left;
    ASTNode *right = node->data.binary_op.right;

    propagate_env_scope(node, left);
    propagate_env_scope(node, right);

    accept(v, left);
    accept(v, right);

    // unificar las expresiones por ejmplo para function f(x)= > x+12; es necesario unificar la x

    int unified = try_unify_binary_op(v, left, right, node->data.binary_op.op,
                                      node->data.binary_op.name_op);

    if (unified == 3 || unified == 2)
    {
        accept(v, left);
    }
    if (unified == 3 || unified == 1)
    {
        accept(v, right);
    }

    TypeValue *type_left = resolve_node_type(left);
    TypeValue *type_right = resolve_node_type(right);

    if (!match_op(type_left, type_right, node->data.binary_op.op))
    {
        message_semantic_error(v,"Operador '%s' no puede ser usado entre '%s' y '%s'. Line %d",
                                node->data.binary_op.name_op, type_left->name,type_right->name,node->line);
    }

    fprintf(stderr, "CON EXITO DE BINARY OP\n");
}

void visit_block(ASTVisitor *v, ASTNode *node)
{
    if (!node->checked)
    {
        // si el nodo no ha sido verifica antes,
        // se inicializa el entonro del prgoram
        initialize_program_environment(v, node);
    }

    node->checked = 1;

    // itera por las sentencias del bloque
    ASTNode *curr = NULL;

    for (int i = 0; i < node->data.program.count; i++)
    {
        curr = node->data.program.statements[i];
        // propaga el scope y el entorno
        propagate_env_scope(node, curr);

        // visita recursivamente la sentencia
        accept(v, curr);

        if (curr->type == AST_ASSIGNMENT)
        {
            node->computed_type = &TYPE_ERROR;
            message_semantic_error(v, "Variable '%s' tiene que ser inicializada primero en un bloque 'let-in'. Line %d.",
                                   curr->data.binary_op.left->data.var_name, curr->line);
        }
    }

    if (curr)
    {
        // determinacion del tipo resultante
        node->computed_type = resolve_node_type(curr);
        node->usages = add_usages(curr, node->usages);
    }

    else
    {
        // si no hay sentencias
        node->computed_type = &TYPE_VOID;
    }

}


// void visit_unary_op(ASTVisitor* v, ASTNode* node)
// {

// }