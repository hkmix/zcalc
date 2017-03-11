#include "parser.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    const std::string input{"123.45 + 12.44 - 12_000_002.173_001 / 0.15 * .189 - .0 ** 0"};

    std::cout << "Parsing: " << input << "\n";

    Parser parser{input};

    std::cout << parser;

    return 0;
}