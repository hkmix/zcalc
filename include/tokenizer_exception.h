#ifndef TOKENIZER_EXCEPTION_H_
#define TOKENIZER_EXCEPTION_H_

#include <string>

class TokenizerException {
public:
    static const std::string UNEXPECTED_TOKEN;
    static const std::string INVALID_NUMBER;

public:
    explicit TokenizerException(const std::string& message, std::size_t column);

    const std::string message() const;
    std::size_t column() const;

private:
    const std::string message_;
    const std::size_t column_;
};

#endif // TOKENIZER_EXCEPTION_H_