#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <string>
#include "../lexer/token.h"
#include "ast.h"

using namespace std;

namespace HULK_PARSER {

// Symbol type (terminal or non-terminal)
enum class SymbolType {
    TERMINAL,
    NON_TERMINAL
};

// Symbol in the grammar
struct Symbol {
    SymbolType type;
    int id; // TokenType for terminals, custom ID for non-terminals
    
    bool operator==(const Symbol& other) const {
        return type == other.type && id == other.id;
    }
};

// Hash function for Symbol to use in unordered_map
struct SymbolHash {
    size_t operator()(const Symbol& s) const {
        return hash<int>()(static_cast<int>(s.type)) ^ hash<int>()(s.id);
    }
};

// Production rule
struct Production {
    Symbol lhs; // Left-hand side (non-terminal)
    vector<Symbol> rhs; // Right-hand side (sequence of symbols)
};

// LR(1) Item
struct LR1Item {
    int productionIndex;
    int dotPosition;
    HULK_LEXER::TokenType lookahead;
    
    bool operator==(const LR1Item& other) const {
        return productionIndex == other.productionIndex && 
               dotPosition == other.dotPosition && 
               lookahead == other.lookahead;
    }
};

// Hash function for LR1Item
struct LR1ItemHash {
    size_t operator()(const LR1Item& item) const {
        return hash<int>()(item.productionIndex) ^ 
               hash<int>()(item.dotPosition) ^ 
               hash<int>()(static_cast<int>(item.lookahead));
    }
};

// LR(1) Item Set (state in the automaton)
using ItemSet = unordered_set<LR1Item, LR1ItemHash>;

// Hash function for ItemSet
struct ItemSetHash {
    size_t operator()(const ItemSet& items) const {
        size_t hash = 0;
        for (const auto& item : items) {
            hash ^= LR1ItemHash()(item);
        }
        return hash;
    }
};

// Action types for the parsing table
enum class ActionType {
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
};

// Action entry in the parsing table
struct Action {
    ActionType type;
    int value; // State number for SHIFT, production number for REDUCE
    
    Action(ActionType t = ActionType::ERROR, int v = 0) : type(t), value(v) {}
};

// LR(1) Parser class
class Parser {
private:
    // Grammar
    vector<Production> productions;
    
    // Parsing tables
    vector<unordered_map<HULK_LEXER::TokenType, Action>> actionTable;
    vector<unordered_map<int, int>> gotoTable;
    
    // Input tokens
    vector<HULK_LEXER::Token> tokens;
    int currentToken;
    
    // Parsing stacks
    stack<int> stateStack;
    stack<shared_ptr<ASTNode>> nodeStack;
    
    // Helper methods
    void initializeGrammar();
    void buildParsingTables();
    shared_ptr<ASTNode> reduceProduction(int productionId, 
                                             vector<shared_ptr<ASTNode>> nodes);
    
    // LR(1) table construction helpers
    ItemSet closure(const ItemSet& items);
    ItemSet goTo(const ItemSet& items, const Symbol& symbol);
    vector<ItemSet> constructCanonicalCollection();
    void constructParsingTables(const vector<ItemSet>& canonicalCollection);
    
    // Error handling
    void syntaxError(const string& message);
    
public:
    Parser(const vector<HULK_LEXER::Token>& tokens);
    shared_ptr<Program> parse();
};

} // namespace HULK_PARSER

#endif // PARSER_H