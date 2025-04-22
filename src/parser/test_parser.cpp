#include <iostream>
#include <vector>
#include "../lexer/token.h"
#include "parser.h"
#include "test_tokens.cpp"

using namespace std;
using namespace HULK_LEXER;
using namespace HULK_PARSER;

int main() {
    // Generate test tokens
    vector<Token> tokens = generateTestTokens();
    
    cout << "Generated " << tokens.size() << " test tokens." << endl;
    
    // Print the tokens for verification
    cout << "\nToken list:" << endl;
    for (size_t i = 0; i < tokens.size(); i++) {
        cout << i << ": " << tokens[i].lexeme << " (Type: " << static_cast<int>(tokens[i].type) 
             << ", Line: " << tokens[i].line << ", Col: " << tokens[i].col << ")" << endl;
    }
    
    // Parse the tokens
    cout << "\nParsing tokens..." << endl;
    Parser parser(tokens);
    shared_ptr<Program> program = parser.parse();
    
    // Print the AST
    if (program) {
        cout << "\nParsing successful!" << endl;
        cout << "\nAbstract Syntax Tree:" << endl;
        cout << program->toString() << endl;
    } else {
        cout << "\nParsing failed." << endl;
    }
    
    return 0;
}