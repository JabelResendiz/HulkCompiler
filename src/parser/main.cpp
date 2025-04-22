#include <iostream>
#include <fstream>
#include <sstream>
#include "../lexer/scanner.h"
#include "parser.h"

using namespace std;
using namespace HULK_LEXER;
using namespace HULK_PARSER;

int main() {
    // Read the input file
    ifstream file("example.hulk");
    if (!file.is_open()) {
        cerr << "Error: could not open the file." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();  
    string code = buffer.str();

    // Tokenize the input
    Scanner scanner(code);
    vector<Token> tokens = scanner.scanTokens();

    // Parse the tokens
    Parser parser(tokens);
    shared_ptr<Program> program = parser.parse();

    // Print the AST
    if (program) {
        cout << "Parsing successful!" << endl;
        cout << program->toString() << endl;
    } else {
        cout << "Parsing failed." << endl;
    }

    return 0;
}