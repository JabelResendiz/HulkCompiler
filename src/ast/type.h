
//types.h

#ifndef TYPE_H
#define TYPE_H


typedef enum
{
    OP_ADD,OP_SUB,OP_MULT,OP_DIV,OP_CONCAT,OP_DCONCAT,OP_POW,OP_MOD,
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
extern TypeValue TYPE_GENERIC;

typedef struct 
{
    Operator op;
    TypeValue* left_type;
    TypeValue* right_type;
    TypeValue* result_type; 
}OperatorRule;

extern int rule_count;
extern OperatorRule operatorRules[];

int match_op(TypeValue* first, TypeValue* second,Operator op);
int compare_types (TypeValue* first, TypeValue* second);


int ancestor_type(TypeValue* ancestor,TypeValue* type_f);


TypeValue* compute_lca(TypeValue* type_1,TypeValue* type_2);

int is_builtin_type(TypeValue* type);
// TypeValue* resolve_op_type(TypeValue* left,TypeValue* right, Operator op, int flag);

TypeValue* create_type(char* name, TypeValue* type, TypeValue** param_types,int count, struct ASTNode* node);

#endif