%{
#include "parser.tab.h" // Para que Flex conozca los tokens
#include <stdlib.h> // para atoi
%}

%%
[0-9]+     { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]+   ; // Ignora espacios y tabs
.          { return yytext[0]; } // Caracteres individuales como + - * /
%%

int yywrap() {
    return 1;
}
