#!/bin/bash
test_count=0

# Function to run a test case
run_test() {
    local case_title="$1"
    local input="$2"
    local expected_output="$3"
    
    # Run the test case
    actual_output=$($binaries <<EOF
$input
EOF
)
    
    # Compare actual and expected outputs
    diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
    exit_status=$?
    
    # Display test result
    test_count=$((test_count + 1))
    echo "Test Case #$test_count: $case_title: $exit_status"
    if [ $exit_status -eq 0 ]; then
        echo "Test Passed: Actual and expected outputs match."
    else
        echo "Test Failed: Actual and expected outputs do not match."
        echo "Actual output:"
        echo "$actual_output"
        echo "Differences:"
        echo "$diff_output"
    fi
    echo ""
}

# Main script

# Check if argument provided
if [ $# -eq 0 ]; then
    echo "Error: No argument provided."
    echo "Usage: $0 <language: c++, or rust>"
    echo "Example: \"./tester.sh rust\""
    exit 1
fi
if [ "$1" != "c++" ] && [ "$1" != "rust" ]; then
    echo "Error: Invalid argument provided."
    echo "Usage: $0 <language: c++, or rust>"
    echo "Example: \"./tester.sh c++\""
    exit 1
fi
if [ "$1" == "c++" ]; then
    # Compile the C++ program
    clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 hello.cpp -o hello_program
    binaries="./hello_program"
fi
if [ "$1" == "rust" ]; then
    # Build the Rust program using Cargo
    cargo build --quiet
    binaries="cargo run --quiet"
fi

# Test cases
run_test "Testing 'hi'" \
"hi
exit" \
"--> Hello!
--> "
run_test "Testing multiple greetings to the same user" \
"hello John
hello John
hello John
hello John
hello John
exit" \
"--> Welcome, John!
--> Hello again(x2), John!
--> Hello again(x3), John!
--> Hello again(x4), John!
--> Hello again(x5), John!
--> "
run_test "Testing user history deletion" \
"John delete
hello John
hello John
John delete
hello John
exit" \
"--> No history found for John.
--> Welcome, John!
--> Hello again(x2), John!
--> History for John was deleted.
--> Welcome, John!
--> "
run_test "Testing secret word handling" \
"hello Jane
hello Jane
hello bread
hello John
hello Jane
exit" \
"--> Welcome, Jane!
--> Hello again(x2), Jane!
--> Secret word was entered. Clearing all the history...
--> Welcome, John!
--> Welcome, Jane!
--> "
run_test "Testing greetings to multiple users" \
"hello Alice
hello Alice
hello Alice
hello Bob
hello Bob
hello Alice
hello Bob
exit" \
"--> Welcome, Alice!
--> Hello again(x2), Alice!
--> Hello again(x3), Alice!
--> Welcome, Bob!
--> Hello again(x2), Bob!
--> Hello again(x4), Alice!
--> Hello again(x3), Bob!
--> "
run_test "Testing user deletion and secret word" \
"hello Mary
hello Mary
hello Mary
Mary delete
hello Mary
hello Mary
Mary delete
hello bread
exit" \
"--> Welcome, Mary!
--> Hello again(x2), Mary!
--> Hello again(x3), Mary!
--> History for Mary was deleted.
--> Welcome, Mary!
--> Hello again(x2), Mary!
--> History for Mary was deleted.
--> Secret word was entered. Clearing all the history...
--> "
run_test "Testing user deletion and secret word" \
"hello Peter
hello Peter
hello Peter
hello bread
hello Peter
hello Peter
Peter delete
hello Peter
exit" \
"--> Welcome, Peter!
--> Hello again(x2), Peter!
--> Hello again(x3), Peter!
--> Secret word was entered. Clearing all the history...
--> Welcome, Peter!
--> Hello again(x2), Peter!
--> History for Peter was deleted.
--> Welcome, Peter!
--> "
run_test "Testing multiple word usernames" \
"hello John Smith
hello John Smith
hello John Smith
hello Alice Cooper
hello Alice Cooper
hello Alice Cooper
exit" \
"--> Welcome, John Smith!
--> Hello again(x2), John Smith!
--> Hello again(x3), John Smith!
--> Welcome, Alice Cooper!
--> Hello again(x2), Alice Cooper!
--> Hello again(x3), Alice Cooper!
--> "
run_test "Testing invalid commands" \
"xyz
John
hello John delete
helloJohn
hello
hello 
exit" \
"--> Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").
--> Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").
--> Welcome, John delete!
--> Hello!
--> Hello!
--> Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").
--> "
