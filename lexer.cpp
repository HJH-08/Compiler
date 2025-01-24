#include "lexer.hpp"
#include <cctype>
#include <iostream>

// Constructor: Initializes lexer with the source code
Lexer::Lexer(const std::string& src) : source(src), position(0) {
    currentChar = source[position];
}

// Move to the next character
void Lexer::advance() {
    position++;
    if (position < source.size()) {
        currentChar = source[position];
    } else {
        currentChar = '\0';  // End of file
    }
}

// Skip whitespace characters
void Lexer::skipWhitespace() {
    while (isspace(currentChar)) {
        advance();
    }
}

// Parse an integer token
Token Lexer::number() {
    std::string num;
    while (isdigit(currentChar)) {
        num += currentChar;
        advance();
    }
    return Token(TokenType::INTEGER, num);
}

// Parse an identifier or keyword
Token Lexer::identifier() {
    std::string ident;
    while (isalnum(currentChar)) {
        ident += currentChar;
        advance();
    }

    // Check if it's a keyword
    if (keywords.find(ident) != keywords.end()) {
        return Token(keywords[ident], ident);
    }
    
    return Token(TokenType::IDENTIFIER, ident);
}

// Convert source code into tokens
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (currentChar != '\0') {
        if (isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (isdigit(currentChar)) {
            tokens.push_back(number());
            continue;
        }

        if (isalpha(currentChar)) {
            tokens.push_back(identifier());
            continue;
        }

        switch (currentChar) {
            case '=':
                tokens.push_back(Token(TokenType::ASSIGN, "="));
                break;
            case '+':
                tokens.push_back(Token(TokenType::PLUS, "+"));
                break;
            case '-':
                tokens.push_back(Token(TokenType::MINUS, "-"));
                break;
            case '*':
                tokens.push_back(Token(TokenType::MULTIPLY, "*"));
                break;
            case '/':
                tokens.push_back(Token(TokenType::DIVIDE, "/"));
                break;
            case '<':
                tokens.push_back(Token(TokenType::LESS, "<"));
                break;
            case '>':
                tokens.push_back(Token(TokenType::GREATER, ">"));
                break;
            case '(':
                tokens.push_back(Token(TokenType::LPAREN, "("));
                break;
            case ')':
                tokens.push_back(Token(TokenType::RPAREN, ")"));
                break;
            case '{':
                tokens.push_back(Token(TokenType::LBRACE, "{"));
                break;
            case '}':
                tokens.push_back(Token(TokenType::RBRACE, "}"));
                break;
            case ';':
                tokens.push_back(Token(TokenType::SEMICOLON, ";"));
                break;
            default:
                std::cerr << "Unexpected character: " << currentChar << std::endl;
                break;
        }
        advance();
    }

    tokens.push_back(Token(TokenType::EOF_TOKEN, "EOF"));
    return tokens;
}
