#include "tokenizer.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

// Utility functions
namespace
{

bool idx_valid(const std::string& input, std::size_t idx)
{
    return idx >= 0 && idx < input.size();
}

bool is_digit(char c)
{
    return c == '_' || (c >= '0' && c <= '9');
}

} // namespace

// Tokenizer
void Tokenizer::tokenize(const std::string& input)
{
    tokens_.clear();

    // Tokenize in greedy manner
    std::size_t idx = 0;

    while (idx_valid(input, idx)) {
        bool operated = false;

        if (is_digit(input[idx])) {
            idx = read_number(input, idx);
            operated = true;
        }

        // Prevent infinite loop on invalid value
        if (!operated) {
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
    double value = 0;

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

    // Tokenize and finish
    std::string num_string{input.substr(idx, end_idx - idx)};
    num_string.erase(std::remove_if(num_string.begin(),
                                    num_string.end(),
                                    [](char c) { return c == '_'; }),
                     num_string.end());

    Token token{TokenType::NUMBER, num_string};

    token.set_value(std::stod(num_string));
    tokens_.push_back(token);

    return end_idx;
}

std::ostream& operator<<(std::ostream& out, const Tokenizer& tokenizer)
{
    out << "Total " << tokenizer.tokens_.size() << " tokens\n";
    for (const auto& token : tokenizer.tokens_) {
        out << "  " << token.name();

        // Print the value if it is a number
        if (token.type() == TokenType::NUMBER) {
            out << " " << std::setprecision(12) << token.value();
        }

        out << "\n";
    }

    return out;
}