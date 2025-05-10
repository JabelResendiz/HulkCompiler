%{
#include "parser.tab.h"
#include "tokenType.h"
#include <cstdlib>

using namespace HULK_LEXER;

%}

%option noyywrap

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

"print"           { return HULK_LEXER::PRINT; }
"if"              { return HULK_LEXER::IF;}
"else"            { return HULK_LEXER::ELSE;}
"while"           { return HULK_LEXER::WHILE;}
"for"             { return HULK_LEXER::FOR;}
"let"             { return HULK_LEXER::LET;}
{DIGIT}+          { yylval.ival = atoi(yytext); return HULK_LEXER::NUMBER; }
"("               { return HULK_LEXER::LPAREN; }
")"               { return HULK_LEXER::RPAREN; }
"+"               { return HULK_LEXER::PLUS; }
"-"               { return HULK_LEXER::MINUS; }

[ \t\n]+          { /* skip whitespace */ }
.                 { return yytext[0]; }

%%
