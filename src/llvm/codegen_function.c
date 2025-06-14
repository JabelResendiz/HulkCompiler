
#include "codegen.h"
#include <stdio.h>
#include <string.h>

// #define DEFINE_MATH_FUNC(name)                                 \
//     LLVMValueRef name##_handler(LLVMVisitor *v, ASTNode *node) \
//     {                                                          \
//         return handle_math(v, node, #name, #name "_tmp");      \
//     }

// DEFINE_MATH_FUNC(sqrt)
// DEFINE_MATH_FUNC(sin)
// DEFINE_MATH_FUNC(cos)
// DEFINE_MATH_FUNC(exp)

LLVMValueRef codegen_call_function(LLVMVisitor *v, ASTNode *node)
{
    fprintf(stderr,"ANDO EN EL CODEGEN DE CALL FUNCTION: nombre de la funcion %s\n", node->data.func_node.name);

   
    if (!strcmp(node->data.func_node.name, "print"))
    {
        return codegen_print(v, node);
    }
    if (!strcmp(node->data.func_node.name, "sqrt"))
    {
        return codegen_math_function(v, node, "sqrt", "sqrt_tmp");
    }
    if (!strcmp(node->data.func_node.name, "sin"))
    {
        return codegen_math_function(v, node, "sin", "sin_tmp");
    }
    if (!strcmp(node->data.func_node.name, "cos"))
    {
        return codegen_math_function(v, node, "cos", "cos_tmp");
    }
    if (!strcmp(node->data.func_node.name, "exp"))
    {
        return codegen_math_function(v, node, "exp", "exp_tmp");
    }
    if (!strcmp(node->data.func_node.name, "log"))
    {
        return codegen_log(v, node);
    }
    if (!strcmp(node->data.func_node.name, "rand"))
    {
        return codegen_rand(v, node);
    }

     fprintf(stderr,"ando callao\n");
    return codegen_custom_func(v, node);
}

LLVMValueRef codegen_print(LLVMVisitor *v, ASTNode *node)
{
    fprintf(stderr,"JABEL RESENDIZ");
     LLVMValueRef printf_func = LLVMGetNamedFunction(v->ctx->module, "printf");

    // Si no hay argumentos, solo imprime una nueva línea
    if (node->data.func_node.arg_count == 0) {
        LLVMValueRef format_str = LLVMBuildGlobalStringPtr(v->ctx->builder, "\n", "newline");
        LLVMTypeRef printf_type = LLVMFunctionType(LLVMInt32Type(),
            (LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(), 0)}, 1, 1);
        return LLVMBuildCall2(v->ctx->builder, printf_type, printf_func,
            (LLVMValueRef[]){format_str}, 1, "printf_call");
    }

    // Generar código para el argumento
    ASTNode* arg_node = node->data.func_node.args[0];
    LLVMValueRef arg = codegen_accept(v, arg_node);
    if (!arg) return NULL;

    const char* format = "";
    LLVMValueRef format_str;
    LLVMValueRef args[2];  
    int num_args = 2;      

    // Seleccionar formato según el tipo del argumento
    if (compare_types(arg_node->computed_type, &TYPE_NUM)) {
        format = "%g\n";
        format_str = LLVMBuildGlobalStringPtr(v->ctx->builder, format, "fmt");
        args[0] = format_str;
        args[1] = arg;
    } else if (compare_types(arg_node->computed_type, &TYPE_BOOLEAN)) {
        format_str = LLVMBuildGlobalStringPtr(v->ctx->builder, "%s\n", "fmt");
        LLVMValueRef true_str = LLVMBuildGlobalStringPtr(v->ctx->builder, "true", "true_str");
        LLVMValueRef false_str = LLVMBuildGlobalStringPtr(v->ctx->builder, "false", "false_str");
        LLVMValueRef cond_str = LLVMBuildSelect(v->ctx->builder, arg, true_str, false_str, "bool_str");
        args[0] = format_str;
        args[1] = cond_str;
    } else if (compare_types(arg_node->computed_type, &TYPE_STRING)) {
        format = "%s\n";
        format_str = LLVMBuildGlobalStringPtr(v->ctx->builder, format, "fmt");
        args[0] = format_str;
        args[1] = arg;
    } else {
       
        format = "%s\n";
        format_str = LLVMBuildGlobalStringPtr(v->ctx->builder, format, "fmt");
        LLVMValueRef unknown_str = LLVMBuildGlobalStringPtr(v->ctx->builder, "<unknown>", "unknown_str");
        args[0] = format_str;
        args[1] = unknown_str;
    }

    // Construir llamada a printf
    LLVMTypeRef printf_type = LLVMFunctionType(LLVMInt32Type(),
        (LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(), 0)}, 1, 1);

    fprintf(stderr,"JABEL RESENDIZ");

    return LLVMBuildCall2(v->ctx->builder, printf_type, printf_func, args, num_args, "printf_call");
}

LLVMValueRef codegen_math_function(LLVMVisitor *v, ASTNode *node,const char* name, const char* tmp_name)
{
     LLVMValueRef arg = codegen_accept(v, node->data.func_node.args[0]);
    LLVMTypeRef type = LLVMFunctionType(LLVMDoubleType(),
        (LLVMTypeRef[]){LLVMDoubleType()}, 1, 0);
    LLVMValueRef func = LLVMGetNamedFunction(v->ctx->module, name);
    return LLVMBuildCall2(v->ctx->builder, type, func,
            (LLVMValueRef[]){arg}, 1, tmp_name);
}

LLVMValueRef codegen_rand(LLVMVisitor *v, ASTNode *node)
{
    LLVMTypeRef rand_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef rand_func = LLVMGetNamedFunction(v->ctx->module, "rand");

    // Convertir el resultado entero a double dividiendo por RAND_MAX
    LLVMValueRef rand_val = LLVMBuildCall2(v->ctx->builder, rand_type, rand_func, NULL, 0, "rand_tmp");
    LLVMValueRef rand_max = LLVMConstReal(LLVMDoubleType(), RAND_MAX);
    LLVMValueRef rand_double = LLVMBuildSIToFP(v->ctx->builder, rand_val, LLVMDoubleType(), "rand_double");

    return LLVMBuildFDiv(v->ctx->builder, rand_double, rand_max, "rand_result");
}

LLVMValueRef codegen_log(LLVMVisitor *v, ASTNode *node)
{
    
    if (node->data.func_node.arg_count == 1)
    {
        LLVMValueRef arg = codegen_accept(v, node->data.func_node.args[0]);
        LLVMTypeRef log_type = LLVMFunctionType(LLVMDoubleType(),
                                                (LLVMTypeRef[]){LLVMDoubleType()}, 1, 0);
        LLVMValueRef log_func = LLVMGetNamedFunction(v->ctx->module, "log");
        return LLVMBuildCall2(v->ctx->builder, log_type, log_func,
                              (LLVMValueRef[]){arg}, 1, "log_tmp");
    }
    // tiene 2 argumetnos
    else
    {
        // log(base, x) = log(x) / log(base)
        LLVMValueRef base = codegen_accept(v, node->data.func_node.args[0]);
        LLVMValueRef x = codegen_accept(v, node->data.func_node.args[1]);

        LLVMTypeRef log_type = LLVMFunctionType(LLVMDoubleType(),
                                                (LLVMTypeRef[]){LLVMDoubleType()}, 1, 0);
        LLVMValueRef log_func = LLVMGetNamedFunction(v->ctx->module, "log");

        LLVMValueRef log_x = LLVMBuildCall2(v->ctx->builder, log_type, log_func,
                                            (LLVMValueRef[]){x}, 1, "log_x");
        LLVMValueRef log_base = LLVMBuildCall2(v->ctx->builder, log_type, log_func,
                                               (LLVMValueRef[]){base}, 1, "log_base");

        return LLVMBuildFDiv(v->ctx->builder, log_x, log_base, "log_result");
    }
}

LLVMValueRef codegen_custom_func(LLVMVisitor *v, ASTNode *node)
{
    fprintf(stderr,"ANDAMOS EN EL CODEGEN_CUSTOM_FUNC\n");

    const char *name = node->data.func_node.name;

    LLVMValueRef func = LLVMGetNamedFunction(v->ctx->module, name);
    LLVMTypeRef func_type = LLVMGetElementType(LLVMTypeOf(func));
    unsigned param_count = LLVMCountParamTypes(func_type);

    int arg_count = node->data.func_node.arg_count;
    ASTNode **args = node->data.func_node.args;
    TypeValue *return_type = node->computed_type;

    fprintf(stderr,"tremenda candela, EL TIPO DE RETURN ES %s\n", return_type->name);


    // Obtener tipos de los argumentos
    LLVMTypeRef *arg_types = malloc(arg_count * sizeof(LLVMTypeRef));
    LLVMValueRef *arg_values = malloc(arg_count * sizeof(LLVMValueRef));

    for (int i = 0; i < arg_count; i++)
    {
        fprintf(stderr,"1111111111111\n");
        arg_types[i] = type_to_llvm(args[i]->computed_type);
        arg_values[i] = codegen_accept(v, args[i]);
    }

    fprintf(stderr,"tremenda candela\n");

    

    if (!func)
    {
        func = LLVMAddFunction(v->ctx->module, name, func_type);
    }

    fprintf(stderr,"tremenda candela\n");

    
    char *calltmp = compare_types(return_type, &TYPE_VOID) ? "" : "calltmp";

    fprintf(stderr,"tremenda candela\n");

    // Construir llamada
    LLVMValueRef call = LLVMBuildCall2(
        v->ctx->builder,
        func_type,
        func,
        arg_values,
        arg_count,
        calltmp);

    fprintf(stderr,"tremenda candela\n");

    
    free(arg_types);
    free(arg_values);
    return call;
}

LLVMValueRef codegen_dec_function(LLVMVisitor* v, ASTNode* node)
{
    fprintf(stderr,"estamos en el decl_function_codegen \n");
    
    LLVMModuleRef module = v->ctx->module;
    LLVMBuilderRef builder = v->ctx->builder;
    LLVMValueRef current_stack_depth_var = v->ctx->current_stack_depth_var;
    int max_stack_depth = v->ctx->max_stack_depth;

    const char *name = node->data.func_node.name;
    TypeValue *return_type = node->data.func_node.body->computed_type;
    ASTNode **params = node->data.func_node.args;
    int param_count = node->data.func_node.arg_count;
    ASTNode *body = node->data.func_node.body;

    // Obtener tipos de parámetros
    LLVMTypeRef *param_types = malloc(param_count * sizeof(LLVMTypeRef));
    for (int i = 0; i < param_count; i++)
    {
        param_types[i] = type_to_llvm(params[i]->computed_type);
    }

    LLVMValueRef func = LLVMGetNamedFunction(module, name);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, "entry");
    LLVMBasicBlockRef exit_block = LLVMAppendBasicBlock(func, "function_exit");

    // Configurar builder
    LLVMPositionBuilderAtEnd(builder, entry);

    // 1. Stack depth handling
    // Increment counter
    LLVMTypeRef int32_type = LLVMInt32Type();
    LLVMValueRef depth_val = LLVMBuildLoad2(builder, int32_type, current_stack_depth_var, "load_depth");
    LLVMValueRef new_depth = LLVMBuildAdd(builder, depth_val, LLVMConstInt(int32_type, 1, 0), "inc_depth");
    LLVMBuildStore(builder, new_depth, current_stack_depth_var);

    // Verificar overflow
    LLVMValueRef cmp = LLVMBuildICmp(builder, LLVMIntSGT, new_depth,
                                     LLVMConstInt(LLVMInt32Type(), max_stack_depth, 0), "cmp_overflow");

    // Crear bloques para manejo de error
    LLVMBasicBlockRef error_block = LLVMAppendBasicBlock(func, "stack_overflow");
    LLVMBasicBlockRef continue_block = LLVMAppendBasicBlock(func, "func_body");
    LLVMBuildCondBr(builder, cmp, error_block, continue_block);

    // Bloque de error
    LLVMPositionBuilderAtEnd(builder, error_block);
    llvm_handle_stack_overflow(v->ctx, node);

    // Continuar con función normal
    LLVMPositionBuilderAtEnd(builder, continue_block);

    push_scope();

    // Almacenar parámetros en variables locales
    for (int i = 0; i < param_count; i++)
    {
        LLVMValueRef param = LLVMGetParam(func, i);
        LLVMValueRef alloca = LLVMBuildAlloca(builder, param_types[i], params[i]->data.var_name);
        LLVMBuildStore(builder, param, alloca);
        declare_variable(params[i]->data.var_name, alloca);
    }

    // Generar código para el cuerpo
    LLVMValueRef body_val = codegen_accept(v, body);

    // Branch al bloque de salida
    LLVMBuildBr(builder, exit_block);

    // Bloque de salida
    LLVMPositionBuilderAtEnd(builder, exit_block);

    // Decrementar contador antes de retornar
    LLVMValueRef final_depth = LLVMBuildLoad2(builder, int32_type, current_stack_depth_var, "load_depth_final");
    LLVMValueRef dec_depth = LLVMBuildSub(builder, final_depth, LLVMConstInt(int32_type, 1, 0), "dec_depth");
    LLVMBuildStore(builder, dec_depth, current_stack_depth_var);

    // Return value handling
    if (compare_types(return_type, &TYPE_VOID))
    {
        LLVMBuildRetVoid(builder);
    }
    else if (body_val)
    {
        // If we have a return value, use it
        LLVMBuildRet(builder, body_val);
    }
    else
    {
        // Default return 0.0 as double
        LLVMBuildRet(builder, LLVMConstReal(LLVMDoubleType(), 0.0));
    }

    pop_scope();
    free(param_types);

    fprintf(stderr,"TODO CON EXITO EN EL DEC_FUCNTION\n");

    return func;
}