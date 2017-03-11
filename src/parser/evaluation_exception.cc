#include "evaluation_exception.h"

#include <sstream>

const std::string EvaluationException::INVALID_EXPRESSION{"Invalid expression"};
const std::string EvaluationException::DIVIDE_BY_ZERO{"Division by zero"};
const std::string EvaluationException::INVALID_EXPONENTIATION{"Invalid exponentiation"};
const std::string EvaluationException::MISMATCHED_PARENS{"Mismatched parentheses"};
const std::string EvaluationException::NOT_ENOUGH_NUMBERS{"Not enough numbers given"};
const std::string EvaluationException::UNIMPLEMENTED{"Unimplemented call used"};

EvaluationException::EvaluationException()
    : EvaluationException{EvaluationException::INVALID_EXPRESSION}
{
}

EvaluationException::EvaluationException(const std::string& message)
    : message_{message}
{
}


const std::string& EvaluationException::message() const
{
    return message_;
}