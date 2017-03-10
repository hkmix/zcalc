#include "tokenizer.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    const std::string input{"123.456781 12.44 12 0.15 .189 .0 0"};

    Tokenizer tokenizer;
    tokenizer.tokenize(input);

    std::cout << tokenizer;

    return 0;
}