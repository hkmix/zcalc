#ifndef PARSER_H_
#define PARSER_H_

#include "token.h"

#include <vector>

class Parser {
public:
    friend std::ostream& operator<<(std::ostream& out, const Parser& parser);

public:
    explicit Parser(const std::string& input);

    double evaluate() const;

private:
    std::vector<Token> parsed_tokens_;
};

#endif // PARSER_H_