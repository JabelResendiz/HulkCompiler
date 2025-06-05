#include "ast/ast.hpp"
#include <fstream>
#include <sstream>
#include <memory>

extern int yyparse();
extern std::unique_ptr<ASTNode> root;

int main() {
    // Leer el archivo
    std::ifstream file("decl.hulk");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    // Configurar el lexer y parser
    yy_scan_string(content.c_str());
    int parse_result = yyparse();

    if (parse_result == 0 && root) {
        std::cout << "AST Structure:\n";
        print_ast(root);
    } else {
        std::cerr << "Parsing failed or no valid AST generated." << std::endl;
    }

    return 0;
}