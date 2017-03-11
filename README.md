# zcalc

**WORK IN-PROGRESS**, incomplete

A simple calculator to practice using CMake and parsing/handling input.

## Available operations

- Add, subtract, multiply, divide
- Exponentiation
- Parentheses

## Instructions

1. Create subdirectories

        / $ mkdir build

1. Generate desired make files (use `-G` to specify build engine) and build

        / $ cd build
        /build $ cmake ..
        /build $ make

1. Execute

        /build $ cd ../bin
        /bin $ ./zcalc