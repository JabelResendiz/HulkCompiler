
// // main.c

// #include <stdio.h>
// #include <stdlib.h>
// #include "ast.h"

// extern int yyparse();
// extern ASTNode* root;

// int main() {
//     char* line = NULL;
//     size_t len = 0;

//     printf("Enter expression:\n");

//     int read = getline(&line, &len, stdin);
//     if (read == -1) {
//         perror("Error reading input");
//         return 1;
//     }

//     // Pasar la expresión a yylex y yyparse
//     yy_scan_string(line);  
//     int parse_result = yyparse(); 

//     // Si no hubo error y el árbol fue generado, imprimir el AST
//     if (parse_result == 0 && root != NULL) {
//         printf("AST Structure :\n");
//         print_ast(root,0);
//         free_ast(root);  
//     } else {
//         printf("Parsing failed or no valid AST generated.\n");
//     }

//     free(line);  

//     return 0;
// }



// main.c

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yyparse();
extern ASTNode* root;

int main() {
    // Abrir el archivo "example.hulk" en el mismo directorio
    FILE *file = fopen("example.hulk", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Reservar memoria para el contenido del archivo
    char *line = (char *)malloc(file_size + 1);
    if (line == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    // Leer el contenido del archivo
    size_t len = fread(line, 1, file_size, file);
    line[len] = '\0';  // Asegurarse de que la cadena esté terminada en nulo

    fclose(file);  // Cerrar el archivo

    // Pasar la expresión a yylex y yyparse
    yy_scan_string(line);  // Flex leerá la cadena
    int parse_result = yyparse(); // Iniciar el análisis sintáctico

    // Si no hubo error y el árbol fue generado, imprimir el AST
    if (parse_result == 0 && root != NULL) {
        printf("AST Structure :\n");
        print_ast(root, 0);
        free_ast(root);  // Liberar el árbol AST
    } else {
        printf("Parsing failed or no valid AST generated.\n");
    }

    free(line);  // Liberar la memoria utilizada para el contenido del archivo

    return 0;
}

