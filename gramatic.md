program         → statement_list

statement_list  → statement
                | statement_list statement

statement       → print_stmt
                | if_stmt
                | expr ';'

print_stmt      → 'print' '(' expr ')' ';'

if_stmt         → 'if' '(' expr ')' statement 'else' statement

expr            → expr '+' expr
                | expr '-' expr
                | expr '*' expr
                | expr '/' expr
                | '(' expr ')'
                | NUMBER
                | letExpr

letExpr         → 'let' binding_list 'in' let_body 

binding_list    → binding
                | binding_list ',' binding 

binding         → IDENTIFIER '=' expression

let_body        → expr
                | '{' statement_list '}'




