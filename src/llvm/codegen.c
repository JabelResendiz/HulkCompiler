

// // codegen.c

// #include "codegen.h"
// #include "init_codegen.h"
// #include "llvm_scope/llvm_scope.h"
// #include <stdio.h>

// LLVMTypeRef get_llvm_type(TypeValue* type)
// {
//     if (compare_types(type,&TYPE_NUM))
//     {
//         return LLVMDoubleType(); // doble en LLVM
//     }
//     else if (compare_types(type,&TYPE_STRING))
//     {
//         return LLVMPointerType(LLVMInt8Type(), 0); // puntero a i8* lo que equivale un char*
//     }
//     else if (compare_types(type,&TYPE_BOOLEAN))
//     {
//         return LLVMInt1Type(); // se usa i1, el tipo entero de 1 bit en LLVM
//     }
//     else if (compare_types(type,&TYPE_VOID))
//     {
//         return LLVMVoidType(); // retorno el tipo void de LLVM
//     }
//     else if (compare_types(type,&TYPE_OBJ))
//     {
//         // usamos un puntero void* que puede apuntar a cualquier tipo
//         return LLVMPointerType(LLVMInt8Type(), 0);
//     }

//     fprintf(stderr, "Error: Tipo desconocido %s\n", type->name);
//     exit(1);
// }

// void codegen_main(ASTNode *node, const char *filename)
// {
//     LLVMVisitor visitor =
//         {
//             .basic.program = codegen_program,
//             .basic.number = codegen_number,
//             .expr.binary = codegen_binary_op};

//     // Initializa el LLVM
//     init_llvm();

//     // Declare external functions
//     // declare_external_functions();
//     // find_function_dec(&visitor, ast);
//     // make_body_function_dec(&visitor, ast);
//     // Create scope
//     push_scope();

//     // Create main function
//     LLVMTypeRef main_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
//     LLVMValueRef main_func = LLVMAddFunction(module, "main", main_type);

//     // Create entry block
//     LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_func, "entry");
//     LLVMPositionBuilderAtEnd(builder, entry);

//     // Generate code for AST
//     if (node)
//     {
//         codegen_accept(&visitor, node);
//     }

//     // Agregar return 0 si el bloque no termina con return
//     if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(builder)))
//     {
//         LLVMBuildRet(builder, LLVMConstInt(LLVMInt32Type(), 0, 0));
//     }

//     // Escribir archivo .ll
//     char *error = NULL;
//     if (LLVMPrintModuleToFile(module, filename, &error))
//     {
//         fprintf(stderr, "Error writing IR: %s\n", error);
//         LLVMDisposeMessage(error);
//         exit(1);
//     }

//     free_llvm_resources(); // liberar contexto, módulo, builder

//     // LLVMBasicBlockRef current_block = LLVMGetInsertBlock(builder);
//     // if (!LLVMGetBasicBlockTerminator(current_block)) {
//     //     // Return 0 from main if the block isn't already terminated
//     //     LLVMBuildRet(builder, LLVMConstInt(LLVMInt32Type(), 0, 0));
//     // }

//     // // Write to file
//     // char* error = NULL;
//     // if (LLVMPrintModuleToFile(module, filename, &error)) {
//     //     fprintf(stderr, "Error writing IR: %s\n", error);
//     //     LLVMDisposeMessage(error);
//     //     exit(1);
//     // }

//     // // Free resources
//     // free_llvm_resources();
// }

// LLVMValueRef codegen_program(LLVMVisitor *v, ASTNode *node)
// {
//     push_scope();
//     LLVMValueRef last = NULL;

//     for (int i = 0; i < node->data.program.count; i++)
//     {
//         ASTNode *stmt = node->data.program.statements[i];
//         // if (stmt->type != NODE_FUNC_DEC)
//         // {
//         last = codegen_accept(v, stmt);
//         // }
//     }

//     pop_scope();
//     return last ? last : LLVMConstInt(LLVMInt32Type(), 0, 0);
// }

// LLVMValueRef codegen_number(LLVMVisitor *v, ASTNode *node)
// {
//     return LLVMConstReal(LLVMDoubleType(), node->data.number_value);
// }

// LLVMValueRef codegen_variable(LLVMVisitor *v, ASTNode *node)
// {
//     LLVMValueRef alloca = lookup_variable(node->data.var_name);

//     if (!alloca)
//     {
//         exit(1);
//     }

//     LLVMTypeRef var_type = LLVMGetElementType(LLVMTypeOf(alloca));

//     return LLVMBuildLoad2(builder, var_type, alloca, "load");
// }

// LLVMValueRef codegen_let_in(LLVMVisitor *v, ASTNode *node)
// {
//     // se crea un ambito lexico para q las variables declaradas con let no afecten
//     // el programa
//     push_scope();

//     ASTNode **bindings = node->data.func_node.args;

//     int dec_count = node->data.func_node.arg_count;

//     // Evaluar y almacenar cada declaración
//     for (int i = 0; i < dec_count; i++)
//     {
//         ASTNode *decl = bindings[i];
//         const char *name = decl->data.binary_op.left->data.var_name;

//         // evaluar el lado derecho de la variable
//         LLVMValueRef value = codegen_accept(v, decl->data.binary_op.right);

//         if (!value)
//         {
//             return NULL;
//         }

//         // Crear alloca para la variable
//         // Reserva espacio en la pila alloca
//         LLVMTypeRef type = get_llvm_type(decl->data.binary_op.right->computed_type);
//         LLVMValueRef alloca = LLVMBuildAlloca(builder, type, name);
//         // Guarda el store
//         LLVMBuildStore(builder, value, alloca);
//         // Regsitra esa variable en el entorno actaul
//         declare_variable(name, alloca);
//     }

//     // Obtener el bloque actual antes de evaluar el cuerpo
//     LLVMBasicBlockRef current_block = LLVMGetInsertBlock(builder);

//     // Evaluar el cuerpo
//     LLVMValueRef result = codegen_accept(v, node->data.func_node.body);

//     // Asegurar que estamos en el bloque correcto después de la evaluación
//     LLVMPositionBuilderAtEnd(builder, LLVMGetInsertBlock(builder));

//     // Se elimina el ambito local
//     pop_scope();
//     return result;
// }

// LLVMValueRef codegen_assignments(LLVMVisitor *v, ASTNode *node)
// {
//     const char *name = node->data.binary_op.left->data.var_name;

//     LLVMValueRef value = codegen_accept(v, node->data.binary_op.right);

//     // Deteminar le tipo LLVM del valor a asignar dependiendo del tipo del lenguaje
//     LLVMTypeRef new_type;

//     switch (node->data.binary_op.right->computed_type)
//     {
//     case TYPE_STRING:
//         new_type = LLVMPointerType(LLVMInt8Type(), 0);
//         break;
//     case TYPE_BOOLEAN:
//         new_type = LLVMInt1Type();
//         break;
//     default:
//         new_type = LLVMDoubleType();
//         break;
//     }

//     // Guarda el bloque actual donde se esta generando codigo
//     LLVMBasicBlockRef current_block = LLVMGetInsertBlock(builder);

//     // Obtiene el bloque de entrad ade la funcion que contiene el bloque actual
//     LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(LLVMGetBasicBlockParent(current_block));

//     // Muevae el builder temporalmente al bloque de entrada para crear la alloca
//     LLVMPositionBuilderAtEnd(builder, entry_block);

//     // Busca si ya existe una alloca para esa variable
//     LLVMValueRef existing_alloca = lookup_variable(name);

//     // Reservará el puntero a memoria donde se almacenará el valor.
//     LLVMValueRef alloca;

//     if (existing_alloca)
//     {
//         // if (node->type == NODE_D_ASSIGNMENT)
//         // {
//         //     update_variable(var_name, existing_alloca);
//         // }

//         // Si hay unca varaible pero su tipo no coincide con el del nuveo valor , se crea un nueva alloca y se update
//         LLVMTypeRef existing_type = LLVMGetElementType(LLVMTypeOf(existing_alloca));
//         if (existing_type != LLVMTypeOf(value))
//         {
//             alloca = LLVMBuildAlloca(builder, new_type, name);
//             update_variable(name, alloca);
//         }
//         else
//         {
//             alloca = existing_alloca;
//         }
//     }
//     else
//     {
//         // Si no existia antes se crea una nueva alloca y se declara esa variable en el entorno
//         alloca = LLVMBuildAlloca(builder, new_type, name);
//         declare_variable(name, alloca);
//     }

//     // Se vuelve al bloque donde estaba antes para continuar generando el resto del código
//     LLVMPositionBuilderAtEnd(builder, current_block);

//     //Se guarda el valor calculado en la dirección de memoria reservada con alloca
//     LLVMBuildStore(builder, value, alloca);

//     // // Para asignación destructiva (:=), retornar el valor asignado
//     // if (node->type == NODE_D_ASSIGNMENT)
//     // {
//     //     return value;
//     // }

//     return NULL;
// }