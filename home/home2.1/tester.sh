#!/bin/bash

# check if argument provided
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

# Test Case 0: Testing "hi"
echo "Test Case 0: Testing 'hi'"
actual_output=$($binaries <<EOF
hi
exit
EOF
)

expected_output="--> Hello!
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 1: Testing multiple greetings to the same user
echo "Test Case 1: Testing multiple greetings to the same user"
actual_output=$($binaries <<EOF
hello John
hello John
hello John
hello John
hello John
exit
EOF
)

expected_output="--> Welcome, John!
--> Hello again(x2), John!
--> Hello again(x3), John!
--> Hello again(x4), John!
--> Hello again(x5), John!
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 2: Testing user history deletion
echo "Test Case 2: Testing user history deletion"
actual_output=$($binaries <<EOF
John delete
hello John
hello John
John delete
hello John
exit
EOF
)

expected_output="--> No history found for John.
--> Welcome, John!
--> Hello again(x2), John!
--> History for John was deleted.
--> Welcome, John!
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 3: Testing secret word handling
echo "Test Case 3: Testing secret word handling"
actual_output=$($binaries <<EOF
hello Jane
hello Jane
hello bread
hello John
hello Jane
exit
EOF
)

expected_output="--> Welcome, Jane!
--> Hello again(x2), Jane!
--> Secret word was entered. Clearing all the history...
--> Welcome, John!
--> Welcome, Jane!
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 4: Testing greetings to multiple users
echo "Test Case 4: Testing greetings to multiple users"
actual_output=$($binaries <<EOF
hello Alice
hello Alice
hello Alice
hello Bob
hello Bob
hello Alice
hello Bob
exit
EOF
)

expected_output="--> Welcome, Alice!
--> Hello again(x2), Alice!
--> Hello again(x3), Alice!
--> Welcome, Bob!
--> Hello again(x2), Bob!
--> Hello again(x4), Alice!
--> Hello again(x3), Bob!
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 5: Testing user deletion and secret word
echo "Test Case 5: Testing user deletion and secret word"
actual_output=$($binaries <<EOF
hello Mary
hello Mary
hello Mary
Mary delete
hello Mary
hello Mary
Mary delete
hello bread
exit
EOF
)

expected_output="--> Welcome, Mary!
--> Hello again(x2), Mary!
--> Hello again(x3), Mary!
--> History for Mary was deleted.
--> Welcome, Mary!
--> Hello again(x2), Mary!
--> History for Mary was deleted.
--> Secret word was entered. Clearing all the history...
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 6: Testing user deletion and secret word
echo "Test Case 6: Testing user deletion and secret word"
actual_output=$($binaries <<EOF
hello Peter
hello Peter
hello Peter
hello bread
hello Peter
hello Peter
Peter delete
hello Peter
exit
EOF
)

expected_output="--> Welcome, Peter!
--> Hello again(x2), Peter!
--> Hello again(x3), Peter!
--> Secret word was entered. Clearing all the history...
--> Welcome, Peter!
--> Hello again(x2), Peter!
--> History for Peter was deleted.
--> Welcome, Peter!
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 7: Testing multiple word usernames
echo "Test Case 7: Testing multiple word usernames"
actual_output=$($binaries <<EOF
hello John Smith
hello John Smith
hello John Smith
hello Alice Cooper
hello Alice Cooper
hello Alice Cooper
exit
EOF
)

expected_output="--> Welcome, John Smith!
--> Hello again(x2), John Smith!
--> Hello again(x3), John Smith!
--> Welcome, Alice Cooper!
--> Hello again(x2), Alice Cooper!
--> Hello again(x3), Alice Cooper!
--> "
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi
echo ""

# Test Case 8: Testing invalid commands
echo "Test Case 8: Testing invalid commands"
actual_output=$($binaries <<EOF
xyz
John
hello John delete
helloJohn

hello
hello 
exit
EOF
)

expected_output="--> Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").
--> Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").
--> Welcome, John delete!
--> Hello!
--> Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").
--> Hello!
--> Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").
--> 
"
diff_output=$(diff -Z <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
exit_status=$?
if [ $exit_status -eq 0 ]; then
    echo "Test Passed: Output matches the expected output."
else
    echo "Test Failed: Output does not match the expected output."
    echo "Actual output:"
    echo "$actual_output"
    echo "Differences:"
    echo "$diff_output"
fi

if [ "$1" == "c++" ]; then
    echo ""
    # Clean up
    rm hello_program
fi

# Exit with the appropriate status
exit $exit_status
