#include <stdio.h>
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>

int main() {
    // Crear contexto, módulo y builder
    LLVMModuleRef module = LLVMModuleCreateWithName("my_module");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMContextRef context = LLVMGetGlobalContext();

    // Tipo de retorno i32 y función main sin parámetros
    LLVMTypeRef returnType = LLVMInt32Type(); // i32
    LLVMTypeRef funcType = LLVMFunctionType(returnType, NULL, 0, 0);
    LLVMValueRef mainFunc = LLVMAddFunction(module, "main", funcType);

    // Crear el bloque de entrada
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(mainFunc, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    // Generar 2 + 3
    LLVMValueRef const2 = LLVMConstInt(LLVMInt32Type(), 9, 0);
    LLVMValueRef const3 = LLVMConstInt(LLVMInt32Type(), 1, 0);
    LLVMValueRef sum = LLVMBuildAdd(builder, const2, const3, "sum");

    // Retornar la suma
    LLVMBuildRet(builder, sum);

    // Verificar el módulo
    char *error = NULL;
    if (LLVMVerifyModule(module, LLVMAbortProcessAction, &error)) {
        fprintf(stderr, "Error al verificar módulo: %s\n", error);
        LLVMDisposeMessage(error);
    }

    // Obtener IR como string
    char *ir = LLVMPrintModuleToString(module);
    puts(ir);  // Mostrar el IR por consola

    // Guardar IR manualmente en archivo
    FILE *f = fopen("output.ll", "w");
    if (f) {
        fputs(ir, f);
        fclose(f);
        printf("IR guardado correctamente en output.ll\n");
    } else {
        fprintf(stderr, "No se pudo abrir el archivo para escribir.\n");
    }

    LLVMDisposeMessage(ir);  // Liberar memoria del IR

    // Limpiar recursos de LLVM
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);

    return 0;
}
