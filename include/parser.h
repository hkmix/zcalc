#ifndef PARSER_H_
#define PARSER_H_

#include "token.h"
#include "tokenizer.h"

#include <vector>

class Parser {
public:
    friend std::ostream& operator<<(std::ostream& out, const Parser& parser);

public:
    explicit Parser(const std::string& input);

    value_t evaluate() const;

private:
    Tokenizer tokenizer_;
    std::vector<Token> parsed_tokens_;
};

#endif // PARSER_H_