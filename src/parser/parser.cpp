#include "parser.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

namespace HULK_PARSER {

// Non-terminal symbols (used in the grammar)
enum NonTerminal {
    NT_PROGRAM = 1000,
    NT_STATEMENT,
    NT_EXPRESSION,
    NT_LET_STATEMENT,
    NT_IF_STATEMENT,
    NT_WHILE_STATEMENT,
    NT_FOR_STATEMENT,
    NT_FUNCTION_DECLARATION,
    NT_PRINT_STATEMENT,
    NT_PARAMETER_LIST,
    NT_STATEMENT_LIST,
    NT_UNARY_EXPRESSION,
    NT_BINARY_EXPRESSION,
    NT_FUNCTION_CALL,
    NT_ARGUMENT_LIST,
    NT_LITERAL,
    NT_LET_IN_EXPRESSION,
    NT_IF_ELSE_EXPRESSION,
    NT_BUILT_IN_FUNCTION
};

Parser::Parser(const vector<HULK_LEXER::Token>& tokens) 
    : tokens(tokens), currentToken(0) {
    initializeGrammar();
    buildParsingTables();
}

void Parser::initializeGrammar() {
    // Define the grammar productions
    // This is a simplified version - in a real implementation, 
    // you would have all the productions from the grammar.txt file
    
    // Program -> Statement
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_PROGRAM}, 
        {{SymbolType::NON_TERMINAL, NT_STATEMENT}}
    });
    
    // Program -> Program Statement
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_PROGRAM}, 
        {{SymbolType::NON_TERMINAL, NT_PROGRAM}, {SymbolType::NON_TERMINAL, NT_STATEMENT}}
    });
    
    // Statement -> Expression ;
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_STATEMENT}, 
        {{SymbolType::NON_TERMINAL, NT_EXPRESSION}, {SymbolType::TERMINAL, HULK_LEXER::TokenType::SEMICOLON}}
    });
    
    // Statement -> LetStatement
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_STATEMENT}, 
        {{SymbolType::NON_TERMINAL, NT_LET_STATEMENT}}
    });
    
    // Statement -> IfStatement
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_STATEMENT}, 
        {{SymbolType::NON_TERMINAL, NT_IF_STATEMENT}}
    });
    
    // Statement -> WhileStatement
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_STATEMENT}, 
        {{SymbolType::NON_TERMINAL, NT_WHILE_STATEMENT}}
    });
    
    // Statement -> ForStatement
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_STATEMENT}, 
        {{SymbolType::NON_TERMINAL, NT_FOR_STATEMENT}}
    });
    
    // Statement -> FunctionDeclaration
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_STATEMENT}, 
        {{SymbolType::NON_TERMINAL, NT_FUNCTION_DECLARATION}}
    });
    
    // Statement -> PrintStatement
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_STATEMENT}, 
        {{SymbolType::NON_TERMINAL, NT_PRINT_STATEMENT}}
    });
    
    // LetStatement -> LET IDENTIFIER = Expression IN Expression ;
    productions.push_back({
        {SymbolType::NON_TERMINAL, NT_LET_STATEMENT}, 
        {
            {SymbolType::TERMINAL, HULK_LEXER::TokenType::LET}, 
            {SymbolType::TERMINAL, HULK_LEXER::TokenType::IDENTIFIER}, 
            {SymbolType::TERMINAL, HULK_LEXER::TokenType::ASSIGN}, 
            {SymbolType::NON_TERMINAL, NT_EXPRESSION}, 
            {SymbolType::TERMINAL, HULK_LEXER::TokenType::IN}, 
            {SymbolType::NON_TERMINAL, NT_EXPRESSION}, 
            {SymbolType::TERMINAL, HULK_LEXER::TokenType::SEMICOLON}
        }
    });
    
    // ... Add more productions for the complete grammar
    
    // For brevity, I'm not including all productions here
    // In a real implementation, you would define all productions from the grammar
}

ItemSet Parser::closure(const ItemSet& items) {
    ItemSet result = items;
    bool changed = true;
    
    while (changed) {
        changed = false;
        ItemSet newItems;
        
        for (const auto& item : result) {
            // If dot is before a non-terminal
            if (item.dotPosition < productions[item.productionIndex].rhs.size() &&
                productions[item.productionIndex].rhs[item.dotPosition].type == SymbolType::NON_TERMINAL) {
                
                Symbol nonTerminal = productions[item.productionIndex].rhs[item.dotPosition];
                
                // Find all productions with this non-terminal on the left side
                for (size_t i = 0; i < productions.size(); ++i) {
                    if (productions[i].lhs == nonTerminal) {
                        // Calculate FIRST set for the rest of the input + lookahead
                        // This is simplified - in a real implementation, you would compute FIRST sets
                        HULK_LEXER::TokenType lookahead = item.lookahead;
                        
                        LR1Item newItem{static_cast<int>(i), 0, lookahead};
                        if (result.find(newItem) == result.end() && 
                            newItems.find(newItem) == newItems.end()) {
                            newItems
                            LR1Item newItem{static_cast<int>(i), 0, lookahead};
                            if (result.find(newItem) == result.end() && 
                                newItems.find(newItem) == newItems.end()) {
                                newItems.insert(newItem);
                                changed = true;
                            }
                        }
                    }
                }
            }
            
            result.insert(newItems.begin(), newItems.end());
        }
        
        return result;
    }
    
    ItemSet Parser::goTo(const ItemSet& items, const Symbol& symbol) {
        ItemSet initialSet;
        
        // Find all items where the dot is before the given symbol
        for (const auto& item : items) {
            if (item.dotPosition < productions[item.productionIndex].rhs.size() &&
                productions[item.productionIndex].rhs[item.dotPosition] == symbol) {
                // Create a new item with the dot advanced
                LR1Item newItem{item.productionIndex, item.dotPosition + 1, item.lookahead};
                initialSet.insert(newItem);
            }
        }
        
        // Return the closure of this set
        return closure(initialSet);
    }
    
    vector<ItemSet> Parser::constructCanonicalCollection() {
        vector<ItemSet> collection;
        unordered_map<ItemSet, int, ItemSetHash> stateMap;
        
        // Start with the initial item set
        ItemSet initialSet = closure({{0, 0, HULK_LEXER::TokenType::TOKEN_EOF}});
        collection.push_back(initialSet);
        stateMap[initialSet] = 0;
        
        // Process all states until no new states are added
        for (size_t i = 0; i < collection.size(); ++i) {
            const ItemSet& state = collection[i];
            
            // Find all symbols that appear after the dot in this state
            unordered_set<Symbol, SymbolHash> symbols;
            for (const auto& item : state) {
                if (item.dotPosition < productions[item.productionIndex].rhs.size()) {
                    symbols.insert(productions[item.productionIndex].rhs[item.dotPosition]);
                }
            }
            
            // For each symbol, compute the goto state
            for (const auto& symbol : symbols) {
                ItemSet nextState = goTo(state, symbol);
                
                if (!nextState.empty()) {
                    // Check if this state already exists
                    if (stateMap.find(nextState) == stateMap.end()) {
                        // Add new state
                        stateMap[nextState] = collection.size();
                        collection.push_back(nextState);
                    }
                }
            }
        }
        
        return collection;
    }
    
    void Parser::constructParsingTables(const vector<ItemSet>& canonicalCollection) {
        // Initialize tables
        actionTable.resize(canonicalCollection.size());
        gotoTable.resize(canonicalCollection.size());
        
        // For each state in the canonical collection
        for (size_t i = 0; i < canonicalCollection.size(); ++i) {
            const ItemSet& state = canonicalCollection[i];
            
            // For each item in the state
            for (const auto& item : state) {
                // If the dot is at the end of the production
                if (item.dotPosition == productions[item.productionIndex].rhs.size()) {
                    // If it's the augmented start production, add an accept action
                    if (item.productionIndex == 0 && item.lookahead == HULK_LEXER::TokenType::TOKEN_EOF) {
                        actionTable[i][HULK_LEXER::TokenType::TOKEN_EOF] = Action(ActionType::ACCEPT, 0);
                    } else {
                        // Otherwise, add a reduce action
                        actionTable[i][item.lookahead] = Action(ActionType::REDUCE, item.productionIndex);
                    }
                } else {
                    // If the dot is before a terminal
                    Symbol nextSymbol = productions[item.productionIndex].rhs[item.dotPosition];
                    if (nextSymbol.type == SymbolType::TERMINAL) {
                        // Compute the goto state
                        ItemSet nextState = goTo(state, nextSymbol);
                        
                        // Find the state number
                        for (size_t j = 0; j < canonicalCollection.size(); ++j) {
                            if (canonicalCollection[j] == nextState) {
                                // Add a shift action
                                actionTable[i][static_cast<HULK_LEXER::TokenType>(nextSymbol.id)] = 
                                    Action(ActionType::SHIFT, j);
                                break;
                            }
                        }
                    }
                }
            }
            
            // For each non-terminal
            for (int nt = NT_PROGRAM; nt <= NT_BUILT_IN_FUNCTION; ++nt) {
                Symbol nonTerminal{SymbolType::NON_TERMINAL, nt};
                
                // Compute the goto state
                ItemSet nextState = goTo(state, nonTerminal);
                
                if (!nextState.empty()) {
                    // Find the state number
                    for (size_t j = 0; j < canonicalCollection.size(); ++j) {
                        if (canonicalCollection[j] == nextState) {
                            // Add a goto entry
                            gotoTable[i][nt] = j;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    void Parser::buildParsingTables() {
        // Construct the canonical collection of LR(1) items
        vector<ItemSet> canonicalCollection = constructCanonicalCollection();
        
        // Build the parsing tables
        constructParsingTables(canonicalCollection);
    }
    
    shared_ptr<ASTNode> Parser::reduceProduction(int productionId, 
                                                    vector<shared_ptr<ASTNode>> nodes) {
        // This method creates the appropriate AST node based on the production being reduced
        const Production& prod = productions[productionId];
        
        switch (prod.lhs.id) {
            case NT_PROGRAM: {
                if (prod.rhs.size() == 1) { // Program -> Statement
                    auto program = make_shared<Program>();
                    program->addStatement(dynamic_pointer_cast<Statement>(nodes[0]));
                    return program;
                } else { // Program -> Program Statement
                    auto program = dynamic_pointer_cast<Program>(nodes[0]);
                    program->addStatement(dynamic_pointer_cast<Statement>(nodes[1]));
                    return program;
                }
            }
            
            case NT_STATEMENT: {
                if (prod.rhs.size() == 2) { // Statement -> Expression ;
                    return make_shared<ExpressionStatement>(
                        dynamic_pointer_cast<Expression>(nodes[0]));
                } else { // Statement -> Other statement types
                    return nodes[0]; // Just pass through the statement
                }
            }
            
            case NT_LET_STATEMENT: {
                // LetStatement -> LET IDENTIFIER = Expression IN Expression ;
                auto idToken = dynamic_pointer_cast<LiteralExpression>(nodes[1]);
                auto valueExpr = dynamic_pointer_cast<Expression>(nodes[3]);
                auto bodyExpr = dynamic_pointer_cast<Expression>(nodes[5]);
                return make_shared<LetStatement>(idToken->token.lexeme, valueExpr, bodyExpr);
            }
            
            case NT_IF_STATEMENT: {
                // If statement with various forms
                auto condition = dynamic_pointer_cast<Expression>(nodes[2]);
                auto thenBranch = dynamic_pointer_cast<Statement>(nodes[5]);
                
                auto ifStmt = make_shared<IfStatement>(condition, 
                    vector<shared_ptr<Statement>>{thenBranch});
                
                if (prod.rhs.size() > 7) {
                    // Has ELSE or ELIF
                    if (prod.rhs[7].id == HULK_LEXER::TokenType::ELSE) {
                        // IF ... ELSE ...
                        auto elseBranch = dynamic_pointer_cast<Statement>(nodes[9]);
                        ifStmt->setElseBranch(vector<shared_ptr<Statement>>{elseBranch});
                    } else {
                        // IF ... ELIF ...
                        auto elifCondition = dynamic_pointer_cast<Expression>(nodes[9]);
                        auto elifBranch = dynamic_pointer_cast<Statement>(nodes[12]);
                        ifStmt->setElifBranch(elifCondition, 
                            vector<shared_ptr<Statement>>{elifBranch});
                        
                        if (prod.rhs.size() > 14) {
                            // IF ... ELIF ... ELSE ...
                            auto elseBranch = dynamic_pointer_cast<Statement>(nodes[16]);
                            ifStmt->setElseBranch(vector<shared_ptr<Statement>>{elseBranch});
                        }
                    }
                }
                
                return ifStmt;
            }
            
            case NT_WHILE_STATEMENT: {
                // WhileStatement -> WHILE ( Expression ) { Statement }
                auto condition = dynamic_pointer_cast<Expression>(nodes[2]);
                auto body = dynamic_pointer_cast<Statement>(nodes[5]);
                return make_shared<WhileStatement>(condition, 
                    vector<shared_ptr<Statement>>{body});
            }
            
            case NT_FOR_STATEMENT: {
                // ForStatement -> FOR ( IDENTIFIER IN Expression ) { Statement }
                auto idToken = dynamic_pointer_cast<LiteralExpression>(nodes[2]);
                auto iterable = dynamic_pointer_cast<Expression>(nodes[4]);
                auto body = dynamic_pointer_cast<Statement>(nodes[7]);
                return make_shared<ForStatement>(idToken->token.lexeme, iterable, 
                    vector<shared_ptr<Statement>>{body});
            }
            
            case NT_FUNCTION_DECLARATION: {
                // FunctionDeclaration with or without parameters
                auto nameToken = dynamic_pointer_cast<LiteralExpression>(nodes[1]);
                vector<string> params;
                
                if (prod.rhs.size() == 7) {
                    // No parameters
                } else {
                    // With parameters
                    auto paramList = dynamic_pointer_cast<ASTNode>(nodes[3]);
                    // Extract parameters from paramList
                    // This is simplified - in a real implementation, you would extract all parameters
                    auto paramToken = dynamic_pointer_cast<LiteralExpression>(paramList);
                    if (paramToken) {
                        params.push_back(paramToken->token.lexeme);
                    }
                }
                
                auto body = dynamic_pointer_cast<Expression>(nodes[prod.rhs.size() - 2]);
                return make_shared<FunctionDeclaration>(nameToken->token.lexeme, params, body);
            }
            
            case NT_PRINT_STATEMENT: {
                // PrintStatement -> PRINT ( Expression ) ;
                auto expr = dynamic_pointer_cast<Expression>(nodes[2]);
                return make_shared<PrintStatement>(expr);
            }
            
            case NT_EXPRESSION: {
                // Various expression types
                if (prod.rhs.size() == 1) {
                    // Simple expressions (literal, identifier)
                    return nodes[0];
                } else if (prod.rhs.size() == 3 && prod.rhs[0].id == HULK_LEXER::TokenType::LPAREN) {
                    // ( Expression )
                    return nodes[1];
                } else {
                    // Other expression types
                    return nodes[0];
                }
            }
            
            case NT_UNARY_EXPRESSION: {
                // UnaryExpression -> - Expression or ! Expression
                auto expr = dynamic_pointer_cast<Expression>(nodes[1]);
                HULK_LEXER::TokenType op = static_cast<HULK_LEXER::TokenType>(prod.rhs[0].id);
                return make_shared<UnaryExpression>(op, expr);
            }
            
            case NT_BINARY_EXPRESSION: {
                // BinaryExpression -> Expression Op Expression
                auto left = dynamic_pointer_cast<Expression>(nodes[0]);
                HULK_LEXER::TokenType op = static_cast<HULK_LEXER::TokenType>(prod.rhs[1].id);
                auto right = dynamic_pointer_cast<Expression>(nodes[2]);
                return make_shared<BinaryExpression>(left, op, right);
            }
            
            case NT_FUNCTION_CALL: {
                // FunctionCall -> IDENTIFIER ( ArgumentList ) or IDENTIFIER ( )
                auto nameToken = dynamic_pointer_cast<LiteralExpression>(nodes[0]);
                vector<shared_ptr<Expression>> args;
                
                if (prod.rhs.size() == 4) {
                    // With arguments
                    auto argList = nodes[2];
                    // Extract arguments from argList
                    // This is simplified - in a real implementation, you would extract all arguments
                    auto arg = dynamic_pointer_cast<Expression>(argList);
                    if (arg) {
                        args.push_back(arg);
                    }
                }
                
                return make_shared<FunctionCallExpression>(nameToken->token.lexeme, args);
            }
            
            case NT_LET_IN_EXPRESSION: {
                // LetInExpression -> LET IDENTIFIER = Expression IN Expression
                auto idToken = dynamic_pointer_cast<LiteralExpression>(nodes[1]);
                auto valueExpr = dynamic_pointer_cast<Expression>(nodes[3]);
                auto bodyExpr = dynamic_pointer_cast<Expression>(nodes[5]);
                return make_shared<LetInExpression>(idToken->token.lexeme, valueExpr, bodyExpr);
            }
            
            case NT_IF_ELSE_EXPRESSION: {
                // IfElseExpression -> IF Expression THEN Expression ELSE Expression
                auto condition = dynamic_pointer_cast<Expression>(nodes[1]);
                auto thenExpr = dynamic_pointer_cast<Expression>(nodes[3]);
                auto elseExpr = dynamic_pointer_cast<Expression>(nodes[5]);
                return make_shared<IfElseExpression>(condition, thenExpr, elseExpr);
            }
            
            case NT_LITERAL: {
                // Literal -> NUMBER | STRING | TRUE | FALSE
                return nodes[0];
            }
            
            default:
                cerr << "Unknown production in reduce: " << productionId << endl;
                return nullptr;
        }
    }
    
    void Parser::syntaxError(const string& message) {
        if (currentToken < tokens.size()) {
            cerr << "Syntax error at line " << tokens[currentToken].line 
                      << ", column " << tokens[currentToken].col 
                      << ": " << message << endl;
        } else {
            cerr << "Syntax error at end of file: " << message << endl;
        }
    }
    
    shared_ptr<Program> Parser::parse() {
        // Initialize the state stack with the initial state (0)
        stateStack.push(0);
        
        // Main parsing loop
        while (true) {
            // Get the current token
            HULK_LEXER::Token token = tokens[currentToken];
            
            // Get the current state
            int state = stateStack.top();
            
            // Look up the action for the current state and token
            if (actionTable[state].find(token.type) == actionTable[state].end()) {
                syntaxError("Unexpected token: " + token.lexeme);
                return nullptr;
            }
            
            Action action = actionTable[state][token.type];
            
            // Perform the action
            if (action.type == ActionType::SHIFT) {
                // Shift: push the token onto the stack and move to the next token
                stateStack.push(action.value);
                nodeStack.push(make_shared<LiteralExpression>(token));
                currentToken++;
            } 
            else if (action.type == ActionType::REDUCE) {
                // Reduce: apply a production rule
                int productionId = action.value;
                Production& production = productions[productionId];
                
                // Pop the right-hand side symbols from the stack
                vector<shared_ptr<ASTNode>> nodes;
                for (int i = 0; i < production.rhs.size(); i++) {
                    stateStack.pop();
                    nodes.insert(nodes.begin(), nodeStack.top());
                    nodeStack.pop();
                }
                
                // Create a new AST node for the reduction
                shared_ptr<ASTNode> newNode = reduceProduction(productionId, nodes);
                nodeStack.push(newNode);
                
                // Look up the goto action
                int nextState = stateStack.top();
                if (gotoTable[nextState].find(production.lhs.id) == gotoTable[nextState].end()) {
                    syntaxError("Invalid state transition");
                    return nullptr;
                }
                
                stateStack.push(gotoTable[nextState][production.lhs.id]);
            } 
            else if (action.type == ActionType::ACCEPT) {
                // Accept: parsing is complete
                if (nodeStack.size() != 1) {
                    syntaxError("Invalid parse tree");
                    return nullptr;
                }
                
                // Return the root of the AST
                return dynamic_pointer_cast<Program>(nodeStack.top());
            } 
            else {
                // Error: invalid action
                syntaxError("Parsing error at token: " + token.lexeme);
                return nullptr;
            }
        }
    }
    
    } // namespace HULK_PARSER