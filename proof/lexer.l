
%{
#include "parser.tab.h" // Para que Flex conozca los tokens
#include <stdlib.h> // para atoi
%}

%%
"print"    { return PRINT; }
"if"       { return IF; }
"else"     { return ELSE; }
"let"      { return LET; }
"in"       { return IN; }
";"        { return ';'; }
"("        { return '('; }
")"        { return ')'; }
">="       { return GE; }
"<="        { return LE; }
"=="        { return EQ; }
">"         { return GT; }
"<"         { return LT; }

[a-zA-Z_][a-zA-Z0-9_]* {yylval.id = strdup(yytext); return IDENTIFIER;}
\"([^"\\]|\\.)*\" {
    yylval.id = strdup(yytext); // Incluye las comillas. Puedes quitarlas si prefieres
    return STRING;
}
[0-9]+     { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]+   ; // Ignora espacios y tabs
.          { return yytext[0]; } // Caracteres individuales como + - * /

%%

int yywrap() {
    return 1;
}
