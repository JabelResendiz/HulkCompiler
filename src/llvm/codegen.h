


#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm-c/Core.h>
#include "../ast/ast.h"
#include "../visitor/visitor.h"
#include "visitor_llvm.h"

// Funcion para obtnener el tipo LLVM correspondiente a un tipo de lenguaje
LLVMTypeRef get_llvm_type(ValueType type);

//Generar la funcion main en LLVM IR
void codegen_main(ASTNode* node,const char* filename);

//Genera el cuerpo principal del program
LLVMValueRef codegen_program(LLVMVisitor*v, ASTNode* node );

// Funciones especificas
LLVMValueRef codegen_number(LLVMVisitor* v, ASTNode* node);

LLVMValueRef codegen_binary_op(LLVMVisitor* v, ASTNode* node);


LLVMValueRef codegen_assignments(LLVMVisitor* v, ASTNode* node);

LLVMValueRef codegen_let_in(LLVMVisitor* v, ASTNode* node);

LLVMValueRef codegen_variable(LLVMVisitor* v, ASTNode* node);

#endif