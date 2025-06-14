
// conditionalc


#include "check_semantic.h"
#include "../scope/unifiedIndex.h"
#include <stdio.h>

static int validate_condition(ASTVisitor* v, ASTNode* condition) {
    
    int unified = try_unify_operand(v, condition, &TYPE_BOOLEAN);
    
    if(unified) {
        accept(v, condition);
    }

    // Hallar el tipo de la condition
    TypeValue* type_condition = resolve_node_type(condition);
    
    if(!compare_types(type_condition, &TYPE_BOOLEAN) && 
       !compare_types(type_condition, &TYPE_ERROR)) {
        fprintf(stderr,"condicion debe ser booleana\n");
        return 0;
    }
    
    return 1;
}

void visit_conditional (ASTVisitor* v, ASTNode* node)

{
    // extraer las partes del conditional
    ASTNode* condition = node->data.conditional.cond;
    ASTNode* body = node->data.conditional.body;
    ASTNode* else_branch = node->data.conditional.else_branch;


    // propagar el scope a los hijos
    propagate_env_scope(node,condition);
    propagate_env_scope(node,body);
    propagate_env_scope(node,else_branch);

    // Visitar la condicion
    accept(v,condition);

    if(!validate_condition(v,condition))
    {
        node->computed_type = &TYPE_ERROR;
        exit(1);
        return ;
    }

    fprintf(stderr,"candela\n");

    // Visitamos el cuerpo
    accept(v,body);
    TypeValue* type_body = resolve_node_type(body);

    fprintf(stderr,"la body type es %s\n",type_body->name);

    
    if(else_branch)
    {
        accept(v,else_branch);
        TypeValue* type_else = resolve_node_type(else_branch);

       // accept(v,body);
       // type_else = resolve_node_type(else_branch);
       // type_body = resolve_node_type(body);

        fprintf(stderr,"la else type es %s\n y la del body es %s\n",type_else->name, type_body->name);

        node->computed_type = compute_lca(type_body,type_else);
        
    }
    else
    {
        //type_body = resolve_node_type(body);
        fprintf(stderr,"el tipo body es %s\n ", type_body->name);

        node->computed_type = type_body;
    }

    fprintf(stderr,"el tipo de node es %s\n",node->computed_type->name);

}

void visit_while_loop(ASTVisitor *v, ASTNode *node)
{

    fprintf(stderr,"estoy en el visit de while\n");
    
    ASTNode *condition = node->data.binary_op.left;
    ASTNode *body = node->data.binary_op.right;

    // Heredar scope
    propagate_env_scope(node,condition);
    propagate_env_scope(node,body);

    // Analizar condicion
    accept(v, condition);

    if(!validate_condition(v,condition))
    {
        node->computed_type = &TYPE_ERROR;
        exit(1);
        return ;
    }
    

    // Analizar cuerpo
    accept(v,body);
    // Tipo del bucle = tipo del cuerpo
    node->computed_type = resolve_node_type(body);

}

// Intentar unificación con BOOLEAN

