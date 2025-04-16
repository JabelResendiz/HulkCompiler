// #include "scanner.h"

// namespace HULK_LEXER
// {
//     enum class State 
//     {
//         START,
//         IN_NUMBER,
//         IN_IDENTIFIER,
//         IN_STRING,
//         DONE,
//         IN_KEYWORD
//     };

//     Scanner::Scanner(std::string source)
//         : source(source), start(0), current(0), line(1), col(0) {}

//     bool Scanner::isAtEnd()
//     {
//         return current >= source.length();
//     }

//     char Scanner::advance()
//     {
//         col++;
//         return source[current++];
//     }

//     char Scanner::peek()
//     {
//         if (isAtEnd())
//             return '\0';
//         return source[current];
//     }

//     void Scanner::addToken(TokenType type)
//     {
//         std::string text = source.substr(start, current - start);
//         tokens.push_back(Token(type, text, line, col));
//     }

//     void Scanner::scanToken()
//     {
//         State state = State::START;

//         char c = advance();
//         switch (c)
//         {
//         case '(':
//             addToken(TokenType::LPAREN);
//             break;
//         case ')':
//             addToken(TokenType::RPAREN);
//             break;
//         case '{':
//             addToken(TokenType::LBRACE);
//             break;
//         case '}':
//             addToken(TokenType::RBRACE);
//             break;
//         case '[':
//             addToken(TokenType::LBRACKET);
//             break;
//         case ']':
//             addToken(TokenType::RBRACKET);
//             break;
//         case ',':
//             addToken(TokenType::COMMA);
//             break;
//         case ';':
//             addToken(TokenType::SEMICOLON);
//             break;
//         case '.':
//             addToken(TokenType::DOT);
//             break;
//         case '+':
//             addToken(TokenType::PLUS);
//             break;
//         case '-':
//             addToken(TokenType::PLUS);
//             break;
//         case '*':
//             addToken(TokenType::MULT);
//             break;
//         case '/':
//             addToken(TokenType::DIV);
//             break;
//         case '^':
//             addToken(TokenType::POW);
//             break;
//         case '%':
//             addToken(TokenType::MOD);
//             break;
//         case '&':
//             addToken(TokenType::AND);
//             break;
//         case '|':
//             addToken(TokenType::OR);
//             break;
//         case '@':
//             addToken(TokenType::AT);
//             break;

//         // Agrega más símbolos aquí...
//         case ' ':
//         case '\r':
//         case '\t':
//             // ignorar espacios en blanco
//             break;
//         case '\n':
//             line++;
//             col = 0;
//             break;
//         default:
//             // Caracter desconocido (puedes añadir manejo de errores aquí)
//             break;
//         }
//     }

//     std::vector<Token> Scanner::scanTokens()
//     {
//         while (!isAtEnd())
//         {
//             start = current;
//             scanToken();
//         }

//         tokens.push_back(Token(TokenType::TOKEN_EOF, "", line, col));
//         return tokens;
//     }

// }











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
        DONE
    };


    std::unordered_map<std::string,TokenType> keywords = {

        {"if" , TokenType::IF},
        {"else", TokenType::ELSE},
        {"while", TokenType::WHILE},
        {"for", TokenType::FOR},
    };


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
                    case '-':addToken(TokenType::MINUS);break;
                    case '*':addToken(TokenType::MULT);break;
                    case '/':addToken(TokenType::DIV);break;
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

                    auto it = keywords.find(text);
                    if (it != keywords.end())
                        addToken(it->second);

                    else addToken(TokenType::IDENTIFIER);
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