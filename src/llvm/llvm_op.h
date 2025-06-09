#ifndef LLVM_OP_H
#define LLVM_OP_H

#include <llvm-c/Core.h>
#include "../ast/ast.h"
#include "visitor_llvm.h"

// Genera código LLVM para operaciones binarias (suma, resta, comparaciones, etc.)
LLVMValueRef generate_binary_operation(LLVMVisitor* v, ASTNode* node);


#endif 