
#ifndef TOKEN_H
#define TOKEN_H

#include "tokenType.h"

namespace HULK_LEXER
{
    class Token
    {
        public:
            TokenType type;
            std::string lexeme;
            int line;
            int col;

            Token(TokenType type, std::string lexeme,
                int line, int col)
                : type(type), lexeme(lexeme), line(line), col(col) {}

            std::string toString() const
            {
                return std::to_string(type) + " " + lexeme + " " +std::to_string(line) + " " + std::to_string(col);
            }
    };
}

#endif