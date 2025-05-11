%{
#include "parser.tab.h"
#include "parser/tokenType.h"
#include <cstdlib>
#include <cstdio>


using namespace HULK_LEXER;


int lineno =1;
int colno =1;
int token_start_col ;

extern YYSTYPE yylval;  


#define PRINT_TOKEN(tokname) \
    printf("Token: %-10s | Line: %d | Column: %d | Text: '%s'\n", tokname, lineno, token_start_col, yytext);


#define RETURN_TOKEN(tokname, tokenum)                      \
    do {                                                    \
        token_start_col = colno;                            \
        PRINT_TOKEN(tokname);                               \
        colno += yyleng;                                    \
        return HULK_LEXER::tokenum;                                     \
    } while (0)


#define RETURN_NUM_TOKEN(tokname, tokenum, val)             \
    do {                                                    \
        token_start_col = colno;                            \
        yylval.ival = val;                                  \
        PRINT_TOKEN(tokname);                               \
        colno += yyleng;                                    \
        return HULK_LEXER::tokenum;                                     \
    } while (0)



%}

%option noyywrap

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

"print"  { RETURN_TOKEN("PRINT", PRINT); }
"if"     { RETURN_TOKEN("IF", IF); }
"else"   { RETURN_TOKEN("ELSE", ELSE); }
"("      { RETURN_TOKEN("LPAREN", LPAREN); }
")"      { RETURN_TOKEN("RPAREN", RPAREN); }
"+"      { RETURN_TOKEN("PLUS", PLUS); }
{DIGIT}+          { RETURN_NUM_TOKEN("NUMBER", NUMBER, atoi(yytext));}

[ \t\n]+          { /* skip whitespace */ }
.                 { return yytext[0]; }

%%


int main()
{
    int token;
    while ((token = yylex())) {}
    return 0;
}