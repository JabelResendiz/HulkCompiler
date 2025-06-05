// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 26 "parser.ypp"

#include <cstdio>
#include "ast/ast.hpp"
#include "lexer.hpp"
    
extern int yyparse();
void yyerror(const char *s);
extern std::unique_ptr<ASTNode> root;

#line 51 "parser.cpp"


#include "parser.hpp"


// Unqualified %code blocks.
#line 16 "parser.ypp"

    #include "ast/ast.h"
    #include <iostream>
    std::unique_ptr<ASTNode> root;
    void yy::Parser::error(const location_type& l, const std::string& m) {
        std::cerr << "Error en " << l << ": " << m << std::endl;
    }

#line 67 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.ypp"
namespace yy {
#line 141 "parser.cpp"

  /// Build a parser object.
  Parser::Parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_input: // input
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_statement_2: // statement_2
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_if_stmt: // if_stmt
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_let_expr: // let_expr
      case symbol_kind::S_let_body: // let_body
        value.copy< std::unique_ptr<ASTNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binding_list: // binding_list
      case symbol_kind::S_binding: // binding
        value.copy< std::unique_ptr<VarBinding> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_input: // input
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_statement_2: // statement_2
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_if_stmt: // if_stmt
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_let_expr: // let_expr
      case symbol_kind::S_let_body: // let_body
        value.move< std::unique_ptr<ASTNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_binding_list: // binding_list
      case symbol_kind::S_binding: // binding
        value.move< std::unique_ptr<VarBinding> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_input: // input
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_statement_2: // statement_2
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_if_stmt: // if_stmt
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_let_expr: // let_expr
      case symbol_kind::S_let_body: // let_body
        value.YY_MOVE_OR_COPY< std::unique_ptr<ASTNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binding_list: // binding_list
      case symbol_kind::S_binding: // binding
        value.YY_MOVE_OR_COPY< std::unique_ptr<VarBinding> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_input: // input
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_statement_2: // statement_2
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_if_stmt: // if_stmt
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_let_expr: // let_expr
      case symbol_kind::S_let_body: // let_body
        value.move< std::unique_ptr<ASTNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binding_list: // binding_list
      case symbol_kind::S_binding: // binding
        value.move< std::unique_ptr<VarBinding> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_input: // input
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_statement_2: // statement_2
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_if_stmt: // if_stmt
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_let_expr: // let_expr
      case symbol_kind::S_let_body: // let_body
        value.copy< std::unique_ptr<ASTNode> > (that.value);
        break;

      case symbol_kind::S_binding_list: // binding_list
      case symbol_kind::S_binding: // binding
        value.copy< std::unique_ptr<VarBinding> > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_input: // input
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_statement_2: // statement_2
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_if_stmt: // if_stmt
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_let_expr: // let_expr
      case symbol_kind::S_let_body: // let_body
        value.move< std::unique_ptr<ASTNode> > (that.value);
        break;

      case symbol_kind::S_binding_list: // binding_list
      case symbol_kind::S_binding: // binding
        value.move< std::unique_ptr<VarBinding> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_NUMBER: // NUMBER
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_input: // input
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_statement_2: // statement_2
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_if_stmt: // if_stmt
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_let_expr: // let_expr
      case symbol_kind::S_let_body: // let_body
        yylhs.value.emplace< std::unique_ptr<ASTNode> > ();
        break;

      case symbol_kind::S_binding_list: // binding_list
      case symbol_kind::S_binding: // binding
        yylhs.value.emplace< std::unique_ptr<VarBinding> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // input: statement_list
#line 69 "parser.ypp"
                   { root = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 797 "parser.cpp"
    break;

  case 3: // statement_list: statement
#line 73 "parser.ypp"
                                 { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 803 "parser.cpp"
    break;

  case 4: // statement_list: statement_list statement
#line 74 "parser.ypp"
                                 { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_seq_node(std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 809 "parser.cpp"
    break;

  case 5: // statement: print_stmt SEMICOLON
#line 78 "parser.ypp"
                                       { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 815 "parser.cpp"
    break;

  case 6: // statement: if_stmt SEMICOLON
#line 79 "parser.ypp"
                                       { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 821 "parser.cpp"
    break;

  case 7: // statement: expr SEMICOLON
#line 80 "parser.ypp"
                                       { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 827 "parser.cpp"
    break;

  case 8: // statement_2: print_stmt
#line 84 "parser.ypp"
                           { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 833 "parser.cpp"
    break;

  case 9: // statement_2: if_stmt
#line 85 "parser.ypp"
                           { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 839 "parser.cpp"
    break;

  case 10: // statement_2: expr
#line 86 "parser.ypp"
                           { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 845 "parser.cpp"
    break;

  case 11: // print_stmt: PRINT LPAREN expr RPAREN
#line 90 "parser.ypp"
                                { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_print_node(std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ())); }
#line 851 "parser.cpp"
    break;

  case 12: // if_stmt: IF LPAREN expr RPAREN statement_2 ELSE statement_2
#line 95 "parser.ypp"
    { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_if_node(std::move(yystack_[4].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 857 "parser.cpp"
    break;

  case 13: // expr: expr '+' expr
#line 99 "parser.ypp"
                    { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::ADD, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 863 "parser.cpp"
    break;

  case 14: // expr: expr '-' expr
#line 100 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::SUB, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 869 "parser.cpp"
    break;

  case 15: // expr: expr '@' expr
#line 101 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::CONCAT, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 875 "parser.cpp"
    break;

  case 16: // expr: expr '*' expr
#line 102 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::MUL, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 881 "parser.cpp"
    break;

  case 17: // expr: expr '/' expr
#line 103 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::DIV, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 887 "parser.cpp"
    break;

  case 18: // expr: expr GT expr
#line 104 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::GT, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 893 "parser.cpp"
    break;

  case 19: // expr: expr LT expr
#line 105 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::LT, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 899 "parser.cpp"
    break;

  case 20: // expr: expr EQ expr
#line 106 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::EQ, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 905 "parser.cpp"
    break;

  case 21: // expr: expr GE expr
#line 107 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::GE, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 911 "parser.cpp"
    break;

  case 22: // expr: expr LE expr
#line 108 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::LE, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 917 "parser.cpp"
    break;

  case 23: // expr: LPAREN expr RPAREN
#line 109 "parser.ypp"
                            { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 923 "parser.cpp"
    break;

  case 24: // expr: NUMBER
#line 110 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_num_node(yystack_[0].value.as < int > ()); }
#line 929 "parser.cpp"
    break;

  case 25: // expr: IDENTIFIER
#line 111 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_var_node(yystack_[0].value.as < std::string > ()); }
#line 935 "parser.cpp"
    break;

  case 26: // expr: STRING
#line 112 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_string_node(yystack_[0].value.as < std::string > ()); }
#line 941 "parser.cpp"
    break;

  case 27: // expr: let_expr
#line 113 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 947 "parser.cpp"
    break;

  case 28: // let_expr: LET binding_list IN let_body
#line 118 "parser.ypp"
    { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_let_node(std::move(yystack_[2].value.as < std::unique_ptr<VarBinding> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 953 "parser.cpp"
    break;

  case 29: // binding_list: binding
#line 122 "parser.ypp"
                                    { yylhs.value.as < std::unique_ptr<VarBinding> > () = std::move(yystack_[0].value.as < std::unique_ptr<VarBinding> > ()); }
#line 959 "parser.cpp"
    break;

  case 30: // binding_list: binding_list COMMA binding
#line 123 "parser.ypp"
                                    { yylhs.value.as < std::unique_ptr<VarBinding> > () = append_binding_list(std::move(yystack_[2].value.as < std::unique_ptr<VarBinding> > ()), std::move(yystack_[0].value.as < std::unique_ptr<VarBinding> > ())); }
#line 965 "parser.cpp"
    break;

  case 31: // binding: IDENTIFIER '=' expr
#line 128 "parser.ypp"
    { yylhs.value.as < std::unique_ptr<VarBinding> > () = create_binding(yystack_[2].value.as < std::string > (), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 971 "parser.cpp"
    break;

  case 32: // let_body: statement_2
#line 132 "parser.ypp"
                                  { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 977 "parser.cpp"
    break;

  case 33: // let_body: LPAREN statement_2 RPAREN
#line 133 "parser.ypp"
                                  { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 983 "parser.cpp"
    break;

  case 34: // let_body: LBRACE statement_list RBRACE
#line 134 "parser.ypp"
                                   { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 989 "parser.cpp"
    break;


#line 993 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -31;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
       0,   -31,   -31,   -31,     6,    21,    24,    31,    56,     0,
     -31,    53,    57,    71,   -31,    46,    -5,   -31,    31,    31,
      87,   -31,   -31,   -31,   -31,    31,    31,    31,    31,    31,
     -31,    31,    31,    31,    31,    31,    31,    62,     6,   103,
     119,   -31,    28,    28,   140,    28,    28,    19,    19,   -31,
     -31,   -11,   135,     0,     0,   -31,   -31,   -31,   135,   -31,
     -31,   -31,     0,    58,    87,    55,    67,   -31,   -31,     0,
     -31
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,    24,    25,    26,     0,     0,     0,     0,     0,     2,
       3,     0,     0,     0,    27,     0,     0,    29,     0,     0,
       0,     1,     4,     5,     6,     0,     0,     0,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    18,    19,    20,    21,    22,    13,    14,    16,
      17,    15,    31,     0,     0,    32,     8,     9,    10,    28,
      30,    11,     0,     0,     0,     0,     0,    33,    34,     0,
      12
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -31,   -31,    26,    -8,   -20,   -30,   -22,    -7,   -31,   -31,
      40,   -31
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    55,    11,    12,    13,    14,    16,
      17,    59
  };

  const signed char
  Parser::yytable_[] =
  {
      20,    22,    37,     1,     2,     3,     4,    56,     5,     6,
      15,    39,    40,    33,    34,    57,    38,     7,    42,    43,
      44,    45,    46,    56,    47,    48,    49,    50,    51,    52,
      58,    57,    56,    63,     1,     2,     3,     4,    18,    56,
      57,    19,    66,    33,    34,    35,    64,    57,     7,    70,
      31,    32,    33,    34,    35,    58,    21,    22,     1,     2,
       3,     4,    58,     5,     6,     1,     2,     3,     4,    23,
       5,     6,     7,    24,    36,    68,    67,    69,    60,    53,
      65,    54,    25,    26,    27,    28,    29,    30,     0,     0,
       0,     0,     0,    31,    32,    33,    34,    35,    25,    26,
      27,    28,    29,     0,     0,    41,     0,     0,     0,    31,
      32,    33,    34,    35,    25,    26,    27,    28,    29,     0,
       0,    61,     0,     0,     0,    31,    32,    33,    34,    35,
      25,    26,    27,    28,    29,     0,     0,    62,     0,     0,
       0,    31,    32,    33,    34,    35,    25,    26,    27,    28,
      29,    25,    26,     0,    28,    29,     0,    31,    32,    33,
      34,    35,    31,    32,    33,    34,    35
  };

  const signed char
  Parser::yycheck_[] =
  {
       7,     9,     7,     3,     4,     5,     6,    37,     8,     9,
       4,    18,    19,    24,    25,    37,    21,    17,    25,    26,
      27,    28,    29,    53,    31,    32,    33,    34,    35,    36,
      37,    53,    62,    53,     3,     4,     5,     6,    17,    69,
      62,    17,    62,    24,    25,    26,    53,    69,    17,    69,
      22,    23,    24,    25,    26,    62,     0,    65,     3,     4,
       5,     6,    69,     8,     9,     3,     4,     5,     6,    16,
       8,     9,    17,    16,    28,    20,    18,    10,    38,    17,
      54,    19,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    11,    12,
      13,    14,    15,    -1,    -1,    18,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    11,    12,    13,    14,    15,    -1,
      -1,    18,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      11,    12,    13,    14,    15,    -1,    -1,    18,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    11,    12,    13,    14,
      15,    11,    12,    -1,    14,    15,    -1,    22,    23,    24,
      25,    26,    22,    23,    24,    25,    26
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     8,     9,    17,    30,    31,
      32,    34,    35,    36,    37,     4,    38,    39,    17,    17,
      36,     0,    32,    16,    16,    11,    12,    13,    14,    15,
      16,    22,    23,    24,    25,    26,    28,     7,    21,    36,
      36,    18,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    17,    19,    33,    34,    35,    36,    40,
      39,    18,    18,    33,    36,    31,    33,    18,    20,    10,
      33
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    29,    30,    31,    31,    32,    32,    32,    33,    33,
      33,    34,    35,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    37,    38,
      38,    39,    40,    40,    40
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     2,     2,     1,     1,
       1,     4,     7,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     4,     1,
       3,     3,     1,     3,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "IDENTIFIER",
  "STRING", "LET", "IN", "PRINT", "IF", "ELSE", "GT", "LT", "EQ", "GE",
  "LE", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA",
  "'+'", "'-'", "'*'", "'/'", "'@'", "ERROR", "'='", "$accept", "input",
  "statement_list", "statement", "statement_2", "print_stmt", "if_stmt",
  "expr", "let_expr", "binding_list", "binding", "let_body", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    69,    69,    73,    74,    78,    79,    80,    84,    85,
      86,    90,    94,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   117,   122,
     123,   127,   132,   133,   134
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    24,    22,     2,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,     2,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    27
    };
    // Last valid token kind.
    const int code_max = 277;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "parser.ypp"
} // yy
#line 1565 "parser.cpp"

#line 137 "parser.ypp"


void yy::parser::error(const std::string& msg) {
    std::cerr << "Syntax error: " << msg << std::endl;
}
