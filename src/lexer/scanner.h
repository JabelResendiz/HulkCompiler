
#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include "tokenType.h"
#include <vector>
#include <string>

namespace HULK_LEXER
{
    class Scanner
    {
    private:
        std::string source; 
        int start;
        int current;
        int line;
        int col;

        std::vector<Token> tokens;

        bool isAtEnd();
        char advance();
        void scanToken();
        void addToken(TokenType type);
        char peek();
        bool match(char expected);
        void scanString();
        void scanNumber();
        void scanIdentifier();
        char peekNext();

    public:
        Scanner(std::string source);
        std::vector<Token> scanTokens();
    };

}

#endif