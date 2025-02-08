#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "ast.hpp"
#include <vector>
#include <memory>

class Parser {
private:
    std::vector<Token> tokens;   // List of tokens from the lexer
    size_t position = 0;         // Current position in the token list

    Token currentToken();        // Get the current token
    void advance();              // Move to the next token
    bool match(TokenType type);  // Check and consume a token if it matches

    std::unique_ptr<ASTNode> parseStatement();  // Parses a single statement
    std::unique_ptr<ASTNode> parseExpression(); // Parses an expression
    std::unique_ptr<ASTNode> parsePrimary();    // Parses numbers & variables

public:
    explicit Parser(const std::vector<Token>& tokens); // Constructor
    std::unique_ptr<ProgramNode> parse();             // Parse entire program
};

#endif // PARSER_HPP
