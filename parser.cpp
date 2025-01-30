#include "parser.hpp"
#include <iostream>

// Constructor: Initializes parser with tokens
Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), position(0) {}

// Returns the current token
Token Parser::currentToken() {
    if (position < tokens.size()) {
        return tokens[position];
    }
    return Token(TokenType::EOF_TOKEN, "EOF");
}

// Moves to the next token
void Parser::advance() {
    if (position < tokens.size()) {
        position++;
    }
}

// Matches a token type and advances if it matches
bool Parser::match(TokenType type) {
    if (currentToken().type == type) {
        advance();
        return true;
    }
    return false;
}

// Parses the entire program
std::unique_ptr<ProgramNode> Parser::parse() {
    auto program = std::make_unique<ProgramNode>();

    while (currentToken().type != TokenType::EOF_TOKEN) {
        program->addStatement(parseStatement());
    }

    return program;
}

// Parses a single statement (Variable Assignment or Print)
std::unique_ptr<ASTNode> Parser::parseStatement() {
    if (match(TokenType::LET)) {
        // Variable Assignment: let x = 10;
        std::string varName = currentToken().value;
        advance(); // Consume identifier
        if (!match(TokenType::ASSIGN)) {
            throw std::runtime_error("Expected '=' in assignment");
        }
        auto expr = parseExpression();
        if (!match(TokenType::SEMICOLON)) {
            throw std::runtime_error("Expected ';' after assignment");
        }
        return std::make_unique<VariableAssignmentNode>(varName, std::move(expr));
    }

    if (match(TokenType::PRINT)) {
        // Print Statement: print(x);
        if (!match(TokenType::LPAREN)) {
            throw std::runtime_error("Expected '(' after 'print'");
        }
        auto expr = parseExpression();
        if (!match(TokenType::RPAREN)) {
            throw std::runtime_error("Expected ')' after expression");
        }
        if (!match(TokenType::SEMICOLON)) {
            throw std::runtime_error("Expected ';' after print statement");
        }
        return std::make_unique<PrintStatementNode>(std::move(expr));
    }

    throw std::runtime_error("Unexpected statement");
}

// Parses an expression (Handles + and - operators)
std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto left = parsePrimary();

    while (currentToken().type == TokenType::PLUS || currentToken().type == TokenType::MINUS) {
        std::string op = currentToken().value;
        advance();
        auto right = parsePrimary();
        left = std::make_unique<BinaryExpressionNode>(std::move(left), op, std::move(right));
    }

    return left;
}

// Parses primary expressions (Numbers and Identifiers)
std::unique_ptr<ASTNode> Parser::parsePrimary() {
    if (currentToken().type == TokenType::INTEGER) {
        int value = std::stoi(currentToken().value);
        advance();
        return std::make_unique<IntegerNode>(value);
    }

    if (currentToken().type == TokenType::IDENTIFIER) {
        std::string name = currentToken().value;
        advance();
        return std::make_unique<IdentifierNode>(name);
    }

    throw std::runtime_error("Unexpected token in expression");
}
