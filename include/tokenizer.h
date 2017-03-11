#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "token.h"

#include <string>
#include <vector>

class Tokenizer {
public:
    friend std::ostream& operator<<(std::ostream& out, const Tokenizer& tokenizer);

public:
    explicit Tokenizer(const std::string& input);
    const std::vector<Token>& tokens() const;

private:
    std::vector<Token> tokens_;

    std::size_t read_number(const std::string& input, std::size_t idx);
};


#endif // TOKENIZER_H_