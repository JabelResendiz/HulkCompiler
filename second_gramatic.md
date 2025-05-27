

program:
    statement_list { root = $1; }
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    PRINT expr ';' { $$ = create_print_node($2); }
    | IF '(' expr ')' statement ELSE statement { $$ = create_if_node($3, $5, $7); }
    | let_expr ';' { $$ = $1; }  // let-in como statement
    | expr ';' { $$ = $1; }
    ;

expr:
    let_expr
    | simple_expr
    ;

let_expr:
    LET binding_list IN expr_body { $$ = create_let_node($2, $4); }
    ;

expr_body:
    block_expr
    | simple_expr
    ;

block_expr:
    '{' statement_list tail_expr '}' { $$ = create_block_node($2, $3); }
    ;

tail_expr:
    /* empty */ { $$ = create_void_node(); }  // Valor por defecto
    | expr { $$ = $1; }  // Valor explícito al final
    ;

simple_expr:
    simple_expr '+' simple_expr { $$ = create_binop_node(AST_ADD, $1, $3); }
    | simple_expr '*' simple_expr { $$ = create_binop_node(AST_MUL, $1, $3); }
    | NUMBER { $$ = create_num_node($1); }
    | IDENT { $$ = create_var_node($1); }
    | '(' expr ')' { $$ = $2; }
    ;

binding_list:
    binding
    | binding_list ',' binding
    ;

binding:
    IDENT '=' expr { $$ = create_binding($1, $3); }
    ;





    