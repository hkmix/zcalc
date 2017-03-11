#ifndef EVALUATION_EXCEPTION_H_
#define EVALUATION_EXCEPTION_H_

#include <string>

class Expression;

class EvaluationException {
public:
    static const std::string INVALID_EXPRESSION;
    static const std::string DIVIDE_BY_ZERO;
    static const std::string INVALID_EXPONENTIATION;
    static const std::string MISMATCHED_PARENS;
    static const std::string NOT_ENOUGH_NUMBERS;
    static const std::string TOO_MANY_NUMBERS;
    static const std::string UNIMPLEMENTED;

public:
    EvaluationException();
    explicit EvaluationException(const std::string& message);

    const std::string& message() const;

private:
    const std::string message_;
};

#endif // EVALUATION_EXCEPTION_H_