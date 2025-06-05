#include "ast.hpp"
#include <iostream>
#include <cstring>

ASTNode::~ASTNode() {
    switch(type) {
        case ASTNodeType::VAR: 
            delete[] var_name;
            break;
        case ASTNodeType::STRING:
            delete[] string_value;
            break;
        default:
            break;
    }
}

std::unique_ptr<ASTNode> create_num_node(int value) {
    auto node = std::make_unique<ASTNode>();
    node->type = ASTNodeType::NUM;
    node->value = value;
    return node;
}

std::unique_ptr<ASTNode> create_var_node(const std::string& name) {
    auto node = std::make_unique<ASTNode>();
    node->type = ASTNodeType::VAR;
    node->var_name = new char[name.size() + 1];
    std::strcpy(node->var_name, name.c_str());
    return node;
}

std::unique_ptr<ASTNode> create_string_node(const std::string& value) {
    auto node = std::make_unique<ASTNode>();
    node->type = ASTNodeType::STRING;
    node->string_value = new char[value.size() + 1];
    std::strcpy(node->string_value, value.c_str());
    return node;
}

std::unique_ptr<ASTNode> create_op_node(ASTNodeType type,
                                      std::unique_ptr<ASTNode> left,
                                      std::unique_ptr<ASTNode> right) {
    auto node = std::make_unique<ASTNode>();
    node->type = type;
    node->left = std::move(left);
    node->right = std::move(right);
    return node;
}

std::unique_ptr<ASTNode> create_print_node(std::unique_ptr<ASTNode> expr) {
    auto node = std::make_unique<ASTNode>();
    node->type = ASTNodeType::PRINT;
    node->left = std::move(expr);
    return node;
}

std::unique_ptr<ASTNode> create_if_node(std::unique_ptr<ASTNode> condition,
                                      std::unique_ptr<ASTNode> then_branch,
                                      std::unique_ptr<ASTNode> else_branch) {
    auto node = std::make_unique<ASTNode>();
    node->type = ASTNodeType::IF;
    node->condition = std::move(condition);
    node->left = std::move(then_branch);
    node->else_branch = std::move(else_branch);
    return node;
}

std::unique_ptr<ASTNode> create_seq_node(std::unique_ptr<ASTNode> first,
                                       std::unique_ptr<ASTNode> second) {
    auto node = std::make_unique<ASTNode>();
    node->type = ASTNodeType::SEQ;
    node->left = std::move(first);
    node->right = std::move(second);
    return node;
}

std::unique_ptr<ASTNode> create_let_node(std::unique_ptr<VarBinding> bindings,
                                       std::unique_ptr<ASTNode> body) {
    auto node = std::make_unique<ASTNode>();
    node->type = ASTNodeType::LET;
    node->bindings = std::move(bindings);
    node->left = std::move(body);
    return node;
}

std::unique_ptr<VarBinding> create_binding(const std::string& name,
                                         std::unique_ptr<ASTNode> value) {
    auto binding = std::make_unique<VarBinding>();
    binding->name = name;
    binding->value = std::move(value);
    return binding;
}

std::unique_ptr<VarBinding> append_binding_list(std::unique_ptr<VarBinding> list,
                                              std::unique_ptr<VarBinding> new_binding) {
    if (!list) return new_binding;

    VarBinding* current = list.get();
    while (current->next) {
        current = current->next.get();
    }
    current->next = std::move(new_binding);
    return list;
}

void print_bindings(const std::unique_ptr<VarBinding>& bindings, int indent) {
    const VarBinding* current = bindings.get();
    while (current) {
        for (int i = 0; i < indent; i++) std::cout << " ";
        std::cout << "Binding: " << current->name << " = \n";
        print_ast(current->value, indent + 1);
        current = current->next.get();
    }
}

void print_ast(const std::unique_ptr<ASTNode>& node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) std::cout << "  ";

    switch (node->type) {
        case ASTNodeType::NUM:
            std::cout << "NUM: " << node->value << "\n";
            break;
        case ASTNodeType::VAR:
            std::cout << "Variable: " << node->var_name << "\n";
            break;
        case ASTNodeType::STRING:
            std::cout << "String: " << node->string_value << "\n";
            break;
        case ASTNodeType::ADD: std::cout << "ADD\n"; goto binary;
        case ASTNodeType::SUB: std::cout << "SUB\n"; goto binary;
        case ASTNodeType::CONCAT: std::cout << "CONCAT\n"; goto binary;
        case ASTNodeType::MUL: std::cout << "MUL\n"; goto binary;
        case ASTNodeType::DIV: std::cout << "DIV\n"; goto binary;
        case ASTNodeType::GT: std::cout << "GT\n"; goto binary;
        case ASTNodeType::LT: std::cout << "LT\n"; goto binary;
        case ASTNodeType::EQ: std::cout << "EQ\n"; goto binary;
        case ASTNodeType::GE: std::cout << "GE\n"; goto binary;
        case ASTNodeType::LE: std::cout << "LE\n"; goto binary;
        case ASTNodeType::PRINT:
            std::cout << "PRINT\n";
            print_ast(node->left, indent + 1);
            break;
        case ASTNodeType::IF:
            std::cout << "IF\n";
            for (int i = 0; i < indent + 1; i++) std::cout << "  ";
            std::cout << "Condition:\n";
            print_ast(node->condition, indent + 2);
            for (int i = 0; i < indent + 1; i++) std::cout << "  ";
            std::cout << "Then:\n";
            print_ast(node->left, indent + 2);
            for (int i = 0; i < indent + 1; i++) std::cout << "  ";
            std::cout << "Else:\n";
            print_ast(node->else_branch, indent + 2);
            break;
        case ASTNodeType::SEQ:
            std::cout << "SEQ\n";
            goto binary;
        case ASTNodeType::LET:
            std::cout << "LET:\n";
            print_bindings(node->bindings, indent + 1);
            for (int i = 0; i < indent; i++) std::cout << "  ";
            std::cout << "Body:\n";
            print_ast(node->left, indent + 1);
            break;
        binary:
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        default:
            std::cout << "Unknown AST node type\n";
    }
}