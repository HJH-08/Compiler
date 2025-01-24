#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class Lexer {
private:
    std::string source;
    size_t position = 0;
    char currentChar;
    
    std::unordered_map<std::string, TokenType> keywords = {
        {"let", TokenType::LET},
        {"if", TokenType::IF},
        {"while", TokenType::WHILE},
        {"print", TokenType::PRINT}
    };

    void advance();
    void skipWhitespace();
    Token number();
    Token identifier();

public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();
};

#endif // LEXER_HPP
