#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    EXPONENT,
    LEFT_PARENS,
    RIGHT_PARENS,
};

enum class Associativity {
    LEFT,
    RIGHT,
};

class Token {
public:
    static constexpr unsigned NULL_PRECEDENCE = 0;

    // Operators
    static const Token ADD;
    static const Token SUBTRACT;
    static const Token MULTIPLY;
    static const Token DIVIDE;
    static const Token EXPONENT;
    static const Token LEFT_PARENS;
    static const Token RIGHT_PARENS;

    friend bool operator==(const Token& left, const Token& right);
    friend bool operator!=(const Token& left, const Token& right);
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

public:
    Token(TokenType type, const std::string& symbol, unsigned precedence, Associativity associativity = Associativity::LEFT);

    static const std::vector<Token>& checkable_tokens();

    // Getters
    TokenType type() const;
    const std::string& name() const;
    const std::string& symbol() const;
    double value() const;
    unsigned precedence() const;
    bool is_left_associative() const;

    // Setters
    void set_value(double value);

private:
    TokenType type_;
    const std::string symbol_;
    double value_;
    const unsigned precedence_;
    const Associativity associativity_;
};

#endif // TOKEN_H_