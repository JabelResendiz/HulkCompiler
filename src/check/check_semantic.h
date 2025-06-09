
//check.h

#ifndef CHECK_SEMANTIC_H
#define CHECK_SEMANTIC_H
#include <stdlib.h>
#include "../ast/ast.h"
#include "../visitor/visitor.h"

void make_checker(ASTNode* node);
void visit_program(ASTVisitor* v, ASTNode* node);
void visit_number(ASTVisitor* v, ASTNode* node);
// void visit_string(ASTVisitor* v, ASTNode* node);
void visit_boolean(ASTVisitor* v, ASTNode* node);
void visit_variable(ASTVisitor* v, ASTNode* node);
void visit_binary_op(ASTVisitor* v, ASTNode* node);
// void visit_block(ASTVisitor* v, ASTNode* node);
void visit_let(ASTVisitor* v, ASTNode* node);
// void visit_conditional(ASTVisitor* v, ASTNode* node);
void visit_assignment(ASTVisitor* v, ASTNode* node);


ValueType resolve_node_type(ASTNode* node);

#endif
