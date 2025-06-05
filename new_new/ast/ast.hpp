#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

enum class ASTNodeType {
    NUM, VAR, STRING,
    ADD, SUB, MUL, DIV, CONCAT,
    GT, LT, EQ, GE, LE,
    PRINT, IF, SEQ, LET
};

struct VarBinding;

struct ASTNode {
    ASTNodeType type;
    union {
        int value;
        char* var_name;
        char* string_value;
    };
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> else_branch;
    std::unique_ptr<VarBinding> bindings;

    ~ASTNode(); // Destructor para manejar la memoria de la union
};

struct VarBinding {
    std::string name;
    std::unique_ptr<ASTNode> value;
    std::unique_ptr<VarBinding> next;
};

// Funciones factory
std::unique_ptr<ASTNode> create_num_node(int value);
std::unique_ptr<ASTNode> create_var_node(const std::string& name);
std::unique_ptr<ASTNode> create_string_node(const std::string& value);
std::unique_ptr<ASTNode> create_op_node(ASTNodeType type, 
                                      std::unique_ptr<ASTNode> left, 
                                      std::unique_ptr<ASTNode> right);
std::unique_ptr<ASTNode> create_print_node(std::unique_ptr<ASTNode> expr);
std::unique_ptr<ASTNode> create_if_node(std::unique_ptr<ASTNode> condition, 
                                      std::unique_ptr<ASTNode> then_branch, 
                                      std::unique_ptr<ASTNode> else_branch);
std::unique_ptr<ASTNode> create_seq_node(std::unique_ptr<ASTNode> first, 
                                       std::unique_ptr<ASTNode> second);
std::unique_ptr<ASTNode> create_let_node(std::unique_ptr<VarBinding> bindings, 
                                       std::unique_ptr<ASTNode> body);

// Funciones para bindings
std::unique_ptr<VarBinding> create_binding(const std::string& name, 
                                         std::unique_ptr<ASTNode> value);
std::unique_ptr<VarBinding> append_binding_list(std::unique_ptr<VarBinding> list, 
                                              std::unique_ptr<VarBinding> new_binding);

// Funciones de utilidad
void print_ast(const std::unique_ptr<ASTNode>& node, int indent = 0);
void print_bindings(const std::unique_ptr<VarBinding>& bindings, int indent);

#endif