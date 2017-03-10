#include "token.h"

#include <unordered_map>

const Token Token::ADD{TokenType::ADD, "+"};
const Token Token::SUBTRACT{TokenType::SUBTRACT, "-"};
const Token Token::MULTIPLY{TokenType::MULTIPLY, "*"};
const Token Token::DIVIDE{TokenType::DIVIDE,  "/"};

Token::Token(TokenType type,  const std::string& symbol)
    : type_{type}
    , symbol_{symbol}
    , value_{0}
{
}

TokenType Token::type() const
{
    return type_;
}

const std::string& Token::name() const
{
    static std::unordered_map<TokenType, std::string> token_names{
        {TokenType::NUMBER, "NUMBER"},
        {TokenType::ADD, "ADD"},
        {TokenType::SUBTRACT, "SUBTRACT"},
        {TokenType::MULTIPLY, "MULTIPLY"},
        {TokenType::DIVIDE, "DIVIDE"},
    };

    if (token_names.find(type_) != token_names.end()) {
        return token_names[type_];
    }
}

double Token::value() const
{
    return value_;
}

void Token::set_value(double value)
{
    value_ = value;
}

bool operator==(const Token& left, const Token& right)
{
    return left.type_ == right.type_ && left.name() == right.name();
}

bool operator!=(const Token& left, const Token& right)
{
    return !(left == right);
}