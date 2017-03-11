#include "parser.h"

#include "evaluation_exception.h"
#include "tokenizer.h"

#include <stack>

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
                if ((top.is_left_associative() && top.precedence() <= token.precedence()) ||
                    (!top.is_left_associative() && top.precedence() < token.precedence())) {
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

std::ostream& operator<<(std::ostream& out, const Parser& parser)
{
    out << "Parser: total " << parser.parsed_tokens_.size() << " tokens\n";
    for (const auto& token : parser.parsed_tokens_) {
        out << "  " << token << "\n";
    }

    return out;
}