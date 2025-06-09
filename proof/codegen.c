// codegen.c
#include "codegen.h"
#include "ast.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tabla de símbolos para variables locales
typedef struct SymbolEntry
{
    char *name;
    LLVMValueRef value;
    struct SymbolEntry *next;
} SymbolEntry;

typedef struct SymbolTable
{
    SymbolEntry *entries;
    struct SymbolTable *parent;
} SymbolTable;

static SymbolTable *current_scope = NULL;

static void push_scope()
{
    SymbolTable *new_scope = malloc(sizeof(SymbolTable));
    new_scope->entries = NULL;
    new_scope->parent = current_scope;
    current_scope = new_scope;
}

static void pop_scope()
{
    if (current_scope)
    {
        SymbolTable *parent = current_scope->parent;
        free(current_scope);
        current_scope = parent;
    }
}

static void add_symbol(const char *name, LLVMValueRef value)
{
    SymbolEntry *entry = malloc(sizeof(SymbolEntry));
    entry->name = strdup(name);
    entry->value = value;
    entry->next = current_scope->entries;
    current_scope->entries = entry;
}

static LLVMValueRef lookup_symbol(const char *name)
{
    SymbolTable *scope = current_scope;
    while (scope)
    {
        SymbolEntry *entry = scope->entries;
        while (entry)
        {
            if (strcmp(entry->name, name) == 0)
            {
                return entry->value;
            }
            entry = entry->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

void codegen_init(CodegenContext *ctx, const char *module_name)
{
    ctx->context = LLVMGetGlobalContext();
    ctx->module = LLVMModuleCreateWithNameInContext(module_name, ctx->context);
    ctx->builder = LLVMCreateBuilderInContext(ctx->context);
    ctx->current_function = NULL;
    ctx->pass_manager = NULL;

    // Configurar optimizaciones básicas
    ctx->pass_manager = LLVMCreateFunctionPassManagerForModule(ctx->module);
    LLVMAddInstructionCombiningPass(ctx->pass_manager);
    LLVMAddReassociatePass(ctx->pass_manager);
    LLVMAddGVNPass(ctx->pass_manager);
    LLVMAddCFGSimplificationPass(ctx->pass_manager);
    LLVMInitializeFunctionPassManager(ctx->pass_manager);

    // Inicializar tabla de símbolos
    push_scope();
}

void codegen_cleanup(CodegenContext *ctx)
{
    if (ctx->pass_manager)
    {
        LLVMDisposePassManager(ctx->pass_manager);
    }
    LLVMDisposeBuilder(ctx->builder);
    LLVMDisposeModule(ctx->module);

    // Limpiar tabla de símbolos
    while (current_scope)
    {
        pop_scope();
    }
}

static LLVMTypeRef get_llvm_type(ValueType type)
{
    switch (type)
    {
    case TYPE_INT:
        return LLVMInt32Type();
    case TYPE_STRING:
        return LLVMPointerType(LLVMInt8Type(), 0);
    case TYPE_BOOL:
        return LLVMInt1Type();
    case TYPE_VOID:
        return LLVMVoidType();
    default:
        return LLVMInt32Type(); // Por defecto asumimos entero
    }
}

LLVMValueRef codegen_expr(CodegenContext *ctx, ASTNode *node)
{
    if (!node)
        return NULL;

    switch (node->type)
    {
    case AST_NUM:
        return LLVMConstInt(LLVMInt32Type(), node->value, 0);

    case AST_VAR:
    {
        LLVMValueRef val = lookup_symbol(node->var_name);
        if (!val)
        {
            fprintf(stderr, "Error: Variable no declarada '%s'\n", node->var_name);
            return NULL;
        }
        // Obtener el tipo apuntado (asumiendo val es un puntero)
        LLVMTypeRef ptr_type = LLVMTypeOf(val);
        LLVMTypeRef loaded_type = LLVMGetElementType(ptr_type);
        return LLVMBuildLoad2(ctx->builder, loaded_type, val, node->var_name);
    }

    case AST_STRING:
        return LLVMBuildGlobalStringPtr(ctx->builder, node->string_value, "str");

    case AST_ADD:
    case AST_SUB:
    case AST_MUL:
    case AST_DIV:
    {
        LLVMValueRef L = codegen_expr(ctx, node->left);
        LLVMValueRef R = codegen_expr(ctx, node->right);
        if (!L || !R)
            return NULL;

        switch (node->type)
        {
        case AST_ADD:
            return LLVMBuildAdd(ctx->builder, L, R, "addtmp");
        case AST_SUB:
            return LLVMBuildSub(ctx->builder, L, R, "subtmp");
        case AST_MUL:
            return LLVMBuildMul(ctx->builder, L, R, "multmp");
        case AST_DIV:
            return LLVMBuildSDiv(ctx->builder, L, R, "divtmp");
        default:
            return NULL;
        }
    }

    case AST_CONCAT:
    {
        // Implementación simplificada de concatenación de strings
        LLVMValueRef str1 = codegen_expr(ctx, node->left);
        LLVMValueRef str2 = codegen_expr(ctx, node->right);

        // Necesitaríamos implementar llamadas a funciones de concatenación
        // Esto es un placeholder simplificado
        return str1; // Debería ser una llamada a strcat o similar
    }

    case AST_PRINT:
        return codegen_print(ctx, node);

    case AST_IF:
        return codegen_if(ctx, node);

    case AST_LET:
        return codegen_let(ctx, node);

    default:
        fprintf(stderr, "Error: Expresión no implementada en codegen_expr\n");
        return NULL;
    }
}

LLVMValueRef codegen_let(CodegenContext *ctx, ASTNode *node)
{
    push_scope();

    // Procesar bindings
    VarBinding *binding = node->bindings;
    while (binding)
    {
        LLVMValueRef val = codegen_expr(ctx, binding->value);
        if (!val)
        {
            pop_scope();
            return NULL;
        }

        // Crear alloca para la variable
        LLVMTypeRef type = get_llvm_type(binding->value->computed_type);
        LLVMValueRef alloca = LLVMBuildAlloca(ctx->builder, type, binding->name);
        LLVMBuildStore(ctx->builder, val, alloca);

        // Añadir a la tabla de símbolos
        add_symbol(binding->name, alloca);

        binding = binding->next;
    }

    // Generar cuerpo del let
    LLVMValueRef body_val = codegen_expr(ctx, node->left);

    pop_scope();
    return body_val;
}

LLVMValueRef codegen_if(CodegenContext *ctx, ASTNode *node)
{
    LLVMValueRef cond = codegen_expr(ctx, node->condition);
    if (!cond)
        return NULL;

    // Convertir condición a booleano si es necesario
    if (node->condition->computed_type != TYPE_BOOL)
    {
        cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond,
                             LLVMConstInt(LLVMInt32Type(), 0, 0), "ifcond");
    }

    LLVMBasicBlockRef then_bb = LLVMAppendBasicBlock(ctx->current_function, "then");
    LLVMBasicBlockRef else_bb = node->else_branch ? LLVMAppendBasicBlock(ctx->current_function, "else") : NULL;
    LLVMBasicBlockRef merge_bb = LLVMAppendBasicBlock(ctx->current_function, "ifcont");

    // Emitir branch condicional
    if (else_bb)
    {
        LLVMBuildCondBr(ctx->builder, cond, then_bb, else_bb);
    }
    else
    {
        LLVMBuildCondBr(ctx->builder, cond, then_bb, merge_bb);
    }

    // Generar bloque then
    LLVMPositionBuilderAtEnd(ctx->builder, then_bb);
    LLVMValueRef then_val = codegen_expr(ctx, node->left);
    if (!then_val)
        return NULL;
    LLVMBuildBr(ctx->builder, merge_bb);

    // Actualizar posición del builder después del then
    then_bb = LLVMGetInsertBlock(ctx->builder);

    // Generar bloque else si existe
    LLVMValueRef else_val = NULL;
    if (else_bb)
    {
        LLVMPositionBuilderAtEnd(ctx->builder, else_bb);
        else_val = codegen_expr(ctx, node->else_branch);
        if (!else_val)
            return NULL;
        LLVMBuildBr(ctx->builder, merge_bb);
        else_bb = LLVMGetInsertBlock(ctx->builder);
    }

    // Emitir bloque merge
    LLVMPositionBuilderAtEnd(ctx->builder, merge_bb);

    // Para expresiones if-then-else que producen valores, necesitamos PHI node
    if (then_val && else_val && node->computed_type != TYPE_VOID)
    {
        LLVMTypeRef type = get_llvm_type(node->computed_type);
        LLVMValueRef phi = LLVMBuildPhi(ctx->builder, type, "iftmp");

        LLVMValueRef incoming_values[2] = {then_val, else_val};
        LLVMBasicBlockRef incoming_blocks[2] = {then_bb, else_bb};
        LLVMAddIncoming(phi, incoming_values, incoming_blocks, 2);

        return phi;
    }

    return else_val ? else_val : then_val;
}

LLVMValueRef codegen_print(CodegenContext *ctx, ASTNode *node)
{
    LLVMValueRef val = codegen_expr(ctx, node->left);
    if (!val)
        return NULL;

    // Obtener la función printf
    LLVMTypeRef printf_type = LLVMFunctionType(LLVMInt32Type(),
                                               (LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(), 0)}, 1, 1);
    LLVMValueRef printf_func = LLVMGetNamedFunction(ctx->module, "printf");
    if (!printf_func)
    {
        printf_func = LLVMAddFunction(ctx->module, "printf", printf_type);
        LLVMSetLinkage(printf_func, LLVMDLLImportLinkage);
    }

    // Crear cadena de formato según el tipo
    const char *format_str;
    if (node->left->computed_type == TYPE_STRING)
    {
        format_str = "%s\n";
    }
    else
    {
        format_str = "%d\n";
    }

    LLVMValueRef format = LLVMBuildGlobalStringPtr(ctx->builder, format_str, "fmt");

    // Obtener el tipo de la función (sin puntero)
    LLVMTypeRef func_type = LLVMGetElementType(LLVMTypeOf(printf_func));

    LLVMValueRef args[2] = {format, val};
    return LLVMBuildCall2(ctx->builder, func_type, printf_func, args, 2, "printfcall");
}

void codegen_generate(CodegenContext *ctx, ASTNode *root)
{
    // Crear función main
    LLVMTypeRef main_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef main_func = LLVMAddFunction(ctx->module, "main", main_type);
    ctx->current_function = main_func;

    // Crear bloque de entrada
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_func, "entry");
    LLVMPositionBuilderAtEnd(ctx->builder, entry);

    // Generar código para el AST
    LLVMValueRef ret_val = codegen_expr(ctx, root);

    // Retornar 0 si no hay valor de retorno
    if (!ret_val)
    {
        ret_val = LLVMConstInt(LLVMInt32Type(), 0, 0);
    }

    LLVMBuildRet(ctx->builder, ret_val);

    // Verificar el módulo
    char *error = NULL;
    if (LLVMVerifyModule(ctx->module, LLVMAbortProcessAction, &error))
    {
        fprintf(stderr, "Error al verificar módulo: %s\n", error);
        LLVMDisposeMessage(error);
    }

    // Optimizar la función
    if (ctx->pass_manager)
    {
        LLVMRunFunctionPassManager(ctx->pass_manager, main_func);
    }
}