
%{
#include "parser.tab.h" // Para que Flex conozca los tokens
#include <stdlib.h> // para atoi
%}

%%
"let"      { return LET;}
"in"       { return IN;}
"print"    { return PRINT; }
"if"       { return IF; }
"else"     { return ELSE; }
";"        { return ';'; }
"("        { return '('; }
")"        { return ')'; }
">="       { return GE; }
"<="        { return LE; }
"=="        { return EQ; }
">"         { return GT; }
"<"         { return LT; }

\"[^\"]*\"  {
    char* raw = strdup(yytext + 1);
    raw[strlen(raw) - 1] = '\0';
    yylval.node = create_str_node(raw);
    free(raw);
    return STRING;
}
"@"        { return CONCAT; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.node = create_var_node(yytext); return IDENT; }

[0-9]+     { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]+   ; // Ignora espacios y tabs
.          { return yytext[0]; } // Caracteres individuales como + - * /
%%

int yywrap() {
    return 1;
}
