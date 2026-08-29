
#include "codegen.h"

static int is_super_type(LLVMUserTypeInfo *parent, LLVMUserTypeInfo *child)
{
    LLVMUserTypeInfo *current = child;

    while (current)
    {
        if (current->id == parent->id)
            return current->id;

        current = current->parent_info;
    }

    return -1;
}

LLVMValueRef codegen_is_type(LLVMVisitor *v, ASTNode *node)
{

    // Generate code to get the instance
    LLVMValueRef instance = codegen_accept(v, node->data.cast_test.exp);


    LLVMDumpType(LLVMTypeOf(instance)); // Muestra el tipo LLVM de 'instance'
    LLVMDumpValue(instance); // Muestra el LLVM IR de 'instance' (ej. @obj_ptr o %0)

    LLVMTypeRef current_instance_llvm_type = LLVMTypeOf(instance);

    // Make sure we have a properly dereferenced instance pointer
    if (LLVMGetTypeKind(current_instance_llvm_type) != LLVMPointerTypeKind)
    {
        return LLVMConstInt(LLVMInt1Type(), 0, 0); // Return false
    }

    LLVMTypeRef element_type_if_ptr_to_ptr = LLVMGetElementType(current_instance_llvm_type);
    if (element_type_if_ptr_to_ptr != NULL && LLVMGetTypeKind(element_type_if_ptr_to_ptr) == LLVMPointerTypeKind)
    {
        LLVMDumpType(element_type_if_ptr_to_ptr);
        instance = LLVMBuildLoad2(v->ctx->builder, element_type_if_ptr_to_ptr, instance, "dereferenced_instance");
        LLVMDumpValue(instance);
        current_instance_llvm_type = LLVMTypeOf(instance); // Update type after load
    }
    

    // Get the target type's AST node (the type we are comparing against, e.g., 'MyClass')
    Type *target_type_ast = node->data.cast_test.type;

    // Handle built-in types (int, double, bool, etc.) - no runtime ID needed for these
    if (is_builtin_type(target_type_ast))
    {
        int eq = type_equals(target_type_ast, node->data.cast_test.exp->return_type);
        return LLVMConstInt(LLVMInt1Type(), eq, 0);
    }

    // --- FOR USER-DEFINED TYPES (CLASSES) ---

    // **THIS IS THE CRITICAL CHANGE:**
    // Get the LLVM struct type for the instance directly from your LLVMUserTypeInfo.
    // Use the `return_type` of the expression to find the correct class information.
    LLVMUserTypeInfo *instance_user_type_info = find_user_type(v->ctx, node->data.cast_test.exp->return_type->name);
    if (!instance_user_type_info)
    {
        return LLVMConstInt(LLVMInt1Type(), 0, 0); // Semantic error, return false
    }
    // This is the correct LLVMTypeRef for the struct (e.g., %MyClass)
    LLVMTypeRef instance_struct_llvm_type = instance_user_type_info->struct_type;

    if (instance_struct_llvm_type == NULL)
    {
        return LLVMConstInt(LLVMInt1Type(), 0, 0); // Semantic error, return false
    }

    LLVMDumpType(instance_struct_llvm_type);

    // Cast the generic 'instance' pointer to the specific struct pointer type.
    // This is crucial for LLVMBuildStructGEP2 to work correctly with opaque 'ptr'.
    LLVMTypeRef expected_instance_ptr_type = LLVMPointerType(instance_struct_llvm_type, 0);
    if (current_instance_llvm_type != expected_instance_ptr_type)
    {
        instance = LLVMBuildPointerCast(v->ctx->builder, instance, expected_instance_ptr_type, "casted_instance_ptr");
        LLVMDumpValue(instance);
    }

    // Get the runtime ID from the instance.
    // Based on your `build_struct_fields` definition:
    // Index 0: VTable Pointer
    // Index 1: Type ID (i32)
    int type_id_field_index = 1; // Correct index for Type ID based on your layout

    // Use the *specific* struct type for GEP, not the generic 'ptr' type.
    LLVMValueRef id_ptr = LLVMBuildStructGEP2(v->ctx->builder, instance_struct_llvm_type, instance, type_id_field_index, "type_id_ptr");

    LLVMValueRef instance_id = LLVMBuildLoad2(v->ctx->builder, v->ctx->i32_type, id_ptr, "instance_type_id");

    LLVMDumpValue(instance_id);

    // Get the target type's ID (the ID of the type we are checking against).
    LLVMUserTypeInfo *target_user_type_info = find_user_type(v->ctx, target_type_ast->name);
    if (!target_user_type_info)
    {
        return LLVMConstInt(LLVMInt1Type(), 0, 0); // Semantic error, return false
    }
    int target_type_id_value = target_user_type_info->id;

    LLVMValueRef target_id_llvm = LLVMConstInt(v->ctx->i32_type, target_type_id_value, 0);

    int super_type_check_result = is_super_type(target_user_type_info, instance_user_type_info);

    // Compare IDs and return the i1 result.
    // LLVMValueRef result = LLVMBuildICmp(v->ctx->builder, LLVMIntEQ, instance_id, target_id_llvm, "type_test");

    LLVMValueRef result = LLVMConstInt(LLVMInt1Type(), (super_type_check_result != -1), 0);

    return result;
}

LLVMValueRef codegen_as_type(LLVMVisitor *v, ASTNode *node)
{
}

LLVMValueRef codegen_base_function(LLVMVisitor *v, ASTNode *node)
{

    const char *method_name = node->name_method_base;
    Type *current_class_type_value = node->data.base_method.current_class_type; // El tipo de la clase actual (ej. B)
    Type *return_type_value = current_class_type_value->parent;                 // El tipo de retorno del método base

    if (!method_name || !current_class_type_value || !return_type_value)
    {
        return NULL;
    }

    // 1. Obtener el puntero 'self' de la función actual
    LLVMValueRef self_ptr = LLVMGetParam(v->current_function, 0); // Asume que 'self' está en el ámbito actual
    if (!self_ptr)
    {
        return NULL;
    }

    // 2. Identificar la clase base LLVMUserTypeInfo
    LLVMUserTypeInfo *current_class_info = find_user_type(v->ctx, current_class_type_value->name);
    if (!current_class_info)
    {
        return NULL;
    }

    LLVMUserTypeInfo *base_class_info = current_class_info->parent_info; // Acceso al parent_type_info
    if (!base_class_info)
    {
        return NULL;
    }

    LLVMMethodInfo *method_info = find_method_info(base_class_info, method_name);

    LLVMTypeRef method_signature_type = method_info->llvm_func_type; // El tipo de función COMPLETO

    unsigned int num_llvm_params = LLVMCountParamTypes(method_signature_type); // Número total de parámetros LLVM (incluyendo 'this')
    LLVMValueRef *call_args = (LLVMValueRef *)malloc(num_llvm_params * sizeof(LLVMValueRef));
    if (!call_args)
    {
        perror(RED "Error en malloc para call_args" RESET);
        exit(EXIT_FAILURE);
    }

    call_args[0] = self_ptr; // El puntero 'this'

    // Procesar los argumentos explícitos del método desde el AST
    unsigned int ast_arg_count = node->data.func_node.arg_count;
    // Comprobar que el número de argumentos del AST coincide con los esperados por LLVM (menos 'this')
    if (ast_arg_count != (num_llvm_params - 1))
    {
        free(call_args);
        return NULL;
    }

    for (unsigned int i = 0; i < ast_arg_count; i++)
    {
        // Generar código para cada argumento del AST
        call_args[i + 1] = codegen_accept(v, node->data.func_node.args[i]);
        if (!call_args[i + 1])
        {
            free(call_args);
            return NULL;
        }
    }

    // 5. Construir la instrucción de llamada LLVM
    //LLVMValueRef call_result = LLVMBuildCall2(v->ctx->builder, method_signature_type, loaded_func_ptr, call_args, num_llvm_params, "method_call_result");
    LLVMValueRef call_result = LLVMBuildCall2(
    v->ctx->builder,
    method_signature_type,
    method_info->llvm_func_value, // ← llamada directa, NO cargar de vtable
    call_args,
    num_llvm_params,
    "method_call_result"
);
    
    
    free(call_args);

    char *ir_string = LLVMPrintValueToString(call_result);

    return call_result;

}