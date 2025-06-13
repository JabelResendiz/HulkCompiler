

// type.c

#include "type.h"
#include <stdlib.h>
#include <string.h>



TypeValue TYPE_OBJ = { "Object", NULL, NULL, NULL, NULL, 0 };
TypeValue TYPE_NUM = { "Number", NULL, &TYPE_OBJ, NULL, NULL, 0 };
TypeValue TYPE_STRING = { "String", NULL, &TYPE_OBJ, NULL, NULL, 0 };
TypeValue TYPE_BOOLEAN = { "Boolean", NULL, &TYPE_OBJ, NULL, NULL, 0 };
TypeValue TYPE_VOID = { "Void", NULL, &TYPE_OBJ, NULL, NULL, 0 };
TypeValue TYPE_ERROR = { "Error", NULL, NULL, NULL, NULL, 0 };
TypeValue TYPE_ANY = { "Any", NULL, NULL, NULL, NULL, 0 };


OperatorRule operatorRules[] =
    {
        {OP_ADD, &TYPE_NUM, &TYPE_NUM, &TYPE_NUM},
        {OP_SUB, &TYPE_NUM, &TYPE_NUM, &TYPE_NUM},
        {OP_MULT, &TYPE_NUM, &TYPE_NUM, &TYPE_NUM},
        {OP_DIV, &TYPE_NUM, &TYPE_NUM, &TYPE_NUM},
        {OP_POW, &TYPE_NUM, &TYPE_NUM, &TYPE_NUM},
        {OP_MOD, &TYPE_NUM, &TYPE_NUM, &TYPE_NUM},

        {OP_CONCAT, &TYPE_STRING, &TYPE_STRING, &TYPE_STRING},
        {OP_CONCAT, &TYPE_NUM, &TYPE_STRING, &TYPE_STRING},
        {OP_CONCAT, &TYPE_STRING, &TYPE_NUM, &TYPE_STRING},

        {OP_AND, &TYPE_BOOLEAN, &TYPE_BOOLEAN, &TYPE_BOOLEAN},
        {OP_OR, &TYPE_BOOLEAN, &TYPE_BOOLEAN, &TYPE_BOOLEAN},
        {OP_NEQ, &TYPE_BOOLEAN, &TYPE_BOOLEAN, &TYPE_BOOLEAN},

        {OP_GT, &TYPE_NUM, &TYPE_NUM, &TYPE_BOOLEAN},
        {OP_GE, &TYPE_NUM, &TYPE_NUM, &TYPE_BOOLEAN},
        {OP_LT, &TYPE_NUM, &TYPE_NUM, &TYPE_BOOLEAN},
        {OP_LE, &TYPE_NUM, &TYPE_NUM, &TYPE_BOOLEAN},
        {OP_EQ, &TYPE_NUM, &TYPE_NUM, &TYPE_BOOLEAN},
        {OP_EQ, &TYPE_STRING, &TYPE_STRING, &TYPE_BOOLEAN},
        {OP_LT, &TYPE_BOOLEAN, &TYPE_BOOLEAN, &TYPE_BOOLEAN},
};

int match_op(TypeValue* first, TypeValue* second, Operator op)
{
    int rule_count = sizeof(operatorRules) / sizeof(operatorRules[0]);

    for (int i = 0; i < rule_count; i++)
    {
        if (compare_types(first,&operatorRules[i].left_type) &&
            compare_types(first,&operatorRules[i].right_type) &&
            op == operatorRules[i].op)
        {
            return 1;
        }
    }

    return 0;
}



int compare_types (TypeValue* first, TypeValue* second)
{
    // ambos son NULL => son iguales
    if(first == NULL && second == NULL) return 1;

    // Uno es NULL y el otro no
    if(first == NULL || second == NULL) return 0;

    // Comparar nombre
    if(strcmp(first->name,second->name)!=0) return 0;

    // COmparar subtipos recursivo
    if(!compare_types(first->element_type,second->element_type)) return 0;

    // Comparar tipos de parametros uno a uno
    for(int i=0;i< first->num_params ; ++i)
    {
        if(!compare_types(first->argument_types[i],second->argument_types[i]))
            return 0;
    }

    return 1;
}


// Verifica si un tipo ancestor es un ancestro o igual del tipo type
// Devuelve 1 si ancestor es igual a type o alguno de sus ancestro (padre,abuelo) 
// Devulve 0 en otro caso
int ancestor_type(TypeValue* ancestor,TypeValue* type_f)
{
    if(!type_f) return 0;

    if(compare_types(ancestor,type_f)) return 1;

    return ancestor_type(ancestor,type_f->super_type);

}