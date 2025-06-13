

// variable_semantic.c
#include "check_semantic.h"
#include "../ast/keyword.h"
#include <string.h>

#define foreach_valueList(elem, list) \
    for (UsageElemental *elem = (list) ? (list)->first : NULL; elem != NULL; elem = elem->next)

void visit_let(ASTVisitor *v, ASTNode *node)
{
    ASTNode **bindings = node->data.func_node.args;
    ASTNode *body = node->data.func_node.body;

    propagate_env_scope(node, body);

    for (int i = 0; i < node->data.func_node.arg_count; i++)
    {
        propagate_env_scope(node, bindings[i]);
        accept(v, bindings[i]);
    }

    accept(v, body);

    node->computed_type = resolve_node_type(body);
}

void visit_assignment(ASTVisitor *v, ASTNode *node)
{
    ASTNode *left = node->data.binary_op.left;
    ASTNode *right = node->data.binary_op.right;

    if (match_keyword(left->data.var_name))
    {
        printf("Keyword '%s' can not be used as a variable name. Line: %d.", left->data.var_name, node->line);
        exit(1);
    }

    propagate_env_scope(node, left);
    propagate_env_scope(node, right);

    // buscar el tipo definido (estatico de la variable)
    fprintf(stderr, "el tipo estatico de la variable de tipo es %s\n ", left->static_type);
    Symbol *static_types = find_type_scopes(node->scope, left->static_type);

    // flag para saber si luego habra que liberar memorai
    int flag = 0;

    // si el tipo no existe, intentara inferirlo en el entorno global
    // tipo el usuario a:T pero T aun no ha sido resuelto
    if (strcmp(left->static_type, "") && !static_types)
    {
        fprintf(stderr, "***************\n");

        EnvItem *env_item = find_env_item(node->env, left->data.var_name, 1, 0);

        if (env_item)
        {
            if (!env_item->usages->checked)
            {
                // encontro el tipo en entorno, y asegura entregarlo al entorno actual
                accept(v, env_item->usages);

                // intentara buscarlo nuevamente el tipo en el scope
                static_types = find_type_scopes(node->scope, left->static_type);
            }
            else if(env_item->computed_type)
            {
                static_types = malloc(sizeof(Symbol));
                static_types->name = env_item->computed_type->name;
                static_types->type = env_item->computed_type;
                flag =1;
            }

            if (!static_types)
            {
                // si tampoco tuvo suerte esta vez

                // static_types = malloc(sizeof(Symbol));

                // if (env_item->computed_type)
                // {
                //     static_types->name = env_item->computed_type->name;
                //     static_types->type = env_item->computed_type;
                // }

                // flag = 1;

                fprintf(stderr,"Hay un error\n");
                exit(1);
            }
        }

        // no se encontro en el contexto ERROR

        else
        {
            fprintf(stderr, "NO se encontro en el contexto , el tipo no esta definido \n");
        }
    }

    // se visita el lado derecho
    accept(v, right);

    // se busca resolver el tipo del lado
    TypeValue *inferred_type = resolve_node_type(right);

    fprintf(stderr, "el tipo inferido es %s\n", inferred_type->name);

    // si el tipo aun es GENERIC , pero hay un tipo definido (static_type), se intenta unificar el tipo del valor con el esperado
    if (compare_types(inferred_type, &TYPE_GENERIC) &&
        static_types && try_unify_operand(v, right, static_types->type))
    {
        fprintf(stderr, "))))))))))))))))\n");
        // se vuelve a revisar el nodo y buscar el tipo real
        accept(v, right);
        inferred_type = resolve_node_type(right);
    }

    // si existe un tipo asociado y no es ancestro del tipo inferido
    if (static_types && !ancestor_type(static_types->type, inferred_type))
    {
        // se reporta un error

        fprintf(stderr, "variable fue definido pero no se ha inferido el tipo donde esta\n");
        exit(1);
    }

    // uso de destructores

     if (strcmp(left->static_type, "") && node->type == AST_DESTRUCTOR)
    {
        fprintf(stderr,"VARIABLE SNO PUEDEN SER ANOTADAS TIPO \n");
        exit(1);
    }
    // se usa el tipo definido como definitivo, sobreescribinedo la inferencia, para garantizar conssitencia
    if (static_types)
    {
        inferred_type = static_types->type;
    }

    Symbol *s = scope_lookup(node->scope, left->data.var_name);

    if(!s && node->type == AST_DESTRUCTOR)
    {
        fprintf(stderr,"Hay cosas por hacer\n");
        exit(1);
    }

    // si es una declaracion let , se declara la var en el scope del padre
    else if (node->type == AST_ASSIGNMENT)
    {
        fprintf(stderr, "99999999999999\n");

        scope_add_symbol(node->scope->parent, left->data.var_name, inferred_type, right, 0);

        // se busac ahora el nuevo simbolo
        Symbol *new_s = scope_lookup(node->scope, left->data.var_name);

        // se agrega todas los usages del mismo
        new_s->usage = add_usages(right, new_s->usage);

        // finalmente se asegura que l tipo de retorno de right es el inferido
        right->computed_type = inferred_type;
    }

    // si hay compatiblidad de tipo (o tipo GENERIC) lo que implica que puedes especializarse
    else if (
        ancestor_type(s->type, &inferred_type) ||
        ancestor_type(inferred_type, &TYPE_GENERIC) ||
        ancestor_type(s->type, &TYPE_GENERIC))
    {
        // si el valor es GENERIC pero el simbolo tiene tipo real
        if (compare_types(inferred_type, &TYPE_GENERIC) &&
            !compare_types(s->type, &TYPE_GENERIC))
        {
            // se intenta unificar
            if (try_unify_operand(v, right, s->type))
            {
                accept(v, right);
                inferred_type = resolve_node_type(right);
            }
        }

        // si el simbolo es GENERIC pero el tipo no
        else if (compare_types(s->type, &TYPE_GENERIC) &&
                 !compare_types(inferred_type, &TYPE_GENERIC))
        {
            s->type = inferred_type;

            foreach_valueList(der, s->usage)
            {
                ASTNode *node = der->node;
                if (node && compare_types(node->computed_type, &TYPE_GENERIC))
                {
                    try_unify_operand(v, node, inferred_type);
                }
            }

            right->computed_type = inferred_type;
        }

        // se registran las derivaciones para analisis o futuras unificaciones
        s->usage = add_usages(right, s->usage);
        node->usages = add_usages(left, node->usages);
    }

    // si nada de lo anterior es posible entonces es un error de tipo
    else
    {
        fprintf(stderr, "el tipo asignado no es seguro\n");
        exit(1);
    }

    right->computed_type = inferred_type;

    // si es tipo reasignacion
    if (node->type ==AST_DESTRUCTOR)
    {
        node->computed_type = inferred_type;
    }
    // node->computed_type = inferred_type;

    if(flag) free(static_types);
    
    fprintf(stderr, "el tipo del nodo es %s\n", node->computed_type->name);
}

void visit_variable(ASTVisitor *v, ASTNode *node)
{

    // Buscar
    Symbol *sym = scope_lookup(node->scope, node->data.var_name);

    // fprintf(stderr," se encontro el simbolo en ")
    if (sym)
    {
        fprintf(stderr, "\n00000000 - %s - %d\n", sym->name, sym->param);
        node->computed_type = sym->type;
        node->param = sym->param;
        node->usages = sym->usage;
        return;
    }

    // si no se encontro la variable en la tabla de simbolos del nodo
    else if (!compare_types(node->computed_type, &TYPE_ERROR))
    {
        // habra que buscar en el contexto semantico mas global
        fprintf(stderr, "\n333333333333\n");
        EnvItem *item = find_env_item(node->env, node->data.var_name, 0, 1);

        if (!item)
        {
            node->computed_type = &TYPE_ERROR;
            fprintf(stderr, "Un error grande\n");
            exit(1);
        }
        else
        {
            accept(v, item->usages);
            // se marca el nodo como no revisado para su posterior revisado
            item->usages->checked = 0;
            // se espera que la varaible ya este registrado en el scope del nodo
            sym = scope_lookup(node->scope, node->data.var_name);
            node->computed_type = sym->type;
            node->param = sym->param;
            node->usages = sym->usage;
        }
    }
    fprintf(stderr, "HAY UN ERROR EN VISIT_VARIABLE\n");
    exit(1);
}
