// scanner.cpp
#include "scanner_dfa.h"
#include <cctype>
#include <iostream>

using namespace HULK_LEXER;

Scanner::Scanner(std::string src)
    : source(std::move(src)), start(0), current(0), line(1), col(0) {
    initializeKeywords();
    buildDFAs();
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    col++;
    return source[current++];
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

void Scanner::addToken(TokenType type) {
    std::string lexeme = source.substr(start, current - start);
    tokens.push_back(Token(type, lexeme, line, start));
}

size_t Scanner::simulateDFA(DFAState* startState, TokenType& outType) {
    DFAState* currentState = startState;
    size_t pos = current;
    size_t lastAccept = current;
    TokenType lastType = TokenType::UNKNOWN;

    while (pos < source.length()) {
        char c = source[pos];
        if (currentState->transitions.count(c)) {
            currentState = currentState->transitions[c];
            pos++;
            if (currentState->isFinal) {
                lastAccept = pos;
                lastType = currentState->tokenType;
            }
        } else break;
    }

    if (lastType != TokenType::UNKNOWN) {
        outType = lastType;
        return lastAccept - current;
    }
    return 0;
}

void Scanner::buildDFAs() {
    // Example: simple DFA for numbers [0-9]+
    DFAState* start = new DFAState(false);
    DFAState* digit = new DFAState(true, TokenType::NUMBER);
    for (char c = '0'; c <= '9'; ++c) {
        start->transitions[c] = digit;
        digit->transitions[c] = digit;
    }
    dfaList.push_back({TokenType::NUMBER, start});

    // Example: identifier DFA [a-zA-Z_][a-zA-Z0-9_]*
    DFAState* idStart = new DFAState(false);
    DFAState* idBody = new DFAState(true, TokenType::IDENTIFIER);
    for (char c = 'a'; c <= 'z'; ++c) idStart->transitions[c] = idBody;
    for (char c = 'A'; c <= 'Z'; ++c) idStart->transitions[c] = idBody;
    idStart->transitions['_'] = idBody;
    for (char c = 'a'; c <= 'z'; ++c) idBody->transitions[c] = idBody;
    for (char c = 'A'; c <= 'Z'; ++c) idBody->transitions[c] = idBody;
    for (char c = '0'; c <= '9'; ++c) idBody->transitions[c] = idBody;
    idBody->transitions['_'] = idBody;
    dfaList.push_back({TokenType::IDENTIFIER, idStart});

    // Operators and symbols (1-character)
    const std::unordered_map<char, TokenType> singleCharSymbols = {
        {'+', TokenType::PLUS}, {'-', TokenType::MINUS}, {'*', TokenType::MULT},
        {'/', TokenType::DIV},  {'%', TokenType::MOD},   {'^', TokenType::POW},
        {'(', TokenType::LPAREN}, {')', TokenType::RPAREN},
        {'{', TokenType::LBRACE}, {'}', TokenType::RBRACE},
        {'[', TokenType::LBRACKET}, {']', TokenType::RBRACKET},
        {',', TokenType::COMMA}, {';', TokenType::SEMICOLON},
        {'.', TokenType::DOT},  {'&', TokenType::AND}, {'|', TokenType::OR},
        {'@', TokenType::AT},  {'!', TokenType::NOT},
        {'=', TokenType::ASSIGN}, {'<', TokenType::LT}, {'>', TokenType::GT},
        {':', TokenType::COLON}
    };

    for (const auto& [symbol, type] : singleCharSymbols) {
        DFAState* s = new DFAState(true, type);
        s->transitions[symbol] = new DFAState(true, type);
        dfaList.push_back({type, s});
    }

    // Compound symbols (e.g., ==, !=, >=, <=, =>, ->, :=, ::)
    std::vector<std::pair<std::string, TokenType>> compoundSymbols = {
        {"==", TokenType::EQ}, {"!=", TokenType::NEQ},
        {">=", TokenType::GTE}, {"<=", TokenType::LTE},
        {"=>", TokenType::ARROW}, {"->", TokenType::SIMPLE_ARROW},
        {":=", TokenType::DESTRUCTIVE_ASSIGN}, {"::", TokenType::DOUBLE_COLON}
    };

    for (const auto& [symbol, type] : compoundSymbols) {
        DFAState* start = new DFAState(false);
        DFAState* second = new DFAState(true, type);
        start->transitions[symbol[0]] = new DFAState(false);
        start->transitions[symbol[0]]->transitions[symbol[1]] = second;
        dfaList.push_back({type, start});
    }
}

void Scanner::initializeKeywords() {
    keywords = {
            {"if", TokenType ::IF},
            {"else", TokenType::ELSE},
            {"while",TokenType::WHILE},
            {"for",TokenType::FOR},
            {"print",TokenType::PRINT},
            {"let",TokenType::LET},
            {"in", TokenType::IN},
            {"elif", TokenType::ELIF},
            {"function" , TokenType::FUNCTION},
            {"True",TokenType::TRUE},
            {"False",TokenType::FALSE},
            {"type", TokenType::TYPE},
            {"protocol", TokenType::PROTOCOL},
            {"inherits",TokenType::INHERITS},
            {"invoke", TokenType::INVOKE},
            {"sin", TokenType::SIN},
            {"cos",TokenType::COS},
            {"sqrt",TokenType::SQRT},
            {"exp",TokenType::EXP},
            {"log",TokenType::LOG},
            {"rand",TokenType::RAND},
            {"range",TokenType::RANGE},
            {"extends", TokenType::EXTENDS},
            {"other",TokenType::OTHER},
            {"new", TokenType::NEW},
            {"base", TokenType::BASE},
            {"is", TokenType::IS},
            {"as", TokenType::AS}
    };
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        TokenType matchedType = TokenType::UNKNOWN;
        size_t longest = 0;

        for (auto& [type, dfa] : dfaList) {
            TokenType tempType;
            size_t len = simulateDFA(dfa, tempType);
            if (len > longest) {
                longest = len;
                matchedType = tempType;
            }
        }

        if (longest > 0) {
            current += longest;

            // Si es IDENTIFIER, verificar si es palabra clave
            if (matchedType == TokenType::IDENTIFIER) {
                std::string lexeme = source.substr(start, current - start);
                auto it = keywords.find(lexeme);
                if (it != keywords.end()) {
                    matchedType = it->second;
                }
            }

            addToken(matchedType);
        } else {
            std::cerr << "[Line " << line << "] Unexpected character: '" << peek() << "'\n";
            advance();
        }
    }

    tokens.push_back(Token(TokenType::TOKEN_EOF, "", line, col));
    return tokens;
}
