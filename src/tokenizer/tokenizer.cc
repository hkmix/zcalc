#include "tokenizer.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

// Utility functions
namespace
{

bool idx_valid(const std::string& input, std::size_t idx)
{
    return idx < input.size();
}

bool is_digit(char c)
{
    return c == '_' || (c >= '0' && c <= '9');
}

} // namespace

// Tokenizer
Tokenizer::Tokenizer(const std::string& input)
{
    tokens_.clear();

    // Tokenize in greedy manner
    std::size_t idx = 0;

    while (idx_valid(input, idx)) {
        // Number, read it and continue
        if (is_digit(input[idx])) {
            idx = read_number(input, idx);
            continue;
        }

        // Operator, check for characters
        const Token* best_token = nullptr;
        for (const auto& token : Token::checkable_tokens()) {
            const auto len = token.symbol().size();
            const auto remaining_len = input.size() - idx;

            if (remaining_len < len) {
                continue;
            }

            if (input.substr(idx, len) == token.symbol() &&
                (best_token == nullptr || best_token->precedence() < token.precedence())) {
                best_token = &token;
            }
        }

        if (best_token != nullptr) {
            // Symbol was identified, add it
            tokens_.push_back(*best_token);
            idx += best_token->symbol().size();
        }
        else {
            // Prevent infinite loop on unrecognized values
            ++idx;
        }
    }

    // PASS 1: Negation
    for (std::size_t idx = 0; idx < tokens_.size() - 1; ++idx) {
        if (tokens_[idx].type() != TokenType::SUBTRACT) {
            continue;
        }

        if (idx == 0) {
            tokens_[idx] = Token::NEGATE;
            continue;
        }

        const auto& previous = tokens_[idx - 1];
        if (previous.is_operator() || previous.type() == TokenType::LEFT_PARENS) {
            tokens_[idx] = Token::NEGATE;
            continue;
        }
    }

    // PASS 2: Bracketed multiplication
    // When done, add a multiplication sign whenever we have braces not
    // followed by an operator to allow implicit multiplication
    for (std::size_t idx = 0; idx < tokens_.size() - 1; ++idx) {
        // Look forward one
        const auto& current = tokens_[idx];
        const auto& next = tokens_[idx + 1];
        if ((current.type() == TokenType::RIGHT_PARENS && !next.is_operator()) ||
            (next.type() == TokenType::LEFT_PARENS && !current.is_operator())) {
            tokens_.insert(tokens_.begin() + idx + 1, Token::MULTIPLY);
            ++idx;
        }
    }
}

const std::vector<Token>& Tokenizer::tokens() const
{
    return tokens_;
}

std::size_t Tokenizer::read_number(const std::string& input, std::size_t idx)
{
    // Valid number format:
    // [0-9]*(\.[0-9]*)? with underscores as separators
    std::size_t end_idx = idx;

    // Read value until period
    while (idx_valid(input, end_idx) && is_digit(input[end_idx])) {
        ++end_idx;
    }

    // Check for decimal component
    if (idx_valid(input, end_idx) && input[end_idx] == '.') {
        ++end_idx;

        // Get remaining numbers
        while (idx_valid(input, end_idx) && is_digit(input[end_idx])) {
            ++end_idx;
        }
    }

    // Tokenize and finish using std::stod
    std::string num_string{input.substr(idx, end_idx - idx)};
    num_string.erase(std::remove_if(num_string.begin(),
                                    num_string.end(),
                                    [](char c) { return c == '_'; }),
                     num_string.end());

    Token token{TokenType::NUMBER, num_string, Token::NULL_PRECEDENCE};

    token.set_value(std::stod(num_string));
    tokens_.push_back(token);

    return end_idx;
}

std::ostream& operator<<(std::ostream& out, const Tokenizer& tokenizer)
{
    out << "Tokenizer: total " << tokenizer.tokens_.size() << " tokens\n";
    for (const auto& token : tokenizer.tokens_) {
        out << "  " << token << "\n";
    }

    return out;
}
