// scanner.h
#ifndef SCANNER_DFA_H
#define SCANNER_DFA_H

#include "../token.h"
#include "../tokenType.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace HULK_LEXER {

    struct DFAState {
        bool isFinal;
        TokenType tokenType;
        std::unordered_map<char, DFAState*> transitions;

        DFAState(bool isFinal = false, TokenType type = TokenType::UNKNOWN)
            : isFinal(isFinal), tokenType(type) {}
    };

    class Scanner {
    private:
        std::string source;
        int start;
        int current;
        int line;
        int col;

        std::vector<Token> tokens;
        std::vector<std::pair<TokenType, DFAState*>> dfaList;
        std::unordered_map<std::string, TokenType> keywords;


        bool isAtEnd();
        char advance();
        char peek();
        void addToken(TokenType type);
        size_t simulateDFA(DFAState* startState, TokenType& outType);
        void buildDFAs();
        void initializeKeywords();
        
    public:
        Scanner(std::string source);
        std::vector<Token> scanTokens();
    };

}

#endif
