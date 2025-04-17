#include "scanner.h"
#include <unordered_map>
#include <string>
#include <cctype>

namespace HULK_LEXER
{
    enum class State 
    {
        START,
        IN_NUMBER,
        IN_IDENTIFIER,
        IN_STRING,
        IN_COMMENT,
        ERROR,
        DONE
    };

    TokenType getKeywordType(const std:: string& text)
    {
        static const std::unordered_map<std::string,TokenType> keywords = {
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


        auto it = keywords.find(text);
        if (it != keywords.end())
            return it->second;
        
            else return TokenType::IDENTIFIER;
    }
    


    Scanner::Scanner(std::string source)
        : source(source), start(0), current(0), line(1), col(0) {}
    
    bool Scanner::isAtEnd()
    {
        return current >= source.length();
    }
        
    char Scanner::advance()
    {
        col++;
        return source[current++];
    }

    char Scanner::peek()
    {
        if (isAtEnd())
            return '\0';
        return source[current];
    }


    bool Scanner::match(char expected)
    {
        if (isAtEnd() || source[current] != expected)
            return false;
        
            current ++;
            col ++;

            return true;
    }

    void Scanner::scanString()
    {
        while(peek() != '"' && !isAtEnd())
        {
            if (peek() == '\n')
            {
                line ++;
                col =0;
            }

            advance();
        }

        if (isAtEnd())
            return ;

        advance();
        addToken(TokenType::STRING);
    }


    void Scanner::scanNumber()
    {
        while(std::isdigit(peek())) advance();

        if (peek() == '.' && std::isdigit(peekNext()))
        {
            advance();
            while(std::isdigit(peek()))advance();
        }

        addToken(TokenType::NUMBER);
    }

    void Scanner::scanIdentifier()
    {
        while(std::isalnum(peek()) || peek() == '_')advance();
        
        std::string text = source.substr(start,current-start);

        TokenType type = getKeywordType(text);

        addToken(type);
    }

    char Scanner::peekNext()
    {
        if (current +1 >= source.length()) return '\0';

        return source[current +1];
    }

    void Scanner::addToken(TokenType type)
    {
        std::string lexeme = source.substr(start,current - start);
        
        tokens.push_back(Token(type,lexeme,line,start));

    }

    std ::vector<Token> Scanner::scanTokens()
    {

        while(!isAtEnd())
        {
            start = current;
            scanToken();
        }

        tokens.push_back(Token(TokenType::TOKEN_EOF,"", line,col));

        return tokens;
    }

    void Scanner::scanToken()
    {
        State state = State::START;

        while(!isAtEnd() && state != State::DONE)
        {
            char c = peek();

            switch (state)
            {
            case State::START:
                if (isdigit(c))
                {
                    state = State::IN_NUMBER;
                    advance();
                }

                else if(isalpha(c) || c == '_')
                {
                    state = State::IN_IDENTIFIER;
                    advance();
                }
                else if (c == '"')
                {
                    state = State::IN_STRING;
                    advance();
                }

                else
                {
                    advance();

                    switch (c)
                    {

                    case '>':
                        if (peek() == '=')
                        {
                            advance();
                            addToken(TokenType::GTE);
                        }
                        else addToken(TokenType::GT);
                        break;

                    case '<':
                        if (peek() == '=')
                        {
                            advance();
                            addToken(TokenType::LTE);
                        }
                        else addToken(TokenType::LT);
                        break;
                    
                    case '=':
                        if (peek() == '=')
                        {
                            advance();
                            addToken(TokenType::EQ);
                        }
                        else if (peek()== '>')
                        {
                            advance();
                            addToken(TokenType::ARROW);
                        } 
                        else addToken(TokenType::ASSIGN);
                        break;

                    case '-':
                        if(peek()== '>')
                        {
                            advance();
                            addToken(TokenType::SIMPLE_ARROW);
                        }
                        else addToken(TokenType::MINUS);
                        break;

                    case '/':
                        if(peek()== '/')
                        {
                            advance();
                            addToken(TokenType::COMMENT);
                        }
                        else addToken(TokenType::DIV);
                        break;
                    
                    case '!':
                        if (peek() == '=')
                        {
                            advance();
                            addToken(TokenType::NEQ);
                        }
                        else addToken(TokenType::NOT);
                        break;
                    
                    case ':':
                        if (peek() == '=')
                        {
                            advance();
                            addToken(TokenType::DESTRUCTIVE_ASSIGN);
                        }
                        else if (peek()== ':')
                        {
                            advance();
                            addToken(TokenType::DOUBLE_COLON);
                        }
                         addToken(TokenType::COLON);
                        break;



                    case '(': addToken(TokenType::LPAREN);break;
                    case ')':addToken(TokenType::RPAREN);break;
                    case '{':addToken(TokenType::LBRACE);break;
                    case '}':addToken(TokenType::RBRACE);break;
                    case '[':addToken(TokenType::LBRACKET);break;
                    case ']':addToken(TokenType::RBRACKET);break;
                    case ',':addToken(TokenType::COMMA);break;
                    case ';':addToken(TokenType::SEMICOLON);break;
                    case '.':addToken(TokenType::DOT);break;
                    case '+':addToken(TokenType::PLUS);break;
                    case '*':addToken(TokenType::MULT);break;
                    case '^':addToken(TokenType::POW);break;
                    case '%':addToken(TokenType::MOD);break;
                    case '&':addToken(TokenType::AND);break;
                    case '|':addToken(TokenType::OR);break;
                    case '@':addToken(TokenType::AT);break;
                    case ' ':
                    case '\r':
                    case '\t': break;
                    case '\n':
                        line++;
                        col =0;
                        break;
                    default:
                        break;
                    }
                    state = State::DONE;
                }
                break;
            

            case State::IN_NUMBER:
                if(isdigit(c) || c=='.')
                {
                    advance();
                } else {
                    state = State::DONE;
                    addToken(TokenType::NUMBER);
                }
                break;
            
            case State::IN_IDENTIFIER:
                if(isalnum(c) || c=='_'){
                    advance();
                }else {
                    state = State::DONE;
                    std::string text = source.substr(start,current - start);

                    addToken(TokenType(getKeywordType(text)));
                }
                break;
            
            case State::IN_STRING:
                if (c == '"')
                {
                    advance();
                    state = State::DONE;
                    addToken(TokenType::STRING);
                }

                else {
                    if (c == '\n')
                    {
                        line++;
                        col =0;
                    }
                    advance();
                }

                break;


            default:
                break;
            }
        }

        if(state == State::IN_NUMBER)addToken(TokenType::NUMBER);
        if(state == State::IN_IDENTIFIER)addToken(TokenType::IDENTIFIER);
        if(state == State::IN_STRING)addToken(TokenType::STRING);


    }
}



