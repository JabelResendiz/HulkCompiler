

#include "typecheck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void default_log_error(const char* msg)
{
    fprintf(stderr,"Type Error:%s\n",msg);
}

ValueType visit_num(ASTVisitor* v,ASTNode* node)
{
    return node->computed_type = TYPE_INT;
}

ValueType visit_string( ASTVisitor* v, ASTNode* node) {
    return node->computed_type = TYPE_STRING;
}

ValueType visit_var(ASTVisitor* v, ASTNode* node)
{
    ASTNode* val = env_lookup(v->env,node->var_name);

    if(!val)
    {
        v->log_error("undeclared variable");
        return node->computed_type = TYPE_UNKNOWN;
    }

    return node->computed_type = val->computed_type;
}

ValueType visit_add(ASTVisitor* v, ASTNode* node)
{
    ValueType left = node->left->accept(node->left,v);
    ValueType right = node->right->accept(node->right,v);

    if(left != TYPE_INT || right != TYPE_INT)
    {
        v->log_error("ADD: Operands must be integers");
        return TYPE_UNKNOWN;
    }

    return node->computed_type = TYPE_INT;
}

ValueType visit_sub(ASTVisitor* v, ASTNode* node)
{
    ValueType left = node->left->accept(node->left,v);
    ValueType right = node->right->accept(node->right,v);

    if(left != TYPE_INT || right != TYPE_INT)
    {
        v->log_error("SUB: Operands must be integers");
        return TYPE_UNKNOWN;
    }

    return node->computed_type = TYPE_INT;
}


ValueType visit_mul(ASTVisitor* v, ASTNode* node)
{
    ValueType left = node->left->accept(node->left,v);
    ValueType right = node->right->accept(node->right,v);

    if(left != TYPE_INT || right != TYPE_INT)
    {
        v->log_error("MULT: Operands must be integers");
        return TYPE_UNKNOWN;
    }

    return node->computed_type = TYPE_INT;
}


ValueType visit_div(ASTVisitor* v, ASTNode* node)
{
    ValueType left = node->left->accept(node->left,v);
    ValueType right = node->right->accept(node->right,v);

    if(left != TYPE_INT || right != TYPE_INT)
    {
        v->log_error("DIV: Operands must be integers");
        return TYPE_UNKNOWN;
    }

    return node->computed_type = TYPE_INT;
}


ValueType visit_concat(ASTVisitor* v, ASTNode* node)
{
    ValueType left = node->left->accept(node->left,v);
    ValueType right = node->right->accept(node->right,v);

    if(left != TYPE_STRING || right != TYPE_STRING)
    {
        v->log_error("CONCAT: Operands must be strings");
        return TYPE_UNKNOWN;
    }

    return node->computed_type = TYPE_STRING;
}


ValueType visit_print(ASTVisitor* v, ASTNode* node)
{
    node->left->accept(node->left,v);
    return node->computed_type = TYPE_UNKNOWN;
}

ValueType visit_seq(ASTVisitor* v, ASTNode* node)
{
    node->left->accept(node->left,v);
    return node->computed_type = node->right->accept(node->right,v);
}

ValueType visit_let(ASTVisitor* v, ASTNode* node)
{
    Env* local = create_env(v->env);
    VarBinding* b = node->bindings;
    while(b)
    {
        ValueType t = b->value->accept(b->value,v);
        b->value->computed_type = t;
        env_add(local,b->name,b->value);
        b = b->next;
    }

    ASTVisitor inner = *v;
    inner.env = local;
    ValueType result = node->left->accept(node->left,&inner);
    free_env(local);
    return node->computed_type = result;
}

ValueType visit_if( ASTVisitor* v, ASTNode* node) {
    ValueType cond = node->condition->accept(node->condition, v);
    ValueType t_branch = node->left->accept(node->left, v);
    ValueType e_branch = node->else_branch->accept(node->else_branch, v);
    if (t_branch != e_branch) {
        v->log_error("IF: Branches must match in type");
        return TYPE_UNKNOWN;
    }
    return node->computed_type = t_branch;
}


// Visitor concreto
ASTVisitor make_typechecker(Env* env, void (*log)(const char*)) {
    if (!log) log = default_log_error;
    return (ASTVisitor){
        .visit_num = visit_num,
        .visit_string = visit_string,
        .visit_var = visit_var,
        .visit_add = visit_add,
        .visit_sub = visit_add,
        .visit_mul = visit_add,
        .visit_div = visit_add,
        .visit_concat = visit_concat,
        .visit_print = visit_print,
        .visit_if = visit_if,
        .visit_let = visit_let,
        .visit_seq = visit_seq,
        .env = env,
        .log_error = log
    };
}

