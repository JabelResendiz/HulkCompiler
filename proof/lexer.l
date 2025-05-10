
%{
#include "parser.tab.h" // Para que Flex conozca los tokens
#include <stdlib.h> // para atoi
%}

%%
"print"    { return PRINT; }
"if"       { return IF; }
"else"     { return ELSE; }
";"        { return ';'; }
"("        { return '('; }
")"        { return ')'; }
[0-9]+     { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]+   ; // Ignora espacios y tabs
.          { return yytext[0]; } // Caracteres individuales como + - * /
%%

int yywrap() {
    return 1;
}
