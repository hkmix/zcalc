#include "token.h"

#include "tokenizer_exception.h"

#include <unordered_map>

const Token Token::ADD{TokenType::ADD, "+", 10};
const Token Token::SUBTRACT{TokenType::SUBTRACT, "-", 10};
const Token Token::MULTIPLY{TokenType::MULTIPLY, "*", 15};
const Token Token::DIVIDE{TokenType::DIVIDE, "/", 15};

Token::Token(TokenType type, const std::string& symbol, unsigned precedence)
    : type_{type}
    , symbol_{symbol}
    , value_{0}
    , precedence_{precedence}
{
}

const std::vector<Token>& Token::checkable_tokens()
{
    static std::vector<Token> tokens{
        Token::ADD,
        Token::SUBTRACT,
        Token::MULTIPLY,
        Token::DIVIDE,
    };

    return tokens;
}

TokenType Token::type() const
{
    return type_;
}

const std::string& Token::symbol() const
{
    return symbol_;
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

    throw TokenizerException{TokenizerException::UNEXPECTED_TOKEN, 0};
}

OperatorType Token::operator_type() const
{
    static std::unordered_map<TokenType, OperatorType> operator_types{
        {TokenType::ADD, OperatorType::BINARY},
        {TokenType::SUBTRACT, OperatorType::BINARY},
        {TokenType::MULTIPLY, OperatorType::BINARY},
        {TokenType::DIVIDE, OperatorType::BINARY},
    };

    if (operator_types.find(type_) != operator_types.end()) {
        return operator_types[type_];
    }

    return OperatorType::NONE;
}

double Token::value() const
{
    return value_;
}

unsigned Token::precedence() const
{
    return precedence_;
}

void Token::set_value(double value)
{
    value_ = value;
}

bool operator==(const Token& left, const Token& right)
{
    if (left.type_ != right.type_) {
        return false;
    }

    return left.symbol_ == right.symbol_;
}

bool operator!=(const Token& left, const Token& right)
{
    return !(left == right);
}