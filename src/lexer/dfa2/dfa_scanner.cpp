#include "dfa_scanner.h"
#include <cctype>

namespace HULK_LEXER
{

    DFAScanner::DFAScanner(std::string source)
        : source(std::move(source)), current_pos(0), line(1), column(1)
    {
        initializeDFATable();
    }

    void DFAScanner::initializeDFATable()
    {
        // TRANSICIONES desde START
        transition_table[DFAState::START] = {};
        auto &start_transitions = transition_table[DFAState::START];

        // Identificadores [a-zA-Z_]
        for (char c = 'a'; c <= 'z'; ++c)
            start_transitions[c] = DFAState::IN_IDENTIFIER;
        for (char c = 'A'; c <= 'Z'; ++c)
            start_transitions[c] = DFAState::IN_IDENTIFIER;
        start_transitions['_'] = DFAState::IN_IDENTIFIER;

        // Números [0-9]
        for (char c = '0'; c <= '9'; ++c)
            start_transitions[c] = DFAState::IN_NUMBER;

        // Strings
        start_transitions['"'] = DFAState::IN_STRING;

        // Operadores y símbolos
        start_transitions['-'] = DFAState::IN_OPERATOR;
        start_transitions['='] = DFAState::IN_OPERATOR;
        start_transitions['>'] = DFAState::IN_OPERATOR;
        start_transitions['<'] = DFAState::IN_OPERATOR;
        start_transitions['!'] = DFAState::IN_OPERATOR;
        start_transitions[':'] = DFAState::IN_OPERATOR;
        
        start_transitions['.'] = DFAState::ACCEPT;
        start_transitions[';'] = DFAState::ACCEPT;
        start_transitions[',']= DFAState::ACCEPT;
        start_transitions['+'] = DFAState::ACCEPT;
        start_transitions['*'] = DFAState::ACCEPT;
        start_transitions['%'] = DFAState::ACCEPT;
        start_transitions['^'] = DFAState::ACCEPT;
        start_transitions['&'] = DFAState::ACCEPT;
        start_transitions['|'] = DFAState::ACCEPT;
        start_transitions['@'] = DFAState::ACCEPT;
        start_transitions['('] = DFAState::ACCEPT;
        start_transitions[')'] = DFAState::ACCEPT;
        start_transitions['['] = DFAState::ACCEPT;
        start_transitions[']'] = DFAState::ACCEPT;
        start_transitions['{'] = DFAState::ACCEPT;
        start_transitions['}'] = DFAState::ACCEPT;

        start_transitions['/'] = DFAState::IN_FIRST_SLASH;

        // TRANSICIONES desde FIRST_SLASH
        transition_table[DFAState::IN_FIRST_SLASH] = {};
        auto &slash_trans = transition_table[DFAState::IN_FIRST_SLASH];

        slash_trans['/'] = DFAState::IN_COMMENT;

        // TRANSICIONES desde IN_OPERATOR
        transition_table[DFAState::IN_OPERATOR] = {};
        auto &op_transitions = transition_table[DFAState::IN_OPERATOR];

        op_transitions['='] = DFAState::ACCEPT;
        op_transitions['>'] = DFAState::ACCEPT;
        op_transitions[':'] = DFAState::ACCEPT;

        // TRANSICIONES desde IN_IDENTIFIER
        transition_table[DFAState::IN_IDENTIFIER] = {};
        auto &id_transitions = transition_table[DFAState::IN_IDENTIFIER];
        for (char c = 'a'; c <= 'z'; ++c)
            id_transitions[c] = DFAState::IN_IDENTIFIER;
        for (char c = 'A'; c <= 'Z'; ++c)
            id_transitions[c] = DFAState::IN_IDENTIFIER;
        for (char c = '0'; c <= '9'; ++c)
            id_transitions[c] = DFAState::IN_IDENTIFIER;
        id_transitions['_'] = DFAState::IN_IDENTIFIER;

        // TRANSICIONES desde IN_NUMBER
        transition_table[DFAState::IN_NUMBER] = {};
        auto &num_transitions = transition_table[DFAState::IN_NUMBER];
        for (char c = '0'; c <= '9'; ++c)
            num_transitions[c] = DFAState::IN_NUMBER;
        num_transitions['.'] = DFAState::IN_NUMBER_DECIMAL;

        // TRANSICIONES desde IN_NUMBER_DECIMAL
        transition_table[DFAState::IN_NUMBER_DECIMAL] = {};
        auto &decimal_transitions = transition_table[DFAState::IN_NUMBER_DECIMAL];
        for (char c = '0'; c <= '9'; ++c)
            decimal_transitions[c] = DFAState::IN_NUMBER_DECIMAL;

        // TRANSICIONES desde IN_STRING
        transition_table[DFAState::IN_STRING] = {};
        auto &str_transitions = transition_table[DFAState::IN_STRING];
        for (int c = 0; c <= 127; ++c)
        {
            if (c != '"' && c != '\\')
                str_transitions[static_cast<char>(c)] = DFAState::IN_STRING;
        }
        str_transitions['"'] = DFAState::ACCEPT;
        str_transitions['\\'] = DFAState::IN_STRING_SCAPE;

        // TRANSICIONES desde IN_STRING_SCAPE
        transition_table[DFAState::IN_STRING_SCAPE] = {};
        auto &scape_trans = transition_table[DFAState::IN_STRING_SCAPE];

        scape_trans['n'] = DFAState::IN_STRING;
        scape_trans['t'] = DFAState::IN_STRING;
        scape_trans['"'] = DFAState::IN_STRING;
        scape_trans['\\'] = DFAState::IN_STRING;
        scape_trans['r'] = DFAState::IN_STRING;
    }

    TokenType DFAScanner::getKeywordType(const std::string &text) const
    {
        static const std::unordered_map<std::string, TokenType> keywords =
            {
                {"if", TokenType ::IF},
                {"else", TokenType::ELSE},
                {"while", TokenType::WHILE},
                {"for", TokenType::FOR},
                {"print", TokenType::PRINT},
                {"let", TokenType::LET},
                {"in", TokenType::IN},
                {"elif", TokenType::ELIF},
                {"function", TokenType::FUNCTION},
                {"True", TokenType::TRUE},
                {"False", TokenType::FALSE},
                {"type", TokenType::TYPE},
                {"protocol", TokenType::PROTOCOL},
                {"inherits", TokenType::INHERITS},
                {"invoke", TokenType::INVOKE},
                {"sin", TokenType::SIN},
                {"cos", TokenType::COS},
                {"sqrt", TokenType::SQRT},
                {"exp", TokenType::EXP},
                {"log", TokenType::LOG},
                {"rand", TokenType::RAND},
                {"range", TokenType::RANGE},
                {"extends", TokenType::EXTENDS},
                {"other", TokenType::OTHER},
                {"new", TokenType::NEW},
                {"base", TokenType::BASE},
                {"is", TokenType::IS},
                {"as", TokenType::AS}};

        auto it = keywords.find(text);

        return (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
    }

    char DFAScanner::advance()
    {
        column++;
        return source[current_pos++];
    }

    char DFAScanner::peek() const
    {
        if (isAtEnd())
            return '\0';
        return source[current_pos];
    }

    bool DFAScanner::isAtEnd() const
    {
        return current_pos >= source.length();
    }

    Token DFAScanner::scanNextToken()
    {
        // nucleo del escaneo
        DFAState current_state = DFAState::START;
        DFAState last_accept_state = DFAState::ERROR;
        size_t start_pos = current_pos;
        size_t last_accept_pos = current_pos;

        while (!isAtEnd())
        {
            char c = peek();
            DFAState next_state = getNextState(current_state, c);

            if (next_state == DFAState::ERROR)
            {
                break;
            }

            advance();
            current_state = next_state;

            if (current_state == DFAState::ACCEPT ||
                transition_table.count(current_state) > 0)
            {
                last_accept_state = current_state;
                last_accept_pos = current_pos;
            }
        }

        if (last_accept_state != DFAState::ERROR)
        {
            std::string lexeme = source.substr(start_pos, last_accept_pos - start_pos);
            current_pos = last_accept_pos;
            column += lexeme.length();

            TokenType type = getTokenTypeForState(last_accept_state, lexeme);
            return Token(type, lexeme, line, column - lexeme.length());
        }

        // Manejo de error
        char c = advance();
        return Token(TokenType::UNKNOWN, std::string(1, c), line, column - 1);
    }

    DFAScanner::DFAState DFAScanner::getNextState(DFAState current, char c) const
    {
        auto state_it = transition_table.find(current);
        if (state_it == transition_table.end())
        {
            return DFAState::ERROR;
        }

        auto char_it = state_it->second.find(c);
        if (char_it == state_it->second.end())
        {
            // Verificar clases de caracteres
            if (current == DFAState::IN_IDENTIFIER && isalnum(c))
            {
                return DFAState::IN_IDENTIFIER;
            }
            return DFAState::ERROR;
        }

        return char_it->second;
    }

    TokenType DFAScanner::getTokenTypeForState(DFAState state, const std::string &lexeme) const
    {
        switch (state)
        {
        case DFAState::IN_IDENTIFIER:
            return getKeywordType(lexeme);
        case DFAState::IN_NUMBER: return TokenType::NUMBER;
        case DFAState::IN_NUMBER_DECIMAL: // 12. seria un valor correcto 

            if (lexeme.back()== '.')
                return TokenType::UNKNOWN;
            
            return TokenType::NUMBER;

        // case DFAState::IN_STRING:
        //     return TokenType::STRING;

        case DFAState::ACCEPT:
            if (lexeme == "==")
                return TokenType::EQ;
            if (lexeme == "!=")
                return TokenType::NEQ;
            if (lexeme == "<=")
                return TokenType::LTE;
            if (lexeme == ">=")
                return TokenType::GTE;
            if (lexeme == ":=")
                return TokenType::DESTRUCTIVE_ASSIGN;
            if (lexeme == "=>")
                return TokenType::ARROW;
            if (lexeme == "->")
                return TokenType::SIMPLE_ARROW;
            if (lexeme == "::")
                return TokenType::DOUBLE_COLON;

            if (lexeme == "=")
                return TokenType::ASSIGN;
            if (lexeme == "!")
                return TokenType::NOT;
            if (lexeme == "<")
                return TokenType::LT;
            if (lexeme == ">")
                return TokenType::GT;
            if (lexeme == "+")
                return TokenType::PLUS;
            if (lexeme == "-")
                return TokenType::MINUS;
            if (lexeme == "*")
                return TokenType::MULT;
            // if (lexeme == "/")
            //     return TokenType::DIV;
            if (lexeme == ":")
                return TokenType::COLON;
            if (lexeme == ".")
                return TokenType::DOT;
            if (lexeme == ";")
                return TokenType::SEMICOLON;
            if (lexeme == ",")
                return TokenType::COMMA;
            if (lexeme == "@")
                return TokenType::AT;
            if (lexeme =="%")
                return TokenType::MOD;
            if(lexeme=="&")
                return TokenType::AND;
            if (lexeme=="|")
                return TokenType::OR;
            if (lexeme =="^")
                return TokenType::POW;

            // Símbolos y otros
            if (lexeme == "(")
                return TokenType::LPAREN;
            if (lexeme == ")")
                return TokenType::RPAREN;
            if (lexeme == "[")
                return TokenType::LBRACKET;
            if (lexeme == "]")
                return TokenType::RBRACKET;
            if (lexeme == "{")
                return TokenType::LBRACE;
            if (lexeme == "}")
                return TokenType::RBRACE;
            

            if (lexeme.front()=='"' && lexeme.back() == '"')
            {
                return TokenType::STRING;
            }

            
        case DFAState::IN_COMMENT:
            return TokenType::COMMENT;
        
        case DFAState::IN_FIRST_SLASH:
            return TokenType::DIV;

        default:
            return TokenType::UNKNOWN;
        }
    }

    std::vector<Token> DFAScanner::scanTokens()
    {
        while (!isAtEnd())
        {
            Token token = scanNextToken();
            if (token.type != TokenType::UNKNOWN)
            {
                tokens.push_back(token);
            }

            // Manejo de saltos de línea
            if (!isAtEnd() && peek() == '\n')
            {
                advance();
                line++;
                column = 1;
            }
        }

        tokens.push_back(Token(TokenType::TOKEN_EOF, "", line, column));
        return tokens;
    }

}