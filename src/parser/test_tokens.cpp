#include <vector>
#include "../lexer/token.h"
#include "../lexer/tokenType.h"

using namespace std;
using namespace HULK_LEXER;

// Function to generate test tokens for parser validation
vector<Token> generateTestTokens() {
    vector<Token> tokens;
    
    // Simple expression: 2 + 3;
    tokens.push_back(Token(TokenType::NUMBER, "2", 1, 1));
    tokens.push_back(Token(TokenType::PLUS, "+", 1, 3));
    tokens.push_back(Token(TokenType::NUMBER, "3", 1, 5));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 1, 6));
    
    // Let statement: let x = 10 in x * 2;
    tokens.push_back(Token(TokenType::LET, "let", 2, 1));
    tokens.push_back(Token(TokenType::IDENTIFIER, "x", 2, 5));
    tokens.push_back(Token(TokenType::ASSIGN, "=", 2, 7));
    tokens.push_back(Token(TokenType::NUMBER, "10", 2, 9));
    tokens.push_back(Token(TokenType::IN, "in", 2, 12));
    tokens.push_back(Token(TokenType::IDENTIFIER, "x", 2, 15));
    tokens.push_back(Token(TokenType::STAR, "*", 2, 17));
    tokens.push_back(Token(TokenType::NUMBER, "2", 2, 19));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 2, 20));
    
    // If-else expression: if x > 5 then "greater" else "smaller"
    tokens.push_back(Token(TokenType::IF, "if", 3, 1));
    tokens.push_back(Token(TokenType::IDENTIFIER, "x", 3, 4));
    tokens.push_back(Token(TokenType::GREATER, ">", 3, 6));
    tokens.push_back(Token(TokenType::NUMBER, "5", 3, 8));
    tokens.push_back(Token(TokenType::THEN, "then", 3, 10));
    tokens.push_back(Token(TokenType::STRING, "\"greater\"", 3, 15));
    tokens.push_back(Token(TokenType::ELSE, "else", 3, 25));
    tokens.push_back(Token(TokenType::STRING, "\"smaller\"", 3, 30));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 3, 39));
    
    // Function declaration: function add(a, b) => a + b;
    tokens.push_back(Token(TokenType::FUNCTION, "function", 4, 1));
    tokens.push_back(Token(TokenType::IDENTIFIER, "add", 4, 10));
    tokens.push_back(Token(TokenType::LPAREN, "(", 4, 13));
    tokens.push_back(Token(TokenType::IDENTIFIER, "a", 4, 14));
    tokens.push_back(Token(TokenType::COMMA, ",", 4, 15));
    tokens.push_back(Token(TokenType::IDENTIFIER, "b", 4, 17));
    tokens.push_back(Token(TokenType::RPAREN, ")", 4, 18));
    tokens.push_back(Token(TokenType::ARROW, "=>", 4, 20));
    tokens.push_back(Token(TokenType::IDENTIFIER, "a", 4, 23));
    tokens.push_back(Token(TokenType::PLUS, "+", 4, 25));
    tokens.push_back(Token(TokenType::IDENTIFIER, "b", 4, 27));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 4, 28));
    
    // Function call: add(5, 3);
    tokens.push_back(Token(TokenType::IDENTIFIER, "add", 5, 1));
    tokens.push_back(Token(TokenType::LPAREN, "(", 5, 4));
    tokens.push_back(Token(TokenType::NUMBER, "5", 5, 5));
    tokens.push_back(Token(TokenType::COMMA, ",", 5, 6));
    tokens.push_back(Token(TokenType::NUMBER, "3", 5, 8));
    tokens.push_back(Token(TokenType::RPAREN, ")", 5, 9));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 5, 10));
    
    // Print statement: print("Hello, world!");
    tokens.push_back(Token(TokenType::PRINT, "print", 6, 1));
    tokens.push_back(Token(TokenType::LPAREN, "(", 6, 6));
    tokens.push_back(Token(TokenType::STRING, "\"Hello, world!\"", 6, 7));
    tokens.push_back(Token(TokenType::RPAREN, ")", 6, 22));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 6, 23));
    
    // While statement: while (x > 0) { print(x); x = x - 1; }
    tokens.push_back(Token(TokenType::WHILE, "while", 7, 1));
    tokens.push_back(Token(TokenType::LPAREN, "(", 7, 7));
    tokens.push_back(Token(TokenType::IDENTIFIER, "x", 7, 8));
    tokens.push_back(Token(TokenType::GREATER, ">", 7, 10));
    tokens.push_back(Token(TokenType::NUMBER, "0", 7, 12));
    tokens.push_back(Token(TokenType::RPAREN, ")", 7, 13));
    tokens.push_back(Token(TokenType::LBRACE, "{", 7, 15));
    tokens.push_back(Token(TokenType::PRINT, "print", 7, 17));
    tokens.push_back(Token(TokenType::LPAREN, "(", 7, 22));
    tokens.push_back(Token(TokenType::IDENTIFIER, "x", 7, 23));
    tokens.push_back(Token(TokenType::RPAREN, ")", 7, 24));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 7, 25));
    tokens.push_back(Token(TokenType::IDENTIFIER, "x", 7, 27));
    tokens.push_back(Token(TokenType::ASSIGN, "=", 7, 29));
    tokens.push_back(Token(TokenType::IDENTIFIER, "x", 7, 31));
    tokens.push_back(Token(TokenType::MINUS, "-", 7, 33));
    tokens.push_back(Token(TokenType::NUMBER, "1", 7, 35));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 7, 36));
    tokens.push_back(Token(TokenType::RBRACE, "}", 7, 38));
    
    // For statement: for (i in range(1, 5)) { print(i); }
    tokens.push_back(Token(TokenType::FOR, "for", 8, 1));
    tokens.push_back(Token(TokenType::LPAREN, "(", 8, 5));
    tokens.push_back(Token(TokenType::IDENTIFIER, "i", 8, 6));
    tokens.push_back(Token(TokenType::IN, "in", 8, 8));
    tokens.push_back(Token(TokenType::RANGE, "range", 8, 11));
    tokens.push_back(Token(TokenType::LPAREN, "(", 8, 16));
    tokens.push_back(Token(TokenType::NUMBER, "1", 8, 17));
    tokens.push_back(Token(TokenType::COMMA, ",", 8, 18));
    tokens.push_back(Token(TokenType::NUMBER, "5", 8, 20));
    tokens.push_back(Token(TokenType::RPAREN, ")", 8, 21));
    tokens.push_back(Token(TokenType::RPAREN, ")", 8, 22));
    tokens.push_back(Token(TokenType::LBRACE, "{", 8, 24));
    tokens.push_back(Token(TokenType::PRINT, "print", 8, 26));
    tokens.push_back(Token(TokenType::LPAREN, "(", 8, 31));
    tokens.push_back(Token(TokenType::IDENTIFIER, "i", 8, 32));
    tokens.push_back(Token(TokenType::RPAREN, ")", 8, 33));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 8, 34));
    tokens.push_back(Token(TokenType::RBRACE, "}", 8, 36));
    
    // Complex expression with unary and binary operators: -(3 + 4) * 2;
    tokens.push_back(Token(TokenType::MINUS, "-", 9, 1));
    tokens.push_back(Token(TokenType::LPAREN, "(", 9, 2));
    tokens.push_back(Token(TokenType::NUMBER, "3", 9, 3));
    tokens.push_back(Token(TokenType::PLUS, "+", 9, 5));
    tokens.push_back(Token(TokenType::NUMBER, "4", 9, 7));
    tokens.push_back(Token(TokenType::RPAREN, ")", 9, 8));
    tokens.push_back(Token(TokenType::STAR, "*", 9, 10));
    tokens.push_back(Token(TokenType::NUMBER, "2", 9, 12));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 9, 13));
    
    // Boolean expressions: true && !false;
    tokens.push_back(Token(TokenType::TRUE, "true", 10, 1));
    tokens.push_back(Token(TokenType::AND, "&&", 10, 6));
    tokens.push_back(Token(TokenType::NOT, "!", 10, 9));
    tokens.push_back(Token(TokenType::FALSE, "false", 10, 10));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 10, 15));
    
    // Built-in function calls: sin(3.14) + sqrt(16);
    tokens.push_back(Token(TokenType::SIN, "sin", 11, 1));
    tokens.push_back(Token(TokenType::LPAREN, "(", 11, 4));
    tokens.push_back(Token(TokenType::NUMBER, "3.14", 11, 5));
    tokens.push_back(Token(TokenType::RPAREN, ")", 11, 9));
    tokens.push_back(Token(TokenType::PLUS, "+", 11, 11));
    tokens.push_back(Token(TokenType::SQRT, "sqrt", 11, 13));
    tokens.push_back(Token(TokenType::LPAREN, "(", 11, 17));
    tokens.push_back(Token(TokenType::NUMBER, "16", 11, 18));
    tokens.push_back(Token(TokenType::RPAREN, ")", 11, 20));
    tokens.push_back(Token(TokenType::SEMICOLON, ";", 11, 21));
    
    // End of file token
    tokens.push_back(Token(TokenType::TOKEN_EOF, "", 12, 1));
    
    return tokens;
}