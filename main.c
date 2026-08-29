#include <stdio.h>
#include "./ast/ast.h"
#include "./codegen/codegen.h"
#include "./semantic_check/semantic.h"
#include "./utils/colors.h"
#include "./utils/logger.h"

extern int yyparse(void);
extern FILE *yyin;
extern ASTNode *root;

/* ================== CONFIG ==================*/

#define DEFAULT_INPUT "script.hulk"
#define DEFAULT_OUTPUT "./build/output.ll"
#define DEFAULT_LOG "./build/hulk.log"

char input_file[256] = DEFAULT_INPUT;
char output_file[256] = DEFAULT_OUTPUT;
char log_file[256] = DEFAULT_LOG;

void load_config(const char* filename)
{
    FILE *f = fopen(filename,"r");
    if(!f)
    {
        printf(YELLOW "No config file found (%s), using defaults\n" RESET, filename);
        return;
    }

    char line[512];
    while(fgets(line, sizeof(line), f)) {
        char key[128], value[256];

        if (sscanf(line, "%127[^=]=%255s", key, value) == 2) {
            if (strcmp(key, "input") == 0)
                strncpy(input_file, value, sizeof(input_file));
            else if (strcmp(key, "output") == 0)
                strncpy(output_file, value, sizeof(output_file));
        }
    }

    fclose(f);

}

/* ========================================= */

int main(int argc, char* argv[])
{
    logger_init(log_file);
    LOG_INFO("Hulk Compiler started");

    load_config("conf/hulk.conf");
    LOG_DEBUG("Config loaded from conf/hulk.conf");

    if (argc > 1){
        strncpy(input_file, argv[1], sizeof(input_file));
        LOG_INFO("Input overridden by CLI: %s", input_file);
    }
        
    printf(CYAN "Input file: %s\n" RESET, input_file);
    printf(CYAN "Output file: %s\n" RESET, output_file);

    /* Open input file */
    LOG_INFO("Opening input file");
    yyin = fopen(input_file, "r");
    if (!yyin)
    {
        LOG_ERROR("Cannot open input file");
        perror("Error opening input file");
        return 1;
    }

    /*Parse + semantic */
    LOG_INFO("Parsing started");
    printf("Parsing staarted\n");
    if(yyparse())
    {
        LOG_ERROR("Parser failed");
        return 1;
    }
    LOG_INFO("Parsing OK");

    LOG_INFO("Semantic analysis started");
    if(analyze_semantics(root))
    {
        LOG_ERROR("Semantic error");
        return 1;
    }

    LOG_INFO("Semantic analysis OK");

    LOG_DEBUG("🌳 Abstract Syntax Tree:");
    print_ast(root, 0);

    LOG_INFO("Generating LLVM IR code ...");
    compile_to_llvm(root, output_file);
    LOG_INFO("✅ LLVM code generated succesfully in : %s", output_file);

    free_ast(root);
    root= NULL;
    LOG_DEBUG("AST freed");

    LOG_INFO("Compiler finished");
    logger_close();

    // if (!yyparse() && !analyze_semantics(root))
    // {
    //     fclose(yyin);

    //     printf(BLUE "\n🌳 Abstract Syntax Tree:\n" RESET);
    //     print_ast(root, 0);

    //     printf(CYAN "\nGenerating LLVM code...\n" RESET);
    //     compile_to_llvm(root, output_file);
    //     printf(GREEN "✅ LLVM code generated succesfully in %s\n" RESET, output_file);

    //     free_ast(root);
    //     root = NULL;
    // }

    return 0;
}