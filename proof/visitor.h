// visitor.h
#ifndef VISITOR_H
#define VISITOR_H

#include "env.h"
#include "types.h"

struct ASTNode;
typedef struct ASTNode ASTNode;


typedef struct ASTVisitor ASTVisitor;


typedef struct ASTVisitor {
    
    ValueType (*visit_num)(ASTVisitor*, ASTNode*);
    ValueType (*visit_string)(ASTVisitor*, ASTNode*);
    ValueType (*visit_var)(ASTVisitor*, ASTNode*);
    ValueType (*visit_add)(ASTVisitor*, ASTNode*);
    ValueType (*visit_sub)(ASTVisitor*, ASTNode*);
    ValueType (*visit_mul)(ASTVisitor*, ASTNode*);
    ValueType (*visit_div)(ASTVisitor*, ASTNode*);
    ValueType (*visit_concat)(ASTVisitor*, ASTNode*);
    ValueType (*visit_print)(ASTVisitor*, ASTNode*);
    ValueType (*visit_if)(ASTVisitor*, ASTNode*);
    ValueType (*visit_let)(ASTVisitor*, ASTNode*);
    ValueType (*visit_seq)(ASTVisitor*, ASTNode*);

    Env* env;
    void(*log_error)(const char* msg);

}ASTVisitor;


ValueType visit_num(ASTVisitor* visitor, ASTNode* node);
ValueType visit_string(ASTVisitor* visitor, ASTNode* node);
ValueType visit_var(ASTVisitor* visitor, ASTNode* node);
ValueType visit_add(ASTVisitor* visitor, ASTNode* node);
ValueType visit_sub(ASTVisitor* visitor, ASTNode* node);
ValueType visit_mul(ASTVisitor* visitor, ASTNode* node);
ValueType visit_div(ASTVisitor* visitor, ASTNode* node);
ValueType visit_concat(ASTVisitor* visitor, ASTNode* node);
ValueType visit_print(ASTVisitor* visitor, ASTNode* node);
ValueType visit_if(ASTVisitor* visitor, ASTNode* node);
ValueType visit_let(ASTVisitor* visitor, ASTNode* node);
ValueType visit_seq(ASTVisitor* visitor, ASTNode* node);


#endif