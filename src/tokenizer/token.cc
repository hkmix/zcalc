#include "token.h"

#include "tokenizer_exception.h"

#include <iomanip>
#include <limits>
#include <unordered_map>

const Token Token::ADD{TokenType::ADD, "+", 10, Associativity::LEFT};
const Token Token::SUBTRACT{TokenType::SUBTRACT, "-", 10, Associativity::LEFT};
const Token Token::MULTIPLY{TokenType::MULTIPLY, "*", 15, Associativity::LEFT};
const Token Token::DIVIDE{TokenType::DIVIDE, "/", 15, Associativity::LEFT};
const Token Token::EXPONENT{TokenType::EXPONENT, "**", 20, Associativity::RIGHT};

const Token Token::LEFT_PARENS{TokenType::LEFT_PARENS, "(", Token::NULL_PRECEDENCE};
const Token Token::RIGHT_PARENS{TokenType::RIGHT_PARENS, ")", Token::NULL_PRECEDENCE};

Token::Token(TokenType type, const std::string& symbol, unsigned precedence, Associativity associativity)
    : type_{type}
    , symbol_{symbol}
    , value_{0}
    , precedence_{precedence}
    , associativity_{associativity}
{
}

const std::vector<Token>& Token::checkable_tokens()
{
    static std::vector<Token> tokens{
        Token::ADD,
        Token::SUBTRACT,
        Token::MULTIPLY,
        Token::DIVIDE,
        Token::EXPONENT,
        Token::LEFT_PARENS,
        Token::RIGHT_PARENS,
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
        {TokenType::EXPONENT, "EXPONENT"},
        {TokenType::LEFT_PARENS, "LEFT_PARENS"},
        {TokenType::RIGHT_PARENS, "RIGHT_PARENS"},
    };

    if (token_names.find(type_) != token_names.end()) {
        return token_names[type_];
    }

    throw TokenizerException{TokenizerException::UNEXPECTED_TOKEN, 0};
}

double Token::value() const
{
    return value_;
}

unsigned Token::precedence() const
{
    return precedence_;
}

bool Token::is_left_associative() const
{
    return associativity_ == Associativity::LEFT;
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

std::ostream& operator<<(std::ostream& out, const Token& token)
{
    out << token.name() << " ";

    if (token.type_ == TokenType::NUMBER) {
        // Use maximum possible precision
        out << std::setprecision(std::numeric_limits<double>::digits10 + 1) << token.value_;
    }
    else {
        out << token.symbol();
    }

    return out;
}