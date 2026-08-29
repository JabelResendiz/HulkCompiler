

#include "codegen.h"
#include "init_codegen.h"
#include "visitor_llvm.h"
#include "../scope/llvm_scope.h"
#include <stdio.h>
#include <string.h>
#include "../type/type.h"
#include "types.h"

// Genera el LLVM IR a partir de un AST
void compile_to_llvm(ASTNode *ast, const char *filename)
{

    // Inicializar LLVM (Targets, Printers, etc. - solo una vez al inicio de la compilación)
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();
    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmPrinters();
    LLVMInitializeAllAsmParsers();

    LLVMCoreContext *ctx = llvm_core_context_create(); // Crea e inicializa el contexto LLVM
    LLVMVisitor visitor = {.ctx = ctx};                // Inicializa el visitor con el contexto

    // Configura las funciones de codegen en el visitor
    visitor.basic.program = codegen_program;
    visitor.basic.number = codegen_number;
    visitor.basic.string = codegen_string;
    visitor.basic.boolean = codegen_boolean;
    visitor.basic.variable = codegen_variable;
    visitor.expr.binary = codegen_binary_op;
    visitor.expr.assignment = codegen_assignments;
    visitor.expr.call_function = codegen_call_function;
    visitor.control.block = codegen_block;
    visitor.control.dec_function = codegen_dec_function;
    visitor.control.let_in = codegen_let_in;
    visitor.control.conditional = codegen_conditional;
    visitor.control.while_loop = codegen_while;
    visitor.types.type_dec = codegen_type_dec; // Placeholder, make_body_type_dec hace el trabajo
    visitor.types.type_instance = codegen_type_instance;
    visitor.attrs.attr_getter = codegen_attr_getter;
    visitor.attrs.attr_setter = codegen_attr_setter;
    visitor.attrs.method_getter = codegen_method_getter;
    // visitor.types.casting = codegen_as_type;
    visitor.types.test_type = codegen_is_type;
    visitor.attrs.base_func = codegen_base_function;

    // Declara funciones built-in (malloc, printf, etc.)
    llvm_declare_builtins(ctx);

    // build_vtable_table(&visitor, ast);

    // FASE 1: Recolector Declaraciones de Tipos (solo los nombres de struct y vtables)
    find_type_dec(&visitor, ast);

    // FASE 2: Definir cuerpos de tipos y vtables, declarar metodos llvm
    // Esto se hace iterando sobre la lista de user_types, no sobre el AST completo de nuevo.
    LLVMUserTypeInfo *current_user_type = ctx->user_types;

    while (current_user_type)
    {

        for (int i = 0; i < current_user_type->num_methods_virtual; i++)
        {
            codegen_dec_method(&visitor, current_user_type->methods[i]->node, current_user_type);
        }

        current_user_type = current_user_type->next;
    }

    // FASE 3: Registrar las firmas de funciones "libres" (no métodos de clase)
    find_function_dec(&visitor, ast);

    // FASE 4: Generar los cuerpos de las funciones (incluyendo métodos de clase)

    // // Generar cuerpos de MÉTODOS DE CLASE
    // LLVMUserTypeInfo *current_user_type_info_phase4 = ctx->user_types; // Reinicia el puntero
    // while(current_user_type_info_phase4 != NULL) {
    //     for(int i = 0; i < current_user_type_info_phase4->num_methods_virtual; i++) {
    //         codegen_method_body(&visitor, // Pasar el visitor
    //                             current_user_type_info_phase4,
    //                             current_user_type_info_phase4->method_decl_nodes_ast[i],
    //                             current_user_type_info_phase4->method_llvm_funcs[i]);
    //     }
    //     current_user_type_info_phase4 = current_user_type_info_phase4->next;
    // }

    // Generar cuerpos de funciones "libres" o no-métodos
    make_body_function_dec(&visitor, ast);

    // Create scope for main function
    push_scope();

    // Crea la función main con retorno i32 0
    LLVMTypeRef main_type = LLVMFunctionType(ctx->i32_type, NULL, 0, 0);
    LLVMValueRef main_func = LLVMAddFunction(ctx->module, "main", main_type);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(ctx->context, main_func, "entry");

    // Posiciona el builder en el bloque de entrada de main
    LLVMPositionBuilderAtEnd(ctx->builder, entry);

    if (ast)
    {
        // Llama a codegen para recorrer el AST completo y generar el código principal de main
        // Esto incluirá las llamadas a codegen_type_instance si ocurren en el programa principal.
        codegen_accept(&visitor, ast);
    }

    // Asegura que el bloque de entrada de main termine con un retorno
    LLVMBasicBlockRef current_block_in_main = LLVMGetInsertBlock(ctx->builder);
    if (!LLVMGetBasicBlockTerminator(current_block_in_main))
    {
        LLVMBuildRet(ctx->builder, LLVMConstInt(ctx->i32_type, 0, 0));
    }

    // Pop scope for main function
    pop_scope();

    // Escribe en el archivo .ll
    char *error = NULL;


    if (LLVMPrintModuleToFile(ctx->module, filename, &error))
    {
        LLVMDisposeMessage(error);
        exit(1);
    }

    // Libera recursos
    free_llvm_core_context(ctx);
}

LLVMValueRef codegen_program(LLVMVisitor *v, ASTNode *node)
{
    push_scope();
    LLVMValueRef last = NULL;

    for (int i = 0; i < node->data.program_node.count; i++)
    {
        ASTNode *stmt = node->data.program_node.statements[i];
        if (stmt->type != NODE_FUNC_DEC)
        {
            last = codegen_accept(v, stmt);
        }
    }

    pop_scope();
    return last ? last : LLVMConstInt(LLVMInt32Type(), 0, 0);
}

// FASE 0: find_type_dec (Solo recolecta nombres de tipos y los declara globalmente en LLVM)

void find_function_dec(LLVMVisitor *visitor, ASTNode *node)
{

    if (!node)
        return;

    // Si es una declaración de función, procesarla y buscar dentro de su cuerpo
    if (node->type == NODE_FUNC_DEC)
    {
        // codegen_dec_function(v,node);

        make_function_dec(visitor, node);
        // Buscar funciones anidadas dentro del cuerpo de la función
        find_function_dec(visitor, node->data.func_node.body);
        return;
    }

    // Recursivamente buscar en los diferentes tipos de nodos
    switch (node->type)
    {
    case NODE_PROGRAM:
    case NODE_BLOCK:
        for (int i = 0; i < node->data.program_node.count; i++)
        {
            find_function_dec(visitor, node->data.program_node.statements[i]);
        }
        break;

    case NODE_LET_IN:
        // Buscar en las declaraciones
        for (int i = 0; i < node->data.func_node.arg_count; i++)
        {
            if (node->data.func_node.args[i]->type == NODE_ASSIGNMENT)
            {
                find_function_dec(visitor, node->data.func_node.args[i]->data.op_node.right);
            }
        }
        // Buscar en el cuerpo
        find_function_dec(visitor, node->data.func_node.body);
        break;
    }
}

LLVMValueRef make_function_dec(LLVMVisitor *v, ASTNode *node)
{

    const char *name = node->data.func_node.name;
    Type *return_type = node->data.func_node.body->return_type;
    ASTNode **params = node->data.func_node.args;
    int param_count = node->data.func_node.arg_count;
    LLVMTypeRef llvm_return_type = type_to_llvm(v->ctx, return_type);

    // Obtener tipos de parámetros
    LLVMTypeRef *param_types = malloc(param_count * sizeof(LLVMTypeRef));
    for (int i = 0; i < param_count; i++)
    {
        param_types[i] = type_to_llvm(v->ctx, params[i]->return_type);
    }


    // Crear y registrar la firma de la función
    LLVMTypeRef func_type = LLVMFunctionType(
        llvm_return_type,
        param_types,
        param_count,
        0);


    LLVMValueRef func = LLVMAddFunction(v->ctx->module, name, func_type);
    free(param_types);
    return func;
}

void make_body_function_dec(LLVMVisitor *visitor, ASTNode *node)
{
    if (!node)
        return;

    // Si es una declaración de función, generar su cuerpo y procesar funciones anidadas
    if (node->type == NODE_FUNC_DEC)
    {
        codegen_accept(visitor, node);
        // Procesar funciones anidadas en el cuerpo de la función
        make_body_function_dec(visitor, node->data.func_node.body);
        return;
    }

    // Recursivamente procesar los diferentes tipos de nodos
    switch (node->type)
    {
    case NODE_PROGRAM:
    case NODE_BLOCK:
        for (int i = 0; i < node->data.program_node.count; i++)
        {
            make_body_function_dec(visitor, node->data.program_node.statements[i]);
        }
        break;

    case NODE_LET_IN:
        // Procesar declaraciones
        for (int i = 0; i < node->data.func_node.arg_count; i++)
        {
            if (node->data.func_node.args[i]->type == NODE_ASSIGNMENT)
            {
                make_body_function_dec(visitor, node->data.func_node.args[i]->data.op_node.right);
            }
        }
        // Procesar el cuerpo
        make_body_function_dec(visitor, node->data.func_node.body);
        break;
    }

}

#pragma region TYPES

void build_vtable_table(LLVMVisitor *v, ASTNode *node)
{

    const char *type_name = node->data.type_node.name;
    LLVMUserTypeInfo *parent_info = NULL;
    int parent_id = -1;

    if (strcmp(node->data.type_node.parent_name, ""))
    {
        parent_info = find_user_type(v->ctx, node->data.type_node.parent_name);
        if (!parent_info)
        {
            exit(EXIT_FAILURE);
        }
        parent_id = parent_info->id;
    }

    LLVMUserTypeInfo *type_info = malloc(sizeof(LLVMUserTypeInfo));
    type_info->id = v->ctx->user_types ? (v->ctx->user_types->id + 1) : 0;
    type_info->name = strdup(type_name);
    type_info->parent_info = parent_info;

    //add_runtime_type_entry(v->ctx, type_info->id, parent_id);

    // numero de metodos y de asignaciones de mi tipo
    int function_context = 0;
    int assigments_context = 0;

    for (int i = 0; i < node->data.type_node.def_count; i++)
    {
        if (node->data.type_node.definitions[i]->type == NODE_FUNC_DEC)
        {
            function_context++;
        }
        if (node->data.type_node.definitions[i]->type == NODE_ASSIGNMENT)
        {
            assigments_context++;
        }
    }

    int parent_assigments = parent_info ? parent_info->num_data_members : 0;
    int parent_methods = parent_info ? parent_info->num_methods_virtual : 0;

    // Contar la cantidad de metodos sobreescritos de cada uno
    int overriden_methods = 0;

    for (int i = 0; parent_info && i < node->data.type_node.def_count; i++)
    {
        ASTNode *child = node->data.type_node.definitions[i];

        if (child->type == NODE_FUNC_DEC)
        {

            char *base_name = delete_underscore_from_str(child->data.func_node.name, type_name);

            for (int j = 0; j < parent_info->num_methods_virtual; j++)
            {
                char *parent_method_name = delete_underscore_from_str(parent_info->methods[j]->name, parent_info->name);

                if (strcmp(parent_method_name, base_name) == 0)
                {
                    child->data.func_node.flag_overriden = j + 1;
                    overriden_methods++;
                    free(parent_method_name);
                    break;
                }

                free(parent_method_name);
            }

            free(base_name);
        }
    }

    char vtable_name[256];
    snprintf(vtable_name, sizeof(vtable_name), "%s_vtable", type_name);

    LLVMTypeRef vtable_struct_type = LLVMStructCreateNamed(v->ctx->context, vtable_name);
    LLVMTypeRef class_struct_type = LLVMStructCreateNamed(v->ctx->context, type_name);

    type_info->struct_type = class_struct_type;
    type_info->vtable_struct_type = vtable_struct_type;
    type_info->num_data_members = assigments_context + parent_assigments;
    type_info->num_methods_virtual = function_context + parent_methods - overriden_methods;

    type_info->methods = (LLVMMethodInfo **)malloc(type_info->num_methods_virtual * sizeof(LLVMMethodInfo *));
    type_info->members = (LLVMTypeMemberInfo **)malloc(type_info->num_data_members * sizeof(LLVMTypeMemberInfo *));

    type_info->next = v->ctx->user_types;
    v->ctx->user_types = type_info;

    LLVMTypeRef *vtable_slot_ptr_types = (LLVMTypeRef *)malloc(type_info->num_methods_virtual * sizeof(LLVMTypeRef));
    LLVMTypeRef *vtable_slot_types = (LLVMTypeRef *)malloc(type_info->num_methods_virtual * sizeof(LLVMTypeRef));


    for (int i = 0; i < parent_methods; i++)
    {
        vtable_slot_ptr_types[i] = parent_info->vtable_slot_ptr_types[i];
        vtable_slot_types[i] = parent_info->vtable_slot_types[i];
    }

    for (int i = 0, j = parent_methods; i < node->data.type_node.def_count; i++)
    {
        ASTNode *child = node->data.type_node.definitions[i];

        if (child->type == NODE_FUNC_DEC && child->data.func_node.flag_overriden == 0)
        {
            LLVMValueRef llvm_ret_type = type_to_llvm(v->ctx, child->data.func_node.body->return_type);

            // 1. Calcular le numero total de parametros LLVM : 'this' + parametros explicito
            int num_explicit_params = child->data.func_node.arg_count;
            int total_llvm_params = 1 + num_explicit_params;

            // 2. Asignar memoria para el array de tipo de paramtros LLVM
            LLVMTypeRef *llvm_param_types = (LLVMTypeRef *)malloc(total_llvm_params * sizeof(LLVMTypeRef));

            if (!llvm_param_types)
            {
                perror("Error en malloc para llvm_param_types");
                exit(EXIT_FAILURE);
            }

            // 3. El primer paramtros siempre es el puntero 'this'
            llvm_param_types[0] = LLVMPointerType(class_struct_type, 0);

            // 4. Agregar los tipos de los apramtros explcitios
            for (int k = 0; k < num_explicit_params; k++)
            {
                llvm_param_types[k + 1] = type_to_llvm(v->ctx, child->data.func_node.args[k]->return_type);
            }

            // 5. Crear el tipo de la funcion LLVM con el array de parametros correctos
            LLVMTypeRef method_func_type = LLVMFunctionType(llvm_ret_type, llvm_param_types, total_llvm_params, 0);

            vtable_slot_types[j] = method_func_type;

            LLVMTypeRef method_func_ptr_type = LLVMPointerType(method_func_type, 0); // Puntero a ese tipo de función

            vtable_slot_ptr_types[j++] = method_func_ptr_type;

            free(llvm_param_types);
        }

        if (child->type == NODE_FUNC_DEC && child->data.func_node.flag_overriden >= 1)
        {
            int index = child->data.func_node.flag_overriden - 1;

            LLVMValueRef llvm_ret_type = type_to_llvm(v->ctx, child->data.func_node.body->return_type);

            // 1. Calcular le numero total de parametros LLVM : 'this' + parametros explicito
            int num_explicit_params = child->data.func_node.arg_count;
            int total_llvm_params = 1 + num_explicit_params;

            // 2. Asignar memoria para el array de tipo de paramtros LLVM
            LLVMTypeRef *llvm_param_types = (LLVMTypeRef *)malloc(total_llvm_params * sizeof(LLVMTypeRef));

            if (!llvm_param_types)
            {
                perror("Error en malloc para llvm_param_types");
                exit(EXIT_FAILURE);
            }

            // 3. El primer paramtros siempre es el puntero 'this'
            llvm_param_types[0] = LLVMPointerType(class_struct_type, 0);

            // 4. Agregar los tipos de los apramtros explcitios
            for (int k = 0; k < num_explicit_params; k++)
            {
                llvm_param_types[k + 1] = type_to_llvm(v->ctx, child->data.func_node.args[k]->return_type);
            }

            // 5. Crear el tipo de la funcion LLVM con el array de parametros correctos
            LLVMTypeRef method_func_type = LLVMFunctionType(llvm_ret_type, llvm_param_types, total_llvm_params, 0);

            vtable_slot_types[index] = method_func_type;

            LLVMTypeRef method_func_ptr_type = LLVMPointerType(method_func_type, 0); // Puntero a ese tipo de función

            vtable_slot_ptr_types[index] = method_func_ptr_type;
        }
    }

    LLVMStructSetBody(vtable_struct_type, vtable_slot_ptr_types, type_info->num_methods_virtual, 0);

    type_info->vtable_slot_ptr_types = vtable_slot_ptr_types;
    type_info->vtable_slot_types = vtable_slot_types;


    LLVMTypeRef vtable_ptr_type = LLVMPointerType(vtable_struct_type, 0);
    type_info->vtable_ptr_type = vtable_ptr_type;

    LLVMTypeRef *struct_fields = build_struct_fields(v->ctx, node, type_info);

    type_info->struct_fields = struct_fields;

    LLVMStructSetBody(class_struct_type, struct_fields, 2 + type_info->num_data_members, 0); // aqui donde hay un 4 iba un 3

    LLVMTypeRef ptr_type = LLVMPointerType(class_struct_type, 0); // Puntero a %A

#pragma region MET_TYPES

    // ------------------------------------L LA PASION ---------------------------------------------
    // LLVMValueRef *vtable_initializer_values = build_struct_method(v->ctx,node,type_info);


    LLVMValueRef *vtable_initializer_values = build_vtable_initializer(v->ctx, node, type_info);
    type_info->vtable_initializer_values = vtable_initializer_values;

#pragma endregion

    // --- 6. Definición d  e la Instancia Global de Vtable (@A_vtable_instance) ---
    // @A_vtable_instance = internal global %A_vtable { i32 (%A*)* @_A_getX }

    // aqui el segundo 0 debe ser relacionado con los metodos de vtable_initilizer_value
    LLVMValueRef vtable_constant = LLVMConstStruct(vtable_initializer_values, type_info->num_methods_virtual, 0);

    char vtable_name_type[256];
    snprintf(vtable_name_type, sizeof(vtable_name_type), "%s_vtable_instance", type_name);

    LLVMValueRef vtable_instance_global = LLVMAddGlobal(v->ctx->module, vtable_struct_type, vtable_name_type);
    LLVMSetInitializer(vtable_instance_global, vtable_constant);
    LLVMSetLinkage(vtable_instance_global, LLVMInternalLinkage);
    LLVMSetUnnamedAddr(vtable_instance_global, 1);

    type_info->vtable_global = vtable_instance_global; // Se asigna en make_body_type_dec
}

void find_type_dec(LLVMVisitor *v, ASTNode *node)
{

    if (!node)
        return;

    if (node->type == NODE_TYPE_DEC)
    {
        const char *type_name = node->data.type_node.name;
        if (!find_user_type(v->ctx, type_name)) // Si no ha sido declarado aún
        {
            build_vtable_table(v, node);
        }
    }

    if (node->type == NODE_PROGRAM || node->type == NODE_BLOCK)
    {
        for (int i = 0; i < node->data.program_node.count; i++)
        {
            find_type_dec(v, node->data.program_node.statements[i]);
        }
    }

}

#pragma endregion