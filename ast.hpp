#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <vector>

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() noexcept = default; // Ensure proper cleanup of derived classes
};

// Represents an integer value (e.g., "10", "42")
class IntegerNode : public ASTNode {
public:
    int value;

    IntegerNode(int value) : value(value) {}
};

// Represents a variable name (e.g., "sum", "x")
class IdentifierNode : public ASTNode {
public:
    std::string name;

    IdentifierNode(const std::string& name) : name(name) {}
};

// Represents binary operations (e.g., "x + y", "a * b")
class BinaryExpressionNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> left;
    std::string op;
    std::unique_ptr<ASTNode> right;

    BinaryExpressionNode(std::unique_ptr<ASTNode> left, const std::string& op, std::unique_ptr<ASTNode> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    ~BinaryExpressionNode() noexcept override = default;
};

// Represents a variable assignment (e.g., "let sum = x + y;")
class VariableAssignmentNode : public ASTNode {
public:
    std::string variableName;
    std::unique_ptr<ASTNode> expression;

    VariableAssignmentNode(const std::string& variableName, std::unique_ptr<ASTNode> expression)
        : variableName(variableName), expression(std::move(expression)) {}
    
    ~VariableAssignmentNode() noexcept override = default;
};

// Represents a print statement (e.g., "print(sum);")
class PrintStatementNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> expression;

    PrintStatementNode(std::unique_ptr<ASTNode> expression)
        : expression(std::move(expression)) {}
    ~PrintStatementNode() noexcept override = default;
};

// Represents the entire program as a list of statements
class ProgramNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;

    void addStatement(std::unique_ptr<ASTNode> statement) {
        statements.push_back(std::move(statement));
    }
};

#endif // AST_HPP
