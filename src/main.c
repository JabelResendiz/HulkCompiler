
// main.c

#include <stdio.h>
#include "ast/ast.h"
#include "check/check_semantic.h"
#include "llvm/codegen.h"
#include "utils/print_utils.h"

extern int yyparse(void);
extern FILE *yyin;
extern ASTNode *root;

int main()
{
    yyin = fopen("script/script.hulk", "r");

    if (!yyin)
    {
        print_error("Error opening script.hulk");
        return 1;
    }

    if (!yyparse())
    {
        print_title("Abstract Syntax Tree:");
        print_ast(root, 0);

        print_title("🔍 Syntactic Analyzer");
        
        if (!make_checker(root))
        {
            print_success("Syntax is correct");
            print_info("Generating LLVM code...");
            // codegen_main(root, "./build/output.ll");

            print_success("LLVM code generated successfully in output.ll");

            // free_ast(root);
            // root = NULL;
        }

        else
        {
            print_error("❌ Syntax error detected");
        }
    }

    free_ast(root);
    root = NULL;

    return 0;
}
