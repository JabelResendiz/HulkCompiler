//main.c

#include <stdio.h>
#include "ast/ast.h"
#include "check/check_semantic.h"
#include "llvm/codegen.h"


#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define RED "\033[31m"
#define CYAN "\033[36m"

extern int yyparse(void);
extern FILE *yyin;
extern ASTNode* root;

int main()
{
    yyin = fopen("script/let.hulk","r");

    if(!yyin)
    {
        perror("Error openin script.hulk");
        return 1;
    }

    if(!yyparse())
    {
        printf(BLUE "\n🌳 Abstract Syntax Tree:\n" RESET);
        print_ast(root, 0);

        printf(CYAN "\nGenerating LLVM code...\n" RESET);
        codegen_main(root, "./build/output.ll");
        printf(GREEN "✅ LLVM code generated succesfully in output.ll\n" RESET);
        
        free_ast(root);
        root = NULL;
    }

    return 0;
}