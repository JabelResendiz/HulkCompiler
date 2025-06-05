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

// "%code top" blocks.
#line 21 "parser.ypp"

    #include <memory>

#line 43 "parser.tab.cpp"


// First part of user prologue.
#line 25 "parser.ypp"

#include <cstdio>
#include "ast/ast.hpp"
#include "lexer.hpp"
    
extern int yyparse();
void yyerror(const char *s);
extern std::unique_ptr<ASTNode> root;

#line 57 "parser.tab.cpp"


#include "parser.tab.hpp"




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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


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

namespace yy {
#line 154 "parser.tab.cpp"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
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
        value.YY_MOVE_OR_COPY< std::vector<VarBinding> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
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
        value.move< std::vector<VarBinding> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
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
        value.copy< std::vector<VarBinding> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
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
        value.move< std::vector<VarBinding> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

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
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
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
        yylhs.value.emplace< std::vector<VarBinding> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
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
#line 54 "parser.ypp"
                   { root = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 677 "parser.tab.cpp"
    break;

  case 3: // statement_list: statement
#line 58 "parser.ypp"
                                 { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 683 "parser.tab.cpp"
    break;

  case 4: // statement_list: statement_list statement
#line 59 "parser.ypp"
                                 { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_seq_node(std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 689 "parser.tab.cpp"
    break;

  case 5: // statement: print_stmt SEMICOLON
#line 63 "parser.ypp"
                                       { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 695 "parser.tab.cpp"
    break;

  case 6: // statement: if_stmt SEMICOLON
#line 64 "parser.ypp"
                                       { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 701 "parser.tab.cpp"
    break;

  case 7: // statement: expr SEMICOLON
#line 65 "parser.ypp"
                                       { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 707 "parser.tab.cpp"
    break;

  case 8: // statement_2: print_stmt
#line 69 "parser.ypp"
                           { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 713 "parser.tab.cpp"
    break;

  case 9: // statement_2: if_stmt
#line 70 "parser.ypp"
                           { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 719 "parser.tab.cpp"
    break;

  case 10: // statement_2: expr
#line 71 "parser.ypp"
                           { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 725 "parser.tab.cpp"
    break;

  case 11: // print_stmt: PRINT LPAREN expr RPAREN
#line 75 "parser.ypp"
                                { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_print_node(std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ())); }
#line 731 "parser.tab.cpp"
    break;

  case 12: // if_stmt: IF LPAREN expr RPAREN statement_2 ELSE statement_2
#line 80 "parser.ypp"
    { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_if_node(std::move(yystack_[4].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 737 "parser.tab.cpp"
    break;

  case 13: // expr: expr '+' expr
#line 84 "parser.ypp"
                    { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::ADD, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 743 "parser.tab.cpp"
    break;

  case 14: // expr: expr '-' expr
#line 85 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::SUB, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 749 "parser.tab.cpp"
    break;

  case 15: // expr: expr '@' expr
#line 86 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::CONCAT, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 755 "parser.tab.cpp"
    break;

  case 16: // expr: expr '*' expr
#line 87 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::MUL, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 761 "parser.tab.cpp"
    break;

  case 17: // expr: expr '/' expr
#line 88 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::DIV, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 767 "parser.tab.cpp"
    break;

  case 18: // expr: expr GT expr
#line 89 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::GT, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 773 "parser.tab.cpp"
    break;

  case 19: // expr: expr LT expr
#line 90 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::LT, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 779 "parser.tab.cpp"
    break;

  case 20: // expr: expr EQ expr
#line 91 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::EQ, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 785 "parser.tab.cpp"
    break;

  case 21: // expr: expr GE expr
#line 92 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::GE, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 791 "parser.tab.cpp"
    break;

  case 22: // expr: expr LE expr
#line 93 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_op_node(ASTNodeType::LE, std::move(yystack_[2].value.as < std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 797 "parser.tab.cpp"
    break;

  case 23: // expr: LPAREN expr RPAREN
#line 94 "parser.ypp"
                            { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 803 "parser.tab.cpp"
    break;

  case 24: // expr: NUMBER
#line 95 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_num_node(yystack_[0].value.as < int > ()); }
#line 809 "parser.tab.cpp"
    break;

  case 25: // expr: IDENTIFIER
#line 96 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_var_node(yystack_[0].value.as < std::string > ()); }
#line 815 "parser.tab.cpp"
    break;

  case 26: // expr: STRING
#line 97 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_string_node(yystack_[0].value.as < std::string > ()); }
#line 821 "parser.tab.cpp"
    break;

  case 27: // expr: let_expr
#line 98 "parser.ypp"
                      { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 827 "parser.tab.cpp"
    break;

  case 28: // let_expr: LET binding_list IN let_body
#line 103 "parser.ypp"
    { yylhs.value.as < std::unique_ptr<ASTNode> > () = create_let_node(std::move(yystack_[2].value.as < std::vector<VarBinding> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 833 "parser.tab.cpp"
    break;

  case 29: // binding_list: binding
#line 107 "parser.ypp"
                                    { yylhs.value.as < std::vector<VarBinding> > () = std::move(yystack_[0].value.as < std::vector<VarBinding> > ()); }
#line 839 "parser.tab.cpp"
    break;

  case 30: // binding_list: binding_list COMMA binding
#line 108 "parser.ypp"
                                    { yylhs.value.as < std::vector<VarBinding> > () = append_binding_list(std::move(yystack_[2].value.as < std::vector<VarBinding> > ()), std::move(yystack_[0].value.as < std::vector<VarBinding> > ())); }
#line 845 "parser.tab.cpp"
    break;

  case 31: // binding: IDENTIFIER '=' expr
#line 113 "parser.ypp"
    { yylhs.value.as < std::vector<VarBinding> > () = create_binding(yystack_[2].value.as < std::string > (), std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ())); }
#line 851 "parser.tab.cpp"
    break;

  case 32: // let_body: statement_2
#line 117 "parser.ypp"
                                  { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<ASTNode> > ()); }
#line 857 "parser.tab.cpp"
    break;

  case 33: // let_body: LPAREN statement_2 RPAREN
#line 118 "parser.ypp"
                                  { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 863 "parser.tab.cpp"
    break;

  case 34: // let_body: LBRACE statement_list RBRACE
#line 119 "parser.ypp"
                                   { yylhs.value.as < std::unique_ptr<ASTNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<ASTNode> > ()); }
#line 869 "parser.tab.cpp"
    break;


#line 873 "parser.tab.cpp"

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
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
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

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
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
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  parser::yysyntax_error_ (const context& yyctx) const
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


  const signed char parser::yypact_ninf_ = -36;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      78,     2,     3,    -9,    30,   -36,   -36,   -36,    47,    78,
     -36,    40,    46,    44,   -36,    30,    30,    29,     6,   -36,
      88,   -36,   -36,   -36,   -36,   -36,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,   101,   114,    30,    34,
      -9,   -36,   -22,   -22,   140,   -22,   -22,    13,    13,   -29,
     -36,   -36,   -36,    78,   127,    78,    78,   -36,   -36,   -36,
     127,   -36,   -36,    64,    56,    88,    74,    78,   -36,   -36,
     -36
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,    24,    25,    26,     0,     2,
       3,     0,     0,     0,    27,     0,     0,     0,     0,    29,
       0,     1,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    21,    22,    20,    18,    19,    13,    14,    15,
      16,    17,    11,     0,    31,     0,     0,    32,     8,     9,
      10,    28,    30,     0,     0,     0,     0,     0,    33,    34,
      12
  };

  const signed char
  parser::yypgoto_[] =
  {
     -36,   -36,    15,    -8,   -14,   -35,   -34,    -4,   -36,   -36,
      39,   -36
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    57,    11,    12,    13,    14,    18,
      19,    61
  };

  const signed char
  parser::yytable_[] =
  {
      20,    22,    34,    35,    58,    59,    31,    32,    33,    34,
      35,    36,    37,    39,    15,    16,    40,    17,    58,    59,
      58,    59,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    58,    59,    54,    60,     3,     1,     2,    63,
       3,    64,     4,    33,    34,    35,    55,    21,    23,    60,
      56,    65,    25,    70,    24,     5,     6,     7,    22,     5,
       6,     7,    38,    60,    26,    27,    28,    29,    30,    67,
      68,    66,    31,    32,    33,    34,    35,     1,     2,    62,
       3,     1,     2,     0,     3,     0,     4,     0,     0,     0,
       4,     0,    69,     0,     0,     0,     0,     0,     0,     5,
       6,     7,    41,     5,     6,     7,     0,     0,    26,    27,
      28,    29,    30,     0,     0,    52,    31,    32,    33,    34,
      35,    26,    27,    28,    29,    30,     0,     0,    53,    31,
      32,    33,    34,    35,    26,    27,    28,    29,    30,     0,
       0,     0,    31,    32,    33,    34,    35,    26,    27,    28,
      29,    30,     0,     0,     0,    31,    32,    33,    34,    35,
      26,    27,     0,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35
  };

  const signed char
  parser::yycheck_[] =
  {
       4,     9,    31,    32,    39,    39,    28,    29,    30,    31,
      32,    15,    16,     7,    12,    12,    10,    26,    53,    53,
      55,    55,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    67,    67,    38,    39,     6,     3,     4,    53,
       6,    55,    12,    30,    31,    32,    12,     0,     8,    53,
      16,    55,     8,    67,     8,    25,    26,    27,    66,    25,
      26,    27,    33,    67,    20,    21,    22,    23,    24,     5,
      14,    56,    28,    29,    30,    31,    32,     3,     4,    40,
       6,     3,     4,    -1,     6,    -1,    12,    -1,    -1,    -1,
      12,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    25,
      26,    27,    14,    25,    26,    27,    -1,    -1,    20,    21,
      22,    23,    24,    -1,    -1,    14,    28,    29,    30,    31,
      32,    20,    21,    22,    23,    24,    -1,    -1,    14,    28,
      29,    30,    31,    32,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      20,    21,    -1,    23,    24,    -1,    -1,    -1,    28,    29,
      30,    31,    32
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     6,    12,    25,    26,    27,    35,    36,
      37,    39,    40,    41,    42,    12,    12,    26,    43,    44,
      41,     0,    37,     8,     8,     8,    20,    21,    22,    23,
      24,    28,    29,    30,    31,    32,    41,    41,    33,     7,
      10,    14,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    14,    14,    41,    12,    16,    38,    39,    40,
      41,    45,    44,    38,    38,    41,    36,     5,    14,    18,
      38
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    34,    35,    36,    36,    37,    37,    37,    38,    38,
      38,    39,    40,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    42,    43,
      43,    44,    45,    45,    45
  };

  const signed char
  parser::yyr2_[] =
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
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PRINT", "IF", "ELSE",
  "LET", "IN", "SEMICOLON", "';'", "COMMA", "','", "LPAREN", "'('",
  "RPAREN", "')'", "LBRACE", "'{'", "RBRACE", "'}'", "GE", "LE", "EQ",
  "GT", "LT", "NUMBER", "IDENTIFIER", "STRING", "'+'", "'-'", "'@'", "'*'",
  "'/'", "'='", "$accept", "input", "statement_list", "statement",
  "statement_2", "print_stmt", "if_stmt", "expr", "let_expr",
  "binding_list", "binding", "let_body", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const signed char
  parser::yyrline_[] =
  {
       0,    54,    54,    58,    59,    63,    64,    65,    69,    70,
      71,    75,    79,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   102,   107,
     108,   112,   117,   118,   119
  };

  void
  parser::yy_stack_print_ () const
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
  parser::yy_reduce_print_ (int yyrule) const
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


} // yy
#line 1403 "parser.tab.cpp"

#line 122 "parser.ypp"


void yy::parser::error(const std::string& msg) {
    std::cerr << "Syntax error: " << msg << std::endl;
}
