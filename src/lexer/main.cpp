

#include <iostream>
#include "scanner.h"

using namespace std;
using namespace HULK_LEXER;


int main()
{
    string code = "(1+2) - 3";

    Scanner scanner(code);

    vector<Token> tokens = scanner.scanTokens();

    for (const Token& token: tokens)
    {
        cout<< token.toString() <<endl;
    }

    return 0;
}
