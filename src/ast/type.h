
//types.h

#ifndef TYPE_H
#define TYPE_H

// typedef enum
// {
//     TYPE_NUM,
//     TYPE_STRING,
//     TYPE_BOOLEAN,
//     TYPE_VOID,
//     TYPE_OBJ,
//     TYPE_UNKNOWN
// }ValueType;


typedef enum
{
    OP_ADD,OP_SUB,OP_MULT,OP_DIV,OP_CONCAT,OP_POW,OP_MOD,
    OP_AND,OP_OR,OP_NEQ,
    OP_GT,OP_LT,OP_EQ,OP_GE,OP_LE
    
}Operator;



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

extern TypeValue TYPE_NUM;
extern TypeValue TYPE_STRING;
extern TypeValue TYPE_STRING;
extern TypeValue TYPE_BOOLEAN;
extern TypeValue TYPE_OBJ;
extern TypeValue TYPE_VOID;
extern TypeValue TYPE_ERROR;


typedef struct 
{
    Operator op;
    TypeValue* left_type;
    TypeValue* right_type;
    TypeValue* result_type; 
}OperatorRule;


extern OperatorRule operatorRules[];

int match_op(TypeValue* first, TypeValue* second,Operator op);
int compare_types (TypeValue* first, TypeValue* second);

int ancestor_type(TypeValue* ancestor,TypeValue* type_f);

#endif