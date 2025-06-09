
//types.h

#ifndef TYPES_H
#define TYPES_H

typedef enum
{
    TYPE_NUM,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_VOID,
    TYPE_OBJ,
    TYPE_UNKNOWN
}ValueType;


typedef enum
{
    OP_ADD,OP_SUB,OP_MULT,OP_DIV,OP_CONCAT,OP_POW,OP_MOD,
    OP_AND,OP_OR,OP_NEQ,
    OP_GT,OP_LT,OP_EQ,OP_GE,OP_LE
    
}Operator;


typedef struct 
{
    Operator op;
    ValueType left_type;
    ValueType right_type;
    ValueType result_type; 
}OperatorRule;

extern OperatorRule operatorRules[];

int match_op(ValueType first, ValueType second,Operator op);

#endif