


%{
#include <cstdio>
#include <cstdlib>

void yyerror(const char *s);
int yylex();

%}

%union {
    int ival;
}

%token <ival> NUMBER
%token PRINT
%token PLUS MINUS TIMES DIVIDE LPAREN RPAREN

%type <ival> expr

%left PLUS MINUS        // + y - tienen la misma precedencia, asociativos a la izquierda
%left TIMES DIVIDE      // * y / tienen mayor precedencia, asociativos a la izquierda


%%

program:
    /* empty */
    | program statement
    ;

statement:
    PRINT LPAREN expr RPAREN { printf("%d\n", $3); }
    ;

expr:
    expr PLUS expr   { $$ = $1 + $3; }
  | expr MINUS expr  { $$ = $1 - $3; }
  | expr TIMES expr  { $$ = $1 * $3; }
  | expr DIVIDE expr { $$ = $1 / $3; }
  | NUMBER           { $$ = $1; }
  | LPAREN expr RPAREN { $$ = $2; }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}


int main()
{
    yyparse();
    return 0;
}