
// visitor_llvm

#ifndef VISITOR_LLVM
#define VISITOR_LLVM

#include "../ast/ast.h"
#include <llvm-c/Core.h>
#include <string.h>

typedef struct LLVMVisitor LLVMVisitor;

// --- Funciones de visita agrupadas por tipo ---
typedef struct {
    LLVMValueRef (*program)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*number)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*string)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*boolean)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*variable)(LLVMVisitor*, ASTNode*);
} LLVM_BasicVisitors;

typedef struct {
    LLVMValueRef (*binary)(LLVMVisitor*, ASTNode*);
    //LLVMValueRef (*unary)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*assignment)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*call_function)(LLVMVisitor*, ASTNode*);
} LLVM_ExpressionVisitors;

typedef struct {
    //LLVMValueRef (*block)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*dec_function)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*let_in)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*conditional)(LLVMVisitor*, ASTNode*);
    LLVMValueRef (*while_loop)(LLVMVisitor*, ASTNode*);
} LLVM_ControlVisitors;

// typedef struct {
//     LLVMValueRef (*type_dec)(Visitor*, ASTNode*);
//     LLVMValueRef (*type_instance)(Visitor*, ASTNode*);
//     LLVMValueRef (*casting)(Visitor*, ASTNode*);
//     LLVMValueRef (*test_type)(Visitor*, ASTNode*);
// } TypeVisitors;

// typedef struct {
//     LLVMValueRef (*attr_getter)(Visitor*, ASTNode*);
//     LLVMValueRef (*attr_setter)(Visitor*, ASTNode*);
//     LLVMValueRef (*base_func)(Visitor*, ASTNode*);
// } AttributeVisitors;

// --- Estructura del visitor ---
struct LLVMVisitor {
    
    // Visitadores
    LLVM_BasicVisitors basic;
    LLVM_ExpressionVisitors expr;
    LLVM_ControlVisitors control;
    // TypeVisitors types;
    // AttributeVisitors attrs;
};

// --- Funciones de utilidades ---


LLVMValueRef codegen_accept(LLVMVisitor* visitor, ASTNode* node);


#endif