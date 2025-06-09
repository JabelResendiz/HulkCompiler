

#ifndef LLVM_SCOPE_H
#define LLVM_SCOPE_H

#include <llvm-c/Core.h>

typedef struct ScopeVarEntry
{
    char* name;
    LLVMValueRef alloca;
    struct ScopeVarEntry* next;
}ScopeVarEntry;


typedef struct LLVMScope
{
    ScopeVarEntry* entries;
    struct LLVMScope* parent;
}LLVMScope;


void print_scope();
void push_scope(void);
void pop_scope(void);
LLVMValueRef lookup_variable(const char* name);
void declare_variable(const char* name,LLVMValueRef alloca);
void update_variable(const char* name,LLVMValueRef new_alloca);


#endif