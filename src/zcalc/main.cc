#include "parser.h"
#include "evaluation_exception.h"
#include "tokenizer_exception.h"

#include <bitset>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace
{

const std::string binary_string(int_value_t value)
{
    std::bitset<sizeof(int_value_t) * CHAR_BIT> bits{static_cast<uint_value_t>(value)};

    if (value < 0) {
        std::stringstream ss;
        ss << bits;
        return ss.str();
    }
    else if (value == 0) {
        return "0";
    }
    else {
        std::stringstream ss;
        ss << bits;
        auto bit_string = ss.str();

        const auto first_idx = bit_string.find_first_of('1');

        return bit_string.substr(first_idx);
    }
}

} // namespace

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

    try {
        value_t result = parser.evaluate();
        static constexpr auto max_precision = std::numeric_limits<value_t>::digits10 + 1;

        std::cout << std::setprecision(max_precision) << result << "\n";

        // For integral values, print bin/hex/oct
        if (std::trunc(result) == result) {
            int_value_t int_result = static_cast<int_value_t>(result);

            std::cout << "bin: " << binary_string(int_result) << "\n";
            std::cout << "hex: " << std::hex << int_result << "\n";
            std::cout << "oct: " << std::oct << int_result << "\n";
        }
    } catch (EvaluationException& ex) {
        std::cerr << ex.message() << "\n";
    } catch (TokenizerException& ex) {
        std::cerr << ex.message() << "\n";
    } catch (...) {
        std::cerr << "Encountered unknown error.\n";
    }

    return 0;
}