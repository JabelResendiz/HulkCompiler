

// type.c

#include "../ast/ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TypeValue TYPE_OBJ = {"Object", NULL, NULL, NULL, NULL, 0};
TypeValue TYPE_NUM = {"Number", NULL, &TYPE_OBJ, NULL, NULL, 0};
TypeValue TYPE_STRING = {"String", NULL, &TYPE_OBJ, NULL, NULL, 0};
TypeValue TYPE_BOOLEAN = {"Boolean", NULL, &TYPE_OBJ, NULL, NULL, 0};
TypeValue TYPE_VOID = {"Void", NULL, &TYPE_OBJ, NULL, NULL, 0};
TypeValue TYPE_ERROR = {"Error", NULL, NULL, NULL, NULL, 0};
TypeValue TYPE_GENERIC = {"Generic", NULL, NULL, NULL, NULL, 0};

TypeValue *resolve_op_type(TypeValue *left, TypeValue *right, Operator op)
{

    for (int i = 0; i < rule_count; i++)
    {
        if (compare_types(left, operatorRules[i].left_type) &&
            compare_types(right, operatorRules[i].right_type) &&
            op == operatorRules[i].op)
        {
            return &operatorRules[i].result_type;
        }
    }

    return &TYPE_ERROR;
}

int match_op(TypeValue *first, TypeValue *second, Operator op)
{
    for (int i = 0; i < rule_count; i++)
    {
        if (compare_types(first, operatorRules[i].left_type) &&
            compare_types(second, operatorRules[i].right_type) &&
            op == operatorRules[i].op)
        {
            return 1;
        }
    }

    return 0;
}


int compare_types(TypeValue *first, TypeValue *second)
{
    // fprintf(stderr,"el tipo de first es : %s  y el de second es %s \n", first->name,second->name);
    //  ambos son NULL => son iguales
    if (first == NULL && second == NULL)
        return 1;
    if (first == NULL || second == NULL)
        return 0;

    if (!strcmp(first->name, second->name))
    {
        return compare_types(first->element_type, second->element_type);
    }

    return 0;
}

// Verifica si un tipo ancestor es un ancestro o igual del tipo type
// Devuelve 1 si ancestor es igual a type o alguno de sus ancestro (padre,abuelo)
// Devulve 0 en otro caso
int ancestor_type(TypeValue *ancestor, TypeValue *type_f)
{
    if (!type_f)
        return 0;

    if (compare_types(ancestor, type_f))
    {
        fprintf(stderr, "900000\n");
        return 1;
    }

    return ancestor_type(ancestor, type_f->super_type);
}

// // Marca todos los ancestros de un tipo en un arreglo de flags o tabla hash simple
// void mark_ancestors(TypeValue* type, int* visited, int max_types) {
//     while (type != NULL) {
//         visited[type->id] = 1;
//         type = type->super_type;
//     }
// }

// TypeValue* compute_lca(TypeValue* type1, TypeValue* type2) {
//     // Casos especiales
//     if (type_equals(type1, &TYPE_ANY) || type_equals(type2, &TYPE_ANY)) {
//         return &TYPE_ANY;
//     }
//     if (type_equals(type1, &TYPE_ERROR) || type_equals(type2, &TYPE_ERROR)) {
//         return &TYPE_ERROR;
//     }

//     // Supón que los tipos tienen IDs únicos del 0 al N-1
//     const int MAX_TYPES = 256;  // Aumentar si hay más tipos en tu sistema
//     int visited[MAX_TYPES] = {0};

//     // Marca todos los ancestros de type1
//     mark_ancestors(type1, visited, MAX_TYPES);

//     // Recorre type2 hacia arriba hasta encontrar uno ya marcado
//     while (type2 != NULL) {
//         if (visited[type2->id]) {
//             return type2;  // Primer ancestro común
//         }
//         type2 = type2->super_type;
//     }

//     // Si no se encontró ningún ancestro común, devolvemos TYPE_ANY como fallback
//     return &TYPE_ANY;
// }

// halla el menor ancestro comun de ambos tipos
TypeValue *compute_lca(TypeValue *type_1, TypeValue *type_2)
{
    // si alguno es de tipo ANY
    if (compare_types(type_1, &TYPE_GENERIC) ||
        compare_types(type_2, &TYPE_GENERIC))
    {
        return &TYPE_GENERIC;
    }

    else if (compare_types(type_1, &TYPE_ERROR) ||
             compare_types(type_2, &TYPE_ERROR))
    {
        return &TYPE_ERROR;
    }

    fprintf(stderr, "3232\n");
    if (ancestor_type(type_1, type_2))
    {
        fprintf(stderr, "00000\n");
        return type_1;
    }

    if (ancestor_type(type_2, type_1))
        return type_2;

    return compute_lca(type_1->super_type, type_2->super_type);
}

/// @brief Me dice si type es un tipo builtin
/// @param type
/// @return
int is_builtin_type(TypeValue *type)
{
    return (compare_types(type, &TYPE_BOOLEAN) ||
            compare_types(type, &TYPE_NUM) ||
            compare_types(type, &TYPE_STRING) ||
            compare_types(type, &TYPE_OBJ) ||
            compare_types(type, &TYPE_VOID) ||
            compare_types(type, &TYPE_ERROR));
}

/// @brief Crea un tipo nuevo
/// @param name
/// @param type
/// @return retorna el tipo creado
TypeValue *create_type(char *name, TypeValue *type, TypeValue **param_types, int count, struct ASTNode *node)
{
    TypeValue *new_type = malloc(sizeof(TypeValue));
    new_type->name = name;
    new_type->super_type = type;
    new_type->argument_types = param_types;
    new_type->num_params = count;
    new_type->def_node = node;
    return new_type;
}

// averigua el tipo real (si esta definido en el programa se crea)
// sino se mantiene el que tiene por defecto
TypeValue *resolve_node_type(ASTNode *node)
{
    TypeValue *type = node->computed_type;

    // cunado permita la creacion de tipos nuevos
    Symbol *symbol = find_type_scopes(node->scope, type->name);

    if (symbol)
        return symbol->type;

    return type;
}


// Busca todos los tipos de los argumentos pasados por argumento
TypeValue **resolve_nodes_type(ASTNode **args, int arg_count)
{
    TypeValue **types = malloc(sizeof(TypeValue *) * arg_count);

    for (int i = 0; i < arg_count; i++)
    {
        types[i] = resolve_node_type(args[i]);
    }

    return types;
}

