#ifndef LEXER_HPP
#define LEXER_HPP

#include "parser.tab.hpp"
#include <FlexLexer.h>

class HulkLexer : public yyFlexLexer {
public:
    using location_type = yy::parser::location_type;
    
    HulkLexer(std::istream& in) : yyFlexLexer(in) {}
    virtual ~HulkLexer() = default;
    
    yy::parser::symbol_type yylex();
    
    location_type loc;
};

#endif