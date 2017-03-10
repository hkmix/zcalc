#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <vector>

enum class TokenType {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
};

enum class OperatorType {
    NONE,
    UNARY,
    BINARY,
};

class Token {
public:
    static constexpr unsigned NULL_PRECEDENCE = -1;

    static const Token NUMBER;
    static const Token ADD;
    static const Token SUBTRACT;
    static const Token MULTIPLY;
    static const Token DIVIDE;

    friend bool operator==(const Token& left, const Token& right);
    friend bool operator!=(const Token& left, const Token& right);

public:
    Token(TokenType type, const std::string& symbol, unsigned precedence);

    static const std::vector<Token>& checkable_tokens();

    // Getters
    TokenType type() const;
    OperatorType operator_type() const;
    const std::string& name() const;
    const std::string& symbol() const;
    double value() const;
    unsigned precedence() const;

    // Setters
    void set_value(double value);

private:
    TokenType type_;
    const std::string symbol_;
    double value_;
    const unsigned precedence_;
};

#endif // TOKEN_H_