
// codegen.h

#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>

typedef struct 
{
    LLVMContextRef context;
    LLVMModuleRef module;
    LLVMBuilderRef builder;
    LLVMValueRef current_function;
    LLVMPassManagerRef pass_manager;
}CodegenContext;


void codegen_init(CodegenContext* ctx,const char* module_name);
void codegen_cleanup(CodegenContext* ctx);

void codegen_generate(CodegenContext* ctx, ASTNode* root);

LLVMValueRef codegen_expr(CodegenContext* ctx,ASTNode* node);
LLVMValueRef codegen_let(CodegenContext* ctx,ASTNode* node);
LLVMValueRef codegen_if(CodegenContext* ctx,ASTNode* node);
LLVMValueRef codegen_print(CodegenContext* ctx,ASTNode* node);


#endif