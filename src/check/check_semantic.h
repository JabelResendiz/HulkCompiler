
// check.h

#ifndef CHECK_SEMANTIC_H
#define CHECK_SEMANTIC_H
#include <stdlib.h>
#include "../ast/ast.h"
#include "../visitor/visitor.h"
#include "../scope/scope.h"

int make_checker(ASTNode *node);
void visit_program(ASTVisitor *v, ASTNode *node);
void visit_number(ASTVisitor *v, ASTNode *node);
void visit_string(ASTVisitor *v, ASTNode *node);
void visit_boolean(ASTVisitor *v, ASTNode *node);
void visit_variable(ASTVisitor *v, ASTNode *node);
void visit_binary_op(ASTVisitor *v, ASTNode *node);
void visit_block(ASTVisitor* v, ASTNode* node);
void visit_let(ASTVisitor *v, ASTNode *node);
void visit_assignment(ASTVisitor *v, ASTNode *node);
void visit2_call_function(ASTVisitor *v, ASTNode *node);
void visit_call_function(ASTVisitor* v,ASTNode* node,TypeValue* type);
void visit_dec_function(ASTVisitor *v, ASTNode *node);
void check_dec_function(ASTVisitor *v, ASTNode *node, TypeValue *type);
void visit_conditional(ASTVisitor *v, ASTNode *node);
void visit_while_loop(ASTVisitor *v, ASTNode *node);
void visit_type_dec(ASTVisitor *v, ASTNode *node);
void visit_type_instance(ASTVisitor *v, ASTNode *node);
void visit_getter(ASTVisitor *v, ASTNode *node);
void visit_setter(ASTVisitor *v, ASTNode *node);



TypeValue *resolve_node_type(ASTNode *node);
TypeValue **resolve_nodes_type(ASTNode **args, int arg_count);

int try_unify_binary_op(ASTVisitor *v, ASTNode *left,
                        ASTNode *right, Operator op,
                        char *op_name);

int try_unify_operand(ASTVisitor *v,
                      ASTNode *node,
                      TypeValue *type);

int try_unify_conditional(ASTVisitor *v,
                          ASTNode *node,
                          TypeValue *type);

UnifiedIndex *try_unified_type(ASTVisitor *v, 
                               ASTNode **args, 
                               Scope *scope, 
                               int arg_count, 
                               const char *t_name, 
                               EnvItem *item);

UnifiedIndex *try_unified_func(ASTVisitor *v, 
                               ASTNode **args, 
                               Scope *scope, 
                               int arg_count, 
                               const char *f_name, 
                               EnvItem *item);
     // AUXILIAR                          
UnifiedIndex* add_unified_index(UnifiedIndex* list, int index);

int find_rule(Operator op, OperatorRule **rule, int flag, ASTNode *node);

void initialize_program_environment(ASTVisitor *v, ASTNode *node);

void propagate_env_scope(ASTNode *node, ASTNode *child);

EnvItem *find_env_item(Env *env, char *name, int is_type, int var);


#endif
