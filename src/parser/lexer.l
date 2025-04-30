%{
#include "parser.tab.h"
#include <cstdlib>
%}

%option noyywrap

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

"print"           { return PRINT; }
{DIGIT}+          { yylval.ival = atoi(yytext); return NUMBER; }
"("               { return LPAREN; }
")"               { return RPAREN; }
"+"               { return PLUS; }
"-"               { return MINUS; }
"*"               { return TIMES; }
"/"               { return DIVIDE; }
[ \t\n]+          { /* skip whitespace */ }
.                 { return yytext[0]; }

%%
