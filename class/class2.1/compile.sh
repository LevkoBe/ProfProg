#!/bin/bash

# It is better to pass $@ to clang++ to make script more useful for further tasks as at the moment you have only 2 arguments for input file and output
# but for some cases we will need more input files and some extra flags.
clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 "$1" -o "$2"

# for testing purposes:
# ./../../home/home2.1/tester.sh c++