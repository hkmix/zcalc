#include "parser.h"

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char** argv)
{
    const std::string exec_name = std::string{argv[0]};
    if (argc < 2) {
        std::cout << "Usage: " << exec_name << " <expression>\n";

        return 0;
    }

    std::stringstream ss;
    for (auto idx = 1; idx < argc; ++idx) {
        ss << argv[idx] << " ";
    }

    Parser parser{ss.str()};
    std::cout << parser.evaluate() << "\n";

    return 0;
}