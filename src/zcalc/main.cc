#include "tokenizer.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    const std::string input{"123.456781 + 12.44 - 12_000_002.173_001 / 0.15 * .189 - .0 ** 0"};

    std::cout << "Tokenizing: " << input << "\n";

    Tokenizer tokenizer;
    tokenizer.tokenize(input);

    std::cout << tokenizer;

    return 0;
}