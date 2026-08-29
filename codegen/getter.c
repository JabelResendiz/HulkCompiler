
#include "codegen.h"

// Colores para fprintf (si los tienes definidos en otro lugar)
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

// IMPLEMENTACIÓN DE codegen_attr_getter
LLVMValueRef codegen_attr_getter(LLVMVisitor *v, ASTNode *node)
{
    // 1.Generate code for the object expresion (self)
    // This should result in an LLVmValueRef that is a pointer to the object instance.

    // const char* object_instance_ptr = node->data.op_node.left->return_type->name;

    LLVMValueRef object_instance_ptr = codegen_accept(v, node->data.op_node.left);

    if (!object_instance_ptr)
    {
        return NULL;
    }

    // 2. Get the type information for the object
    // Assuming node->data.op_node.left->return_type holds the Type* for the object
    const char *object_type_name = node->data.op_node.left->return_type->name;
    LLVMUserTypeInfo *type_info = find_user_type(v->ctx, object_type_name);
    if (!type_info)
    {
        return NULL;
    }
    
    // 3. Get the attribute name and find its index within the struct
    const char *attribute_name = node->data.op_node.right->data.variable_name; // Assuming 'variable_name' for attributes
    int attribute_index = find_field_index(type_info, attribute_name);

    // Remember: Your struct starts with type_id (0) and vtable_ptr (1).
    // So, actual data members start from index 2.
    // Your find_field_index must account for this offset.
    // If find_field_index returns 0 for 'x' and 1 for 'y' (relative to data members),
    // then the actual LLVM struct index will be 2 for 'x', 3 for 'y'.
    // Let's assume find_field_index already returns the correct LLVM struct index (2, 3, etc.).
    if (attribute_index == -1)
    { // Assuming -1 means not found
        return NULL;
    }
    
    // 4. Get the LLVM Type of the member we are trying to access.
    // You'd need to extend LLVMTypeMemberInfo to include the LLVMTypeRef of the member.
    // Alternatively, if your find_field_index function can also return the type.
    LLVMTypeMemberInfo *member_info = find_member_info(type_info, attribute_name);

    if (!member_info)
    {
        return NULL;
    }

    LLVMTypeRef attribute_llvm_type = member_info->llvm_type;
    if (!attribute_llvm_type)
    {
        return NULL;
    }
    
    // 5. Generate the Get Element Pointer (GEP) instruction
    // This gives us a pointer to the specific attribute within the object instance.
    LLVMValueRef attribute_ptr = LLVMBuildStructGEP2(
        v->ctx->builder,
        type_info->struct_type, // The struct type (e.g., %A)
        object_instance_ptr,    // Pointer to the object instance (e.g., %self_ptr)
        attribute_index,        // The index of the member (e.g., 2 for 'x', 3 for 'y')
        attribute_name          // Name for the instruction
    );
    
    // 6. Load the value from the attribute's memory address
    LLVMValueRef loaded_value = LLVMBuildLoad2(
        v->ctx->builder,
        attribute_llvm_type, // The actual LLVMTypeRef of the attribute (e.g., i32, double)
        attribute_ptr,       // Pointer to the attribute
        "loaded_attribute_val");
    
    return loaded_value;
}

LLVMValueRef codegen_method_getter(LLVMVisitor *v, ASTNode *node)
{

    // 1. Generar el código para la expresión del objeto (por ejemplo, cargar la variable 'miObjeto')
    // Esto debe devolver un LLVMValueRef que es un puntero a la instancia del objeto.
    LLVMValueRef object_instance_ptr = codegen_accept(v, node->data.op_node.left);
    if (!object_instance_ptr)
    {
        return NULL;
    }

    // Asegúrate de que el tipo de retorno de la expresión del objeto esté establecido en el AST
    // (ej. si 'miObjeto' es de tipo 'ClaseA', entonces node->data.op_node.left->return_type->name debería ser "ClaseA")
    const char *object_type_name = node->data.op_node.left->return_type->name;

    const char *object_dynamic_name = node->data.op_node.left->dynamic_type->name;

    LLVMUserTypeInfo *type_info = find_user_type(v->ctx, object_type_name);
    if (!type_info)
    {
        return NULL;
    }

    LLVMUserTypeInfo *type_dynamic_info = find_user_type(v->ctx, object_dynamic_name);
    if (!type_dynamic_info)
    {
        return NULL;
    }

    // El nombre del método se extrae de la parte derecha (la llamada al método)
    const char *method_name = node->data.op_node.right->data.func_node.name;

    const char *real_name_method = NULL;

    LLVMMethodInfo *method_info = NULL;
    LLVMValueRef loaded_func_ptr = NULL;

    if (strcmp(object_type_name, object_dynamic_name))
    {
        const char *base_function = delete_underscore_from_str(method_name, type_dynamic_info->name);

        real_name_method = concat_str_with_underscore(type_info->name, base_function);

        free(base_function);

        method_info = find_method_info(type_info, real_name_method);

        char vtable_global_name[256];
        snprintf(vtable_global_name, sizeof(vtable_global_name), "%s_vtable_instance", object_type_name); // e.g., "_Dog_vtable_constant"
        
        LLVMValueRef static_type_vtable_global = LLVMGetNamedGlobal(v->ctx->module, vtable_global_name);

        
        LLVMValueRef func_ptr_addr = LLVMBuildStructGEP2(
            v->ctx->builder,
            type_info->vtable_struct_type, // Use the static type's vtable struct type
            static_type_vtable_global,     // This is the global vtable constant
            method_info->vtable_index,     // Index of the method in the vtable
            "static_func_ptr_slot_addr");

        loaded_func_ptr = LLVMBuildLoad2(v->ctx->builder, LLVMPointerType(method_info->llvm_func_type, 0), func_ptr_addr, "loaded_static_func_ptr");
        LLVMSetAlignment(loaded_func_ptr, 8);
    }

    else
    {
        method_info = find_method_info(type_dynamic_info, method_name);

        LLVMValueRef vtable_ptr_field_addr = LLVMBuildStructGEP2(v->ctx->builder, type_info->struct_type, object_instance_ptr, 1, "vtable_ptr_addr");

        LLVMValueRef vtable_ptr_loaded = LLVMBuildLoad2(v->ctx->builder, type_info->vtable_ptr_type, vtable_ptr_field_addr, "vtable_ptr_loaded");
        LLVMSetAlignment(vtable_ptr_loaded, 8); // Adjust alignment if necessary

        LLVMValueRef func_ptr_addr = LLVMBuildStructGEP2(v->ctx->builder, type_info->vtable_struct_type, vtable_ptr_loaded, method_info->vtable_index, "func_ptr_slot_addr");
        loaded_func_ptr = LLVMBuildLoad2(v->ctx->builder, LLVMPointerType(method_info->llvm_func_type, 0), func_ptr_addr, "loaded_dynamic_func_ptr");
        LLVMSetAlignment(loaded_func_ptr, 8);
    }

    LLVMTypeRef method_signature_type = method_info->llvm_func_type; // El tipo de función COMPLETO
    // LLVMValueRef func_ptr_addr = LLVMBuildStructGEP2(v->ctx->builder, type_info->vtable_struct_type, vtable_ptr_loaded, method_info->vtable_index, "func_ptr_slot_addr");
    // LLVMValueRef loaded_func_ptr = LLVMBuildLoad2(v->ctx->builder, LLVMPointerType(method_signature_type, 0), func_ptr_addr, "loaded_func_ptr");
    // LLVMSetAlignment(loaded_func_ptr, 8); // Ajusta la alineación si es necesario

    // 4. Preparar los argumentos para la llamada
    // El primer argumento es siempre el puntero 'this' (la instancia del objeto)
    unsigned int num_llvm_params = LLVMCountParamTypes(method_signature_type); // Número total de parámetros LLVM (incluyendo 'this')
    LLVMValueRef *call_args = (LLVMValueRef *)malloc(num_llvm_params * sizeof(LLVMValueRef));
    if (!call_args)
    {
        perror(RED "Error en malloc para call_args" RESET);
        exit(EXIT_FAILURE);
    }

    call_args[0] = object_instance_ptr; // El puntero 'this'

    // Procesar los argumentos explícitos del método desde el AST
    unsigned int ast_arg_count = node->data.op_node.right->data.func_node.arg_count;
    // Comprobar que el número de argumentos del AST coincide con los esperados por LLVM (menos 'this')
    if (ast_arg_count != (num_llvm_params - 1))
    {
        
        free(call_args);
        return NULL;
    }

    for (unsigned int i = 0; i < ast_arg_count; i++)
    {
        // Generar código para cada argumento del AST
        call_args[i + 1] = codegen_accept(v, node->data.op_node.right->data.func_node.args[i]);
        if (!call_args[i + 1])
        {
            free(call_args);
            return NULL;
        }
    }

    // 5. Construir la instrucción de llamada LLVM
    LLVMValueRef call_result = LLVMBuildCall2(v->ctx->builder, method_signature_type, loaded_func_ptr, call_args, num_llvm_params, "method_call_result");
    free(call_args);

    char *ir_string = LLVMPrintValueToString(call_result);

    return call_result; // Devuelve el resultado de la llamada al método
}