#!/bin/bash

clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 "$1" -o "$2"

# for testing purposes:
# ./../../home/home2.1/tester.sh