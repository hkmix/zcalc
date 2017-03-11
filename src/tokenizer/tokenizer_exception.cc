#include "tokenizer_exception.h"

const std::string TokenizerException::UNEXPECTED_TOKEN{"Unexpected token."};
const std::string TokenizerException::INVALID_NUMBER{"Invalid number specified."};

TokenizerException::TokenizerException(const std::string& message, std::size_t column)
    : message_{message}
    , column_{column}
{
}

const std::string TokenizerException::message() const
{
    return "col " + std::to_string(column_) + ": " + message_;
}

std::size_t TokenizerException::column() const
{
    return column_;
}