#ifndef TOKEN_H_
#define TOKEN_H_

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using value_t = long double;
using int_value_t = long long;
using uint_value_t = unsigned long long;

enum class TokenType {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    EXPONENT,
    NEGATE,
    LEFT_PARENS,
    RIGHT_PARENS,
};

enum class Associativity {
    NONE,
    LEFT,
    RIGHT,
};

class Token {
public:
    static constexpr unsigned NULL_PRECEDENCE = 0;

    // Constants
    static const Token PI;
    static const Token NATURAL_E;

    static constexpr value_t PI_VAL = 3.141592653589793238462643383279502884L;
    static constexpr value_t E_VAL = 2.718281828459045235360287471352662498L;

    // Operators
    static const Token ADD;
    static const Token SUBTRACT;
    static const Token MULTIPLY;
    static const Token DIVIDE;
    static const Token EXPONENT;
    static const Token NEGATE;
    static const Token LEFT_PARENS;
    static const Token RIGHT_PARENS;

    friend bool operator==(const Token& left, const Token& right);
    friend bool operator!=(const Token& left, const Token& right);
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

public:
    Token(TokenType type, const std::string& symbol, unsigned precedence,
          Associativity associativity = Associativity::NONE, value_t value = 0.0L);

    Token(const Token&) = default;
    Token& operator=(const Token&) = default;

    static const std::vector<Token>& checkable_tokens();

    // Getters
    TokenType type() const;
    const std::string& name() const;
    const std::string& symbol() const;
    value_t value() const;
    unsigned precedence() const;
    bool is_left_associative() const;
    bool is_operator() const;

    // Setters
    void set_value(value_t value);

private:
    TokenType type_;
    std::string symbol_;
    value_t value_;
    unsigned precedence_;
    Associativity associativity_;
};

#endif // TOKEN_H_