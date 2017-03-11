# zcalc

**WORK IN-PROGRESS**, incomplete

A simple calculator to practice using CMake and parsing/handling input.

## Available operations

- Add, subtract/negation, multiply, divide
- Exponentiation
- Parentheses

## Next steps

- Add more functionality (functions, operators)
- Add ability to input binary/hex/oct
- Add variables and last evaluation variable

## Instructions

1. Create subdirectories

        / $ mkdir build

1. Generate desired make files (use `-G` to specify build engine) and build

        / $ cd build
        /build $ cmake ..
        /build $ make

1. Execute (optionally, add `-v` or `--verbose` to show tokenizer and parser output)

        /build $ cd ../bin
        /bin $ ./zcalc "some expression here"