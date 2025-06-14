
//types.h

#ifndef TYPE_H
#define TYPE_H

#include "operators.h"

typedef struct ASTNode ASTNode;

// aqui se define un tipo del lenguaje ya sea de los nativos o los creados
typedef struct TypeValue
{
    char* name;
    struct TypeValue* element_type;
    struct TypeValue* super_type;
    struct TypeValue** argument_types;
    struct ASTNode* def_node;
    int num_params;
}TypeValue;

// TIPOS NATIVOS
extern TypeValue TYPE_NUM;
extern TypeValue TYPE_STRING;
extern TypeValue TYPE_STRING;
extern TypeValue TYPE_BOOLEAN;
extern TypeValue TYPE_OBJ;
extern TypeValue TYPE_VOID;
extern TypeValue TYPE_ERROR;
extern TypeValue TYPE_GENERIC;


int compare_types (TypeValue* first, TypeValue* second);


int ancestor_type(TypeValue* ancestor,TypeValue* type_f);


TypeValue* compute_lca(TypeValue* type_1,TypeValue* type_2);

int is_builtin_type(TypeValue* type);

TypeValue* create_type(char* name, TypeValue* type, TypeValue** param_types,int count, struct ASTNode* node);

int match_op(TypeValue *first, TypeValue *second, Operator op);

TypeValue *resolve_op_type(TypeValue *left, TypeValue *right, Operator op);

TypeValue *resolve_node_type(ASTNode *node);
TypeValue **resolve_nodes_type(ASTNode **args, int arg_count);


#endif