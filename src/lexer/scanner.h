
// #ifndef SCANNER_H
// #define SCANNER_H

// #include "token.h"
// #include "tokenType.h"
// #include <vector>
// #include <string>

// namespace HULK_LEXER
// {
//     class Scanner
//     {
//     private:
//         std::string source; 
//         int start;
//         int current;
//         int line;
//         int col;

//         std::vector<Token> tokens;

//         bool isAtEnd();
//         char advance();
//         void scanToken();
//         void addToken(TokenType type);
//         char peek();
//         bool match(char expected);
//         void scanString();
//         void scanNumber();
//         void scanIdentifier();
//         char peekNext();

//     public:
//         Scanner(std::string source);
//         std::vector<Token> scanTokens();
//     };

// }

// #endif


























#ifndef DFA_SCANNER_H
#define DFA_SCANNER_H

#include "token.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace HULK_LEXER
{

    class DFAScanner
    {
    public:
        DFAScanner(std::string source);
        std::vector<Token> scanTokens();

    private:
        enum class DFAState
        {
            START,
            IN_IDENTIFIER,
            IN_NUMBER,
            IN_NUMBER_DECIMAL,
            IN_STRING,
            IN_STRING_SCAPE,
            IN_COMMENT,
            IN_FIRST_SLASH,
            IN_OPERATOR,
            ERROR,
            ACCEPT
        };

        using DFATransitionTable = std::unordered_map<DFAState, std::unordered_map<char, DFAState>>;

        std::string source;
        size_t current_pos;
        int line;
        int column;
        std::vector<Token> tokens;
        DFATransitionTable transition_table;

        void initializeDFATable();
        Token scanNextToken();
        DFAState getNextState(DFAState current, char c) const;
        TokenType getTokenTypeForState(DFAState state, const std::string &lexeme) const;
        TokenType getKeywordType(const std::string &text) const;
        char advance();
        char peek() const;
        bool isAtEnd() const;
    };

}

#endif