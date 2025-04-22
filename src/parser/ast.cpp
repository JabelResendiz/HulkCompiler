#include "ast.h"
#include <sstream>

using namespace std;

namespace HULK_PARSER {

// Program implementation
void Program::addStatement(shared_ptr<Statement> stmt) {
    statements.push_back(stmt);
}

string Program::toString() const {
    stringstream ss;
    ss << "Program {\n";
    for (const auto& stmt : statements) {
        ss << "  " << stmt->toString() << "\n";
    }
    ss << "}";
    return ss.str();
}

// ExpressionStatement implementation
ExpressionStatement::ExpressionStatement(shared_ptr<Expression> expr) 
    : expression(expr) {}

string ExpressionStatement::toString() const {
    return "ExpressionStatement { " + expression->toString() + " }";
}

// LetStatement implementation
LetStatement::LetStatement(const string& id, shared_ptr<Expression> val, 
                         shared_ptr<Expression> b) 
    : identifier(id), value(val), body(b) {}

string LetStatement::toString() const {
    return "LetStatement { " + identifier + " = " + value->toString() + 
           " in " + body->toString() + " }";
}

// IfStatement implementation
IfStatement::IfStatement(shared_ptr<Expression> cond, 
                       vector<shared_ptr<Statement>> thenStmts) 
    : condition(cond), thenBranch(thenStmts) {}

void IfStatement::setElseBranch(vector<shared_ptr<Statement>> elseStmts) {
    elseBranch = elseStmts;
}

void IfStatement::setElifBranch(shared_ptr<Expression> elifCond, 
                              vector<shared_ptr<Statement>> elifStmts) {
    elifCondition = elifCond;
    elifBranch = elifStmts;
}

string IfStatement::toString() const {
    stringstream ss;
    ss << "IfStatement { condition: " << condition->toString() << ", then: [";
    
    for (size_t i = 0; i < thenBranch.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << thenBranch[i]->toString();
    }
    ss << "]";
    
    if (elifCondition) {
        ss << ", elif condition: " << elifCondition->toString() << ", elif: [";
        for (size_t i = 0; i < elifBranch.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << elifBranch[i]->toString();
        }
        ss << "]";
    }
    
    if (!elseBranch.empty()) {
        ss << ", else: [";
        for (size_t i = 0; i < elseBranch.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << elseBranch[i]->toString();
        }
        ss << "]";
    }
    
    ss << " }";
    return ss.str();
}

// WhileStatement implementation
WhileStatement::WhileStatement(shared_ptr<Expression> cond, 
                             vector<shared_ptr<Statement>> bodyStmts) 
    : condition(cond), body(bodyStmts) {}

string WhileStatement::toString() const {
    stringstream ss;
    ss << "WhileStatement { condition: " << condition->toString() << ", body: [";
    
    for (size_t i = 0; i < body.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << body[i]->toString();
    }
    ss << "] }";
    
    return ss.str();
}

// ForStatement implementation
ForStatement::ForStatement(const string& var, shared_ptr<Expression> iter, 
                         vector<shared_ptr<Statement>> bodyStmts) 
    : variable(var), iterable(iter), body(bodyStmts) {}

string ForStatement::toString() const {
    stringstream ss;
    ss << "ForStatement { variable: " << variable 
       << ", iterable: " << iterable->toString() << ", body: [";
    
    for (size_t i = 0; i < body.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << body[i]->toString();
    }
    ss << "] }";
    
    return ss.str();
}

// FunctionDeclaration implementation
FunctionDeclaration::FunctionDeclaration(const string& n, 
                                       vector<string> params, 
                                       shared_ptr<Expression> b) 
    : name(n), parameters(params), body(b) {}

string FunctionDeclaration::toString() const {
    stringstream ss;
    ss << "FunctionDeclaration { name: " << name << ", parameters: [";
    
    for (size_t i = 0; i < parameters.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << parameters[i];
    }
    ss << "], body: " << body->toString() << " }";
    
    return ss.str();
}

// PrintStatement implementation
PrintStatement::PrintStatement(shared_ptr<Expression> expr) 
    : expression(expr) {}

string PrintStatement::toString() const {
    return "PrintStatement { " + expression->toString() + " }";
}

// LiteralExpression implementation
LiteralExpression::LiteralExpression(const HULK_LEXER::Token& t) 
    : token(t) {}

string LiteralExpression::toString() const {
    return "Literal(" + token.lexeme + ")";
}

// IdentifierExpression implementation
IdentifierExpression::IdentifierExpression(const string& n) 
    : name(n) {}

string IdentifierExpression::toString() const {
    return "Identifier(" + name + ")";
}

// UnaryExpression implementation
UnaryExpression::UnaryExpression(HULK_LEXER::TokenType o, shared_ptr<Expression> r) 
    : op(o), right(r) {}

string UnaryExpression::toString() const {
    string opStr;
    switch (op) {
        case HULK_LEXER::TokenType::MINUS: opStr = "-"; break;
        case HULK_LEXER::TokenType::NOT: opStr = "!"; break;
        default: opStr = "unknown"; break;
    }
    
    return "Unary(" + opStr + ", " + right->toString() + ")";
}

// BinaryExpression implementation
BinaryExpression::BinaryExpression(shared_ptr<Expression> l, 
                                 HULK_LEXER::TokenType o, 
                                 shared_ptr<Expression> r) 
    : left(l), op(o), right(r) {}

string BinaryExpression::toString() const {
    string opStr;
    switch (op) {
        case HULK_LEXER::TokenType::PLUS: opStr = "+"; break;
        case HULK_LEXER::TokenType::MINUS: opStr = "-"; break;
        case HULK_LEXER::TokenType::MULT: opStr = "*"; break;
        case HULK_LEXER::TokenType::DIV: opStr = "/"; break;
        case HULK_LEXER::TokenType::MOD: opStr = "%"; break;
        case HULK_LEXER::TokenType::POW: opStr = "^"; break;
        case HULK_LEXER::TokenType::EQ: opStr = "=="; break;
        case HULK_LEXER::TokenType::NEQ: opStr = "!="; break;
        case HULK_LEXER::TokenType::LT: opStr = "<"; break;
        case HULK_LEXER::TokenType::GT: opStr = ">"; break;
        case HULK_LEXER::TokenType::LTE: opStr = "<="; break;
        case HULK_LEXER::TokenType::GTE: opStr = ">="; break;
        case HULK_LEXER::TokenType::AND: opStr = "&"; break;
        case HULK_LEXER::TokenType::OR: opStr = "|"; break;
        default: opStr = "unknown"; break;
    }
    
    return "Binary(" + left->toString() + " " + opStr + " " + right->toString() + ")";
}

// FunctionCallExpression implementation
FunctionCallExpression::FunctionCallExpression(const string& c, 
                                             vector<shared_ptr<Expression>> args) 
    : callee(c), arguments(args) {}

string FunctionCallExpression::toString() const {
    stringstream ss;
    ss << "FunctionCall(" << callee << ", [";
    
    for (size_t i = 0; i < arguments.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << arguments[i]->toString();
    }
    ss << "])";
    
    return ss.str();
}

// LetInExpression implementation
LetInExpression::LetInExpression(const string& id, 
                               shared_ptr<Expression> val, 
                               shared_ptr<Expression> b) 
    : identifier(id), value(val), body(b) {}

string LetInExpression::toString() const {
    return "LetIn(" + identifier + " = " + value->toString() + 
           " in " + body->toString() + ")";
}

// IfElseExpression implementation
IfElseExpression::IfElseExpression(shared_ptr<Expression> cond, 
                                 shared_ptr<Expression> thenExpr, 
                                 shared_ptr<Expression> elseExpr) 
    : condition(cond), thenBranch(thenExpr), elseBranch(elseExpr) {}

string IfElseExpression::toString() const {
    return "IfElse(if " + condition->toString() + 
           " then " + thenBranch->toString() + 
           " else " + elseBranch->toString() + ")";
}

} // namespace HULK_PARSER