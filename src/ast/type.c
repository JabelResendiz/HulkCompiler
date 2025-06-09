

// type.c

#include "type.h"

OperatorRule operatorRules[] =
    {
        {OP_ADD, TYPE_NUM, TYPE_NUM, TYPE_NUM},
        {OP_SUB, TYPE_NUM, TYPE_NUM, TYPE_NUM},
        {OP_MULT, TYPE_NUM, TYPE_NUM, TYPE_NUM},
        {OP_DIV, TYPE_NUM, TYPE_NUM, TYPE_NUM},
        {OP_POW, TYPE_NUM, TYPE_NUM, TYPE_NUM},
        {OP_MOD, TYPE_NUM, TYPE_NUM, TYPE_NUM},

        {OP_CONCAT, TYPE_STRING, TYPE_STRING, TYPE_STRING},
        {OP_CONCAT, TYPE_NUM, TYPE_STRING, TYPE_STRING},
        {OP_CONCAT, TYPE_STRING, TYPE_NUM, TYPE_STRING},

        {OP_AND, TYPE_BOOLEAN, TYPE_BOOLEAN, TYPE_BOOLEAN},
        {OP_OR, TYPE_BOOLEAN, TYPE_BOOLEAN, TYPE_BOOLEAN},
        {OP_NEQ, TYPE_BOOLEAN, TYPE_BOOLEAN, TYPE_BOOLEAN},

        {OP_GT, TYPE_NUM, TYPE_NUM, TYPE_BOOLEAN},
        {OP_GE, TYPE_NUM, TYPE_NUM, TYPE_BOOLEAN},
        {OP_LT, TYPE_NUM, TYPE_NUM, TYPE_BOOLEAN},
        {OP_LE, TYPE_NUM, TYPE_NUM, TYPE_BOOLEAN},
        {OP_EQ, TYPE_NUM, TYPE_NUM, TYPE_BOOLEAN},
        {OP_EQ, TYPE_STRING, TYPE_STRING, TYPE_BOOLEAN},
        {OP_LT, TYPE_BOOLEAN, TYPE_BOOLEAN, TYPE_BOOLEAN},
};

int match_op(ValueType first, ValueType second, Operator op)
{
    int rule_count = sizeof(operatorRules) / sizeof(operatorRules[0]);

    for (int i = 0; i < rule_count; i++)
    {
        if (first == operatorRules[i].left_type &&
            second == operatorRules[i].right_type &&
            op == operatorRules[i].op)
        {
            return 1;
        }
    }

    return 0;
}
