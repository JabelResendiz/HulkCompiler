

// variable_semantic.c
#include "check_semantic.h"
#include "../ast/keyword.h"

void visit_let(ASTVisitor* v, ASTNode* node)
{
    ASTNode** bindings = node->data.func_node.args;
    ASTNode* body = node->data.func_node.body;

    body->scope->parent = node->scope;
    
    for(int i=0;i<node->data.func_node.arg_count;i++)
    {
        bindings[i]->scope->parent = node->scope;
        accept(v,bindings[i]);
    }
    

    accept(v,body);

    node->computed_type = resolve_node_type(body);

}
void visit_assignment(ASTVisitor* v, ASTNode* node)
{
    ASTNode* var_node = node->data.binary_op.left;
    ASTNode* val_node = node->data.binary_op.right;

    if(match_keyword(var_node->data.var_name))
    {
        printf( "Keyword '%s' can not be used as a variable name. Line: %d.",var_node->data.var_name,node->line);
        exit(1);
    }
    
    var_node->scope->parent = node->scope;
    val_node->scope->parent = node->scope;

    
    accept(v,val_node);
    
    TypeValue* inferred_type = resolve_node_type(val_node);


    scope_add_symbol(node->scope,var_node->data.var_name,inferred_type,val_node);

    var_node->computed_type = inferred_type;
    node->computed_type = inferred_type;

}


void visit_variable(ASTVisitor* v, ASTNode* node)
{
    // comprobar si la variable esta en el scope 

    Symbol * sym = scope_lookup(node->scope,node->data.var_name);

    if(sym)
    {
        node->computed_type = sym->type;
        return ;
    }

    exit(1);

}
