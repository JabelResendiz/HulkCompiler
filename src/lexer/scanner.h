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