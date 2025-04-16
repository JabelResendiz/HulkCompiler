

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H // evitar incluir el archivo token.h mas de una vez
#include <string>

namespace HULK_LEXER
{

    enum TokenType
    {
        // Palabras clave
        PRINT,
        LET,
        IN,
        IF,
        ELSE,
        ELIF,
        WHILE,
        FOR,
        FUNCTION,
        TRUE,
        FALSE,

        TYPE,
        PROTCOL,
        EXTENDS,
        OTHER,
        NEW,
        INHERITS,
        BASE,
        IS,
        AS,

        START, // (?) revisar la seccion 15

        INVOKE,

        // FUNCTIONS
        SIN,
        COS,
        SQRT,
        EXP,
        LOG,
        RAND,

        RANGE, //  (?) revisar la seccion 15

        // Literales
        IDENTIFIER,
        AUTOMATIC_PARAMETER, // (?) revisar la seccion 17
        NUMBER,
        STRING,
        BOOLEAN,

        // CONSTANTS
        PI,
        E,

        // Operadores
        PLUS, // +
        MINUS, // -
        MULT,  // *
        DIV,   // /
        MOD,   // %
        POW,   // ^
        EQ,  // ==
        NEQ, // !=
        LT,  // <
        GT,  // >
        LTE, // <=
        GTE, // >=
        AND, // &
        OR,  // |

        // (?) HAY UN SIMBOLO DE "|"" DEFINIDO EN SECTION 16 , PARA SINTAXIS DE VECTORES

        NOT,    // !
        ASSIGN, // =
        AT,     // operador @

        DESTRUCTIVE_ASSIGN, // :=
        ARROW,              // =>
        SIMPLE_ARROW,       // ->
        COLON,              // :
        DOUBLE_COLON,       // ::

        // Delimitadores
        LPAREN,
        RPAREN, // ()
        LBRACE,
        RBRACE, // {}
        LBRACKET,
        RBRACKET,  // []
        COMMA,     // ,
        SEMICOLON, // ;
        DOT,       // .

        // Comentarios (si querés reconocerlos)
        COMMENT,

        // Fin de archivo
        END_OF_FILE,
        TOKEN_EOF,

        // Error o desconocido
        UNKNOWN
    };

    // GLOBAL VARIABLES
    static std::string IdentifierStr; // Filled in if tok_identifier
    static double NumVal;        // Filled in if tok_number

}

#endif
