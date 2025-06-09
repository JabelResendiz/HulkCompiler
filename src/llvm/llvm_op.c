#include "llvm_op.h"
#include "init_codegen.h"
#include "codegen.h"
#include "../ast/type.h"
#include <stdio.h>
#include <stdlib.h>

LLVMValueRef handle_object_operation(LLVMValueRef left, LLVMValueRef right, int op) {
    // Obtener el tipo ID de los operandos
    LLVMValueRef left_type_id = LLVMBuildExtractValue(builder, left, 0, "left_type_id");
    LLVMValueRef right_type_id = LLVMBuildExtractValue(builder, right, 0, "right_type_id");
    
    // Crear bloques para el manejo dinámico de tipos
    LLVMBasicBlockRef current_block = LLVMGetInsertBlock(builder);
    LLVMValueRef current_function = LLVMGetBasicBlockParent(current_block);
    
    // Bloque para operación numérica
    LLVMBasicBlockRef number_block = LLVMAppendBasicBlock(current_function, "number_op");
    LLVMBasicBlockRef string_block = LLVMAppendBasicBlock(current_function, "string_op");
    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(current_function, "merge");
    
    // Comparar tipos y bifurcar
    LLVMValueRef is_number = LLVMBuildICmp(builder, LLVMIntEQ, left_type_id, 
        LLVMConstInt(LLVMInt32Type(), 1, 0), "is_number"); // 1 = NUMBER_TYPE_ID
    LLVMBuildCondBr(builder, is_number, number_block, string_block);
    
    // Bloque de operación numérica
    LLVMPositionBuilderAtEnd(builder, number_block);
    LLVMValueRef num_result;
    switch(op) {
        case OP_ADD:
            num_result = LLVMBuildFAdd(builder, left, right, "add");
            break;
        case OP_SUB:
            num_result = LLVMBuildFSub(builder, left, right, "sub");
            break;
        // ... otros casos ...
    }
    LLVMBuildBr(builder, merge_block);
    
    // Bloque de operación de string
    LLVMPositionBuilderAtEnd(builder, string_block);
    LLVMValueRef str_result;
    // Manejar operaciones de string
    LLVMBuildBr(builder, merge_block);
    
    // Bloque de merge
    LLVMPositionBuilderAtEnd(builder, merge_block);
    LLVMValueRef phi = LLVMBuildPhi(builder, LLVMDoubleType(), "result");
    LLVMValueRef incoming_values[] = {num_result, str_result};
    LLVMBasicBlockRef incoming_blocks[] = {number_block, string_block};
    LLVMAddIncoming(phi, incoming_values, incoming_blocks, 2);
    
    return phi;
}

LLVMValueRef codegen_binary_op(LLVMVisitor* v, ASTNode* node) {
    LLVMValueRef L = codegen_accept(v, node->data.binary_op.left);
    LLVMValueRef R = codegen_accept(v, node->data.binary_op.right);

    // Solo realizar operaciones si ambos operandos son números
    if ((node->data.binary_op.left->computed_type == TYPE_NUM) &&
       (node->data.binary_op.right->computed_type == TYPE_NUM)) {

        switch (node->data.binary_op.op) {
            case OP_ADD:
                return LLVMBuildFAdd(builder, L, R, "add_tmp");
            case OP_SUB:
                return LLVMBuildFSub(builder, L, R, "sub_tmp");
            case OP_MULT:
                return LLVMBuildFMul(builder, L, R, "mul_tmp");
            case OP_DIV:
                return LLVMBuildFDiv(builder, L, R, "div_tmp");

            case OP_MOD: {
                LLVMTypeRef fmod_type = LLVMFunctionType(LLVMDoubleType(),
                    (LLVMTypeRef[]){LLVMDoubleType(), LLVMDoubleType()}, 2, 0);
                LLVMValueRef fmod_func = LLVMGetNamedFunction(module, "fmod");
                return LLVMBuildCall2(builder, fmod_type, fmod_func,
                    (LLVMValueRef[]){L, R}, 2, "mod_tmp");
            }

            case OP_POW: {
                LLVMTypeRef pow_type = LLVMFunctionType(LLVMDoubleType(),
                    (LLVMTypeRef[]){LLVMDoubleType(), LLVMDoubleType()}, 2, 0);
                LLVMValueRef pow_func = LLVMGetNamedFunction(module, "pow");
                return LLVMBuildCall2(builder, pow_type, pow_func,
                    (LLVMValueRef[]){L, R}, 2, "pow_tmp");
            }

            case OP_EQ:
                return LLVMBuildFCmp(builder, LLVMRealOEQ, L, R, "eq_tmp");
            case OP_GT:
                return LLVMBuildFCmp(builder, LLVMRealOGT, L, R, "gt_tmp");
            case OP_GE:
                return LLVMBuildFCmp(builder, LLVMRealOGE, L, R, "ge_tmp");
            case OP_LT:
                return LLVMBuildFCmp(builder, LLVMRealOLT, L, R, "lt_tmp");
            case OP_LE:
                return LLVMBuildFCmp(builder, LLVMRealOLE, L, R, "le_tmp");

            default:
                break;
        }
    }

    // Si no es número o no es operación válida, abortar
    exit(1);
}
