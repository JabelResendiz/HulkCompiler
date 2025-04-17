

#include <iostream>
#include <fstream>
#include <sstream>
#include "scanner.h"

using namespace std;
using namespace HULK_LEXER;


int main()
{
    ifstream file("example.hulk");
    if (!file.is_open())
    {
        cerr << "Error: no se pudo abrir el archivo." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();  
    string code = buffer.str();

    Scanner scanner(code);

    vector<Token> tokens = scanner.scanTokens();

    for (const Token& token: tokens)
    {
        cout<< token.toString() <<endl;
    }

    return 0;
}
