

#ifndef SCANNER2_H
#define SCANNER2_H

#include "token.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

namespace HULK_LEXER
{
    class NFAState
    {
    public:
        bool isFinal;
        TokenType finalType;

        std::unordered_map<char, std::vector<std::shared_ptr<NFAState>>> transitions;

        NFAState(bool isFinal = false, TokenType type = TokenType::UNKNOWN)
            : isFinal(isFinal), finalType(type) {}
    };

    class NFABuilder
    {
    public:
        static std::shared_ptr<NFAState> buildFromRegex(const std::string& regex,TokenType type);
        static std::shared_ptr<NFAState> buildCharacter(char  c,TokenType type);
        static std::shared_ptr<NFAState> buildAlternation(std::shared_ptr<NFAState> a, std::shared_ptr<NFAState> b);
        static std::shared_ptr<NFAState> buildConcatenation(std::shared_ptr<NFAState> a, std::shared_ptr<NFAState> b);
        static std::shared_ptr<NFAState> buildKleeneStar(std::shared_ptr<NFAState> a, TokenType type);
    };

    class Scanner
    {
        public :
        Scanner(std::string source);
        std::vector<Token>scanTokens();

        private:
        std::string source;
        size_t start;
        size_t current;
        int line;
        int col;
        std::vector<Token> tokens;

        std::unordered_map<TokenType, std::shared_ptr<NFAState>> nfaTable;


        void initializeNFATable();
        void scanToken();
        void isAtEnd();
        void advance();
        void peek();
        void peekNext();
        void match(char expected);
        void addToken(TokenType type);

        size_t simulateNFA (std::shared_ptr<NFAState> startState);
        Token tryMatchWithNFAs();

        void scanString();
        void scanNumber();
        void scanIdentifier();

        TokenType getKeywordType (const std::string& text);

    };

    
}

#endif