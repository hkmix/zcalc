#include "parser.h"

#include "evaluation_exception.h"
#include "tokenizer.h"

#include <cmath>
#include <stack>
#include <utility>

// Helper functions
namespace
{

std::pair<double, double> top_two(std::stack<double>& stack)
{
    // Element on the right is on the top of the stack
    const auto& right = stack.top();
    stack.pop();

    const auto& left = stack.top();
    stack.pop();

    return std::make_pair(left, right);
}

} // namespace

Parser::Parser(const std::string& input)
{
    Tokenizer tokenizer{input};

    parsed_tokens_.clear();

    // Shunting-yard algorithm
    std::stack<Token> operators;
    for (const auto& token : tokenizer.tokens()) {
        if (token.type() == TokenType::NUMBER) {
            parsed_tokens_.push_back(token);
        }
        else if (token.type() == TokenType::LEFT_PARENS) {
            // Left parens, just push it onto the stack
            operators.push(token);
        }
        else if (token.type() == TokenType::RIGHT_PARENS) {
            // Right parens, pop until left parens or empty
            while (!operators.empty() && operators.top() != Token::LEFT_PARENS) {
                const auto& top = operators.top();
                parsed_tokens_.push_back(top);
                operators.pop();
            }

            // Second condition should never occur, but is here as a sanity check
            if (operators.empty() || operators.top() != Token::LEFT_PARENS) {
                throw EvaluationException{EvaluationException::MISMATCHED_PARENS};
            }

            // Remove the right parens
            operators.pop();
        }
        else if (operators.empty()) {
            // Operator type with no operators, push onto stack
            operators.push(token);
        } else {
            // Operator type, check associativity and precedence
            while (true) {
                if (operators.empty()) {
                    break;
                }

                const auto& top = operators.top();
                if ((top.is_left_associative() && top.precedence() >= token.precedence()) ||
                    (!top.is_left_associative() && top.precedence() > token.precedence())) {
                    parsed_tokens_.push_back(top);
                    operators.pop();
                }
                else {
                    break;
                }
            }

            operators.push(token);
        }
    }

    // Done, push the rest of the operators back
    while (!operators.empty()) {
        const auto& top = operators.top();

        // Verify no mismatched parens
        if (top == Token::LEFT_PARENS || top == Token::RIGHT_PARENS) {
            throw EvaluationException{EvaluationException::MISMATCHED_PARENS};
        }

        parsed_tokens_.push_back(top);
        operators.pop();
    }
}

double Parser::evaluate() const
{
    std::stack<double> values;

    for (const auto& token : parsed_tokens_) {
        switch (token.type()) {
        case TokenType::NUMBER:
            // Number, push it
            values.push(token.value());
            break;

        case TokenType::ADD:
            // If we have two on the stack, add them, else assume unary and do nothing
            if (values.size() == 0) {
                throw EvaluationException{EvaluationException::NOT_ENOUGH_NUMBERS};
            }
            else if (values.size() >= 2) {
                auto pair = top_two(values);
                values.push(pair.first + pair.second);
            }
            break;

        case TokenType::SUBTRACT:
            // If we have two on the stack, subtract them, else assume unary and negate
            if (values.size() == 0) {
                throw EvaluationException{EvaluationException::NOT_ENOUGH_NUMBERS};
            }
            else if (values.size() == 1) {
                const auto& top = values.top();
                values.pop();
                values.push(-top);
            }
            else if (values.size() >= 2) {
                auto pair = top_two(values);
                values.push(pair.first - pair.second);
            }
            break;

        case TokenType::MULTIPLY:
            // If we have two on the stack, multiply them
            if (values.size() >= 2) {
                auto pair = top_two(values);
                values.push(pair.first * pair.second);
            }
            else {
                throw EvaluationException{EvaluationException::NOT_ENOUGH_NUMBERS};
            }
            break;

        case TokenType::DIVIDE:
            // If we have two on the stack, divide them
            if (values.size() >= 2) {
                auto pair = top_two(values);

                if (pair.second == 0.0) {
                    throw EvaluationException{EvaluationException::DIVIDE_BY_ZERO};
                }

                values.push(pair.first / pair.second);
            }
            else {
                throw EvaluationException{EvaluationException::NOT_ENOUGH_NUMBERS};
            }
            break;

        case TokenType::EXPONENT:
            // If we have two on the stack, take the exponentiation
            if (values.size() >= 2) {
                auto pair = top_two(values);
                try {
                    values.push(std::pow(pair.first, pair.second));
                } catch (...) {
                    // HACK: Horrible practice catching this way
                    throw EvaluationException{EvaluationException::INVALID_EXPONENTIATION};
                }
            }
            else {
                throw EvaluationException{EvaluationException::NOT_ENOUGH_NUMBERS};
            }
            break;

        default:
            // Should never get here
            throw EvaluationException{EvaluationException::UNIMPLEMENTED};
        }
    }

    // At the end, if there is more than one number, assume they are to be
    // multiplied to enable bracketed multiplications
    while (values.size() > 1) {
        const auto pair = top_two(values);
        values.push(pair.first * pair.second);
    }

    // Sanity check; should never reach here
    if (values.empty()) {
        throw EvaluationException{EvaluationException::NOT_ENOUGH_NUMBERS};
    }

    return values.top();
}

std::ostream& operator<<(std::ostream& out, const Parser& parser)
{
    out << "Parser: total " << parser.parsed_tokens_.size() << " tokens\n";
    for (const auto& token : parser.parsed_tokens_) {
        out << "  " << token << "\n";
    }

    return out;
}