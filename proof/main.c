
// main.c

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "env.h"
#include "typecheck.h"
#include "eval.h"

extern int yyparse();
extern ASTNode *root;
extern void yy_scan_string(const char *);

int main()
{
    FILE *file = fopen("decl.hulk", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Reservar memoria para el contenido del archivo
    char *line = (char *)malloc(file_size + 1);
    if (line == NULL)
    {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    // Leer el contenido del archivo
    size_t len = fread(line, 1, file_size, file);
    line[len] = '\0'; // Asegurarse de que la cadena esté terminada en nulo

    fclose(file); // Cerrar el archivo

    // Pasar la expresión a yylex y yyparse
    yy_scan_string(line);         // Flex leerá la cadena
    int parse_result = yyparse(); // Iniciar el análisis sintáctico

    // Si no hubo error y el árbol fue generado, imprimir el AST
    if (parse_result == 0 && root != NULL)
    {
        printf("AST Structure:\n");

        print_ast(root, 0);

        // Crear entorno global y evaluar

        Env *global_env = create_env(NULL);

        

        // 1. Crear visitor de chequeo de tipos

        ASTVisitor typechecker = make_typechecker(global_env, NULL); // NULL = logger por defecto
        
       

        // 2. Aplicar el visitor

        ValueType result_type = root->accept(&typechecker,root);

       

        if (result_type == TYPE_UNKNOWN)
        {
            fprintf(stderr, "Type checking failed. Aborting evaluation.\n");
            free_ast(root);
            free_env(global_env);
            free(line);
            return 1;
        }

        ASTNode *result = eval(root, global_env);
        
        printf("\nEvaluated Result: ");
        if (result != NULL)
        {
            print_ast(result, 0); // O print_value(result), si usas Value*
        }
        else
        {
            printf("Evaluation returned NULL.\n");
        }

        if (result != root)
            free_ast(result);
        free_ast(root);       // Liberar AST original
        free_env(global_env); // Liberar entorno
    }
    else
    {
        printf("Parsing failed or no valid AST generated.\n");
    }

    free(line); // Liberar memoria del archivo leído
    return 0;
}
