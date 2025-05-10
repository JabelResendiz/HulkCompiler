// #include <stdio.h>
// #include "ast.h"

// extern int yyparse();
// extern ASTNode *root;

// int main()
// {
//     printf("Enter expression:\n");
//     if (yyparse() == 0)
//     {
//         printf("Parsed successfully. AST:\n");
//         print_ast(root);
//         printf("\n");
//         // Aquí podrías llamar a análisis semántico y generación LLVM
//         free_ast(root);
//     }
//     return 0;
// }




// #include <stdio.h>
// #include "ast.h"

// extern int yyparse();
// extern ASTNode* root;

// int main() {
//     printf("Enter expression:\n");
//     yyparse();  // Analiza una expresión
//     if (root) {
//         printf("AST:\n");
//         print_ast(root);
//         printf("\n");  // Nueva línea al final para una mejor visualización
//         free_ast(root);  // Libera la memoria del AST
//     } else {
//         printf("Error parsing expression.\n");
//     }
//     return 0;
// }







#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yyparse();
extern ASTNode* root;

int main() {
    char* line = NULL;
    size_t len = 0;

    printf("Enter expression:\n");

    // Leer la expresión desde la entrada
    int read = getline(&line, &len, stdin);
    if (read == -1) {
        perror("Error reading input");
        return 1;
    }

    // Pasar la expresión a yylex y yyparse
    yy_scan_string(line);  // Flex leerá la línea
    int parse_result = yyparse(); // Iniciar el análisis sintáctico

    // Si no hubo error y el árbol fue generado, imprimir el AST
    if (parse_result == 0 && root != NULL) {
        printf("AST:\n");
        print_ast(root);
        free_ast(root);  // Liberar el árbol AST
    } else {
        printf("Parsing failed or no valid AST generated.\n");
    }

    free(line);  // Liberar la memoria utilizada para la entrada

    return 0;
}
