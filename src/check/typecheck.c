

//typecheck.c

#include "check_semantic.h"
#include "../ast/type.h"


void visit_program(ASTVisitor* v, ASTNode* node)
{

    for(int i =0 ; i <node->data.program.count;i++)
    {
        ASTNode* child = node->data.program.statements[i];
        child->scope->parent = node->scope;
        accept ( v,child);

        
    }

}


void visit_number(ASTVisitor* v, ASTNode* node){}

void visit_boolean(ASTVisitor* v,ASTNode* node){}

void visit_binary_op(ASTVisitor * v, ASTNode* node)
{
    ASTNode *left = node->data.binary_op.left;
    ASTNode *right = node->data.binary_op.right;
    
    left->scope->parent = node->scope;
    right->scope->parent = node->scope;


    accept(v,left);
    accept(v,right);

    ValueType type_left = left->computed_type;
    ValueType type_right = right->computed_type;

    if(!match_op(type_left,type_right,node->data.binary_op.op) )
    {
        fprintf(stderr,"Error no son del tipo especificado");
    }


}