#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

enum class TokenType {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
};

class Token {
public:
    static const Token NUMBER;
    static const Token ADD;
    static const Token SUBTRACT;
    static const Token MULTIPLY;
    static const Token DIVIDE;

    friend bool operator==(const Token& left, const Token& right);
    friend bool operator!=(const Token& left, const Token& right);

public:
    Token(TokenType type, const std::string& symbol);

    // Getter
    TokenType type() const;
    const std::string& name() const;
    double value() const;

    // Setter
    void set_value(double value);

private:
    TokenType type_;
    const std::string symbol_;
    double value_;
};

#endif // TOKEN_H_