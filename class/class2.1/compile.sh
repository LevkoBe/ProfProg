#!/bin/bash

clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 "$@"
# Example:
# ./compile.sh input1.cpp input2.cpp -o output -I/path/to/include -DDEBUG

# for testing purposes:
# ./../../home/home2.1/tester.sh c++