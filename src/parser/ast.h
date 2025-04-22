#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include "../lexer/token.h"
#include "../lexer/tokenType.h"

using namespace std;

namespace HULK_PARSER {

// Forward declarations
class Expression;
class Statement;

// Base AST Node
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual string toString() const = 0;
};

// Program node - root of the AST
class Program : public ASTNode {
public:
    vector<shared_ptr<Statement>> statements;

    Program() = default;
    void addStatement(shared_ptr<Statement> stmt);
    string toString() const override;
};

// Base Statement node
class Statement : public ASTNode {
public:
    virtual ~Statement() = default;
};

// Expression Statement
class ExpressionStatement : public Statement {
public:
    shared_ptr<Expression> expression;

    ExpressionStatement(shared_ptr<Expression> expr);
    string toString() const override;
};

// Let Statement
class LetStatement : public Statement {
public:
    string identifier;
    shared_ptr<Expression> value;
    shared_ptr<Expression> body;

    LetStatement(const string& id, shared_ptr<Expression> val, shared_ptr<Expression> body);
    string toString() const override;
};

// If Statement
class IfStatement : public Statement {
public:
    shared_ptr<Expression> condition;
    vector<shared_ptr<Statement>> thenBranch;
    vector<shared_ptr<Statement>> elseBranch;
    shared_ptr<Expression> elifCondition;
    vector<shared_ptr<Statement>> elifBranch;

    IfStatement(shared_ptr<Expression> cond, 
                vector<shared_ptr<Statement>> thenStmts);
    
    void setElseBranch(vector<shared_ptr<Statement>> elseStmts);
    void setElifBranch(shared_ptr<Expression> elifCond, 
                       vector<shared_ptr<Statement>> elifStmts);
    
    string toString() const override;
};

// While Statement
class WhileStatement : public Statement {
public:
    shared_ptr<Expression> condition;
    vector<shared_ptr<Statement>> body;

    WhileStatement(shared_ptr<Expression> cond, 
                  vector<shared_ptr<Statement>> bodyStmts);
    string toString() const override;
};

// For Statement
class ForStatement : public Statement {
public:
    string variable;
    shared_ptr<Expression> iterable;
    vector<shared_ptr<Statement>> body;

    ForStatement(const string& var, shared_ptr<Expression> iter, 
                vector<shared_ptr<Statement>> bodyStmts);
    string toString() const override;
};

// Function Declaration
class FunctionDeclaration : public Statement {
public:
    string name;
    vector<string> parameters;
    shared_ptr<Expression> body;

    FunctionDeclaration(const string& name, 
                       vector<string> params, 
                       shared_ptr<Expression> body);
    string toString() const override;
};

// Print Statement
class PrintStatement : public Statement {
public:
    shared_ptr<Expression> expression;

    PrintStatement(shared_ptr<Expression> expr);
    string toString() const override;
};

// Base Expression node
class Expression : public ASTNode {
public:
    virtual ~Expression() = default;
};

// Literal Expression
class LiteralExpression : public Expression {
public:
    HULK_LEXER::Token token;

    LiteralExpression(const HULK_LEXER::Token& token);
    string toString() const override;
};

// Identifier Expression
class IdentifierExpression : public Expression {
public:
    string name;

    IdentifierExpression(const string& name);
    string toString() const override;
};

// Unary Expression
class UnaryExpression : public Expression {
public:
    HULK_LEXER::TokenType op;
    shared_ptr<Expression> right;

    UnaryExpression(HULK_LEXER::TokenType op, shared_ptr<Expression> right);
    string toString() const override;
};

// Binary Expression
class BinaryExpression : public Expression {
public:
    shared_ptr<Expression> left;
    HULK_LEXER::TokenType op;
    shared_ptr<Expression> right;

    BinaryExpression(shared_ptr<Expression> left, 
                    HULK_LEXER::TokenType op, 
                    shared_ptr<Expression> right);
    string toString() const override;
};

// Function Call Expression
class FunctionCallExpression : public Expression {
public:
    string callee;
    vector<shared_ptr<Expression>> arguments;

    FunctionCallExpression(const string& callee, 
                          vector<shared_ptr<Expression>> args);
    string toString() const override;
};

// Let-In Expression
class LetInExpression : public Expression {
public:
    string identifier;
    shared_ptr<Expression> value;
    shared_ptr<Expression> body;

    LetInExpression(const string& id, 
                   shared_ptr<Expression> val, 
                   shared_ptr<Expression> body);
    string toString() const override;
};

// If-Else Expression
class IfElseExpression : public Expression {
public:
    shared_ptr<Expression> condition;
    shared_ptr<Expression> thenBranch;
    shared_ptr<Expression> elseBranch;

    IfElseExpression(shared_ptr<Expression> cond, 
                    shared_ptr<Expression> thenExpr, 
                    shared_ptr<Expression> elseExpr);
    string toString() const override;
};

} // namespace HULK_PARSER

#endif // AST_H