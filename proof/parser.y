
%code requires {
    #include "ast.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex();
void yyerror(const char *s);
ASTNode* root;
%}

%union {
    int num;
    char* id;
    ASTNode* node;
    VarBinding* bindings;
}

%token <num> NUMBER
%token <id> IDENTIFIER
%token <id> STRING
%token LET IN
%token PRINT IF ELSE
%token GT LT EQ GE LE


%type <node> expr statement statement_list statement_2 print_stmt if_stmt let_expr let_body input
%type <bindings> binding
%type <bindings> binding_list 

%left EQ
%left GT LT GE LE
%left '+' '-'
%left '@'
%left '*' '/'


%%

input:
    statement_list { root = $1; }
    ;

statement_list:
    statement                    {$$ = $1; }
    | statement_list statement   {$$ = create_seq_node($1,$2); }
    ;

statement:
    print_stmt ';'               {$$ = $1; }
    | if_stmt  ';'               {$$ = $1; }
    | expr     ';'               {$$ = $1; }
    ;

statement_2:
    print_stmt             {$$ = $1; }
    | if_stmt              {$$ = $1; }
    | expr                 {$$ = $1; }
    ;

print_stmt:
    PRINT '(' expr ')'    {$$ = create_print_node($3);}

if_stmt:
    IF '(' expr ')' statement_2 ELSE statement_2 {$$ = create_if_node($3,$5,$7);}


expr:
      expr '+' expr   { $$ = create_op_node(AST_ADD, $1, $3); }
    | expr '-' expr   { $$ = create_op_node(AST_SUB, $1, $3); }
    | expr '@' expr   { $$ = create_op_node(AST_CONCAT,$1,$3);}
    | expr '*' expr   { $$ = create_op_node(AST_MUL, $1, $3); }
    | expr '/' expr   { $$ = create_op_node(AST_DIV, $1, $3); }
    | expr GT expr    { $$ = create_op_node(AST_GT,  $1, $3); }
    | expr LT expr    { $$ = create_op_node(AST_LT,  $1, $3); }
    | expr EQ expr    { $$ = create_op_node(AST_EQ,  $1, $3); }
    | expr GE expr    { $$ = create_op_node(AST_GE,  $1, $3); }
    | expr LE expr    { $$ = create_op_node(AST_LE,  $1, $3); }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = create_num_node($1); }
    | IDENTIFIER      { $$ = create_var_node($1); }
    | STRING          { $$ = create_string_node($1); }
    | let_expr        { $$ = $1; }
    ;

let_expr:
    LET binding_list IN let_body {$$ = create_let_node($2,$4);}

binding_list:
    binding                         {$$ = $1;}
    | binding_list ',' binding      {$$ = append_binding_list($1, $3);}


binding:
    IDENTIFIER '=' expr {$$ = create_binding($1,$3); }

let_body:
    statement_2                   {$$ = $1; }
    | '(' statement_2 ')'         {$$ = $2; }
    | '{'statement_list '}'       {$$ = $2; }




%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}
