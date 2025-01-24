#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

// Define token types
enum class TokenType {
    LET, IF, WHILE, PRINT, // Keywords
    IDENTIFIER, INTEGER,    // Values
    ASSIGN, PLUS, MINUS, MULTIPLY, DIVIDE,  // Operators
    LESS, GREATER, LPAREN, RPAREN,  // Symbols
    LBRACE, RBRACE, SEMICOLON, EOF_TOKEN  // Structural tokens
};

// Token class
class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(value) {} // initialisation
};

#endif 
