#include "tokenizer.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    const std::string input{"123.456781 12.44 12 0.15 .189 .0 0"};

    Tokenizer tokenizer;
    tokenizer.tokenize(input);

    std::cout << "found " << tokenizer.tokens().size() << " tokens\n";

    for (std::size_t idx = 0; idx < tokenizer.tokens().size(); ++idx) {
        std::cout << "token " << idx << ": " << tokenizer.tokens()[idx].value() << "\n";
    }

    return 0;
}