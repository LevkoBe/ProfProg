#!/bin/bash
test_count=0
overall_exit_status=0  # Variable to track overall exit status

# Function to run a test case
run_test() {
    local input_file="$1"
    local input_color="$2"
    local output_file="$3"
    local expected_file="$4"
    local expected_output="$5"
    
    echo "Running test with:"
    echo "  Input file: $input_file"
    echo "  Color: $input_color"
    echo "  Output file: $output_file"
    echo "  Expected file: $expected_file"
    
    # Run the test case and capture the actual output
    actual_output=$($binaries <<EOF
$input_file
$input_color
$output_file
EOF
)
    
    # Check if the output file and expected file exist
    if [ ! -f "$output_file" ]; then
        echo "Error: Output file $output_file does not exist."
        overall_exit_status=1  # Update overall exit status to indicate failure
        return 1  # Return from the function to continue executing other test cases
    fi
    if [ ! -f "$expected_file" ]; then
        echo "Error: Expected file $expected_file does not exist."
        overall_exit_status=1  # Update overall exit status to indicate failure
        return 1  # Return from the function to continue executing other test cases
    fi
    
    # Compare actual and expected outputs
    diff_file=$(diff -u <(cat "$output_file") <(cat "$expected_file"))
    exit_status_file=$?
    diff_output=$(diff -u <(echo -n -e "$expected_output") <(echo -n -e "$actual_output"))
    exit_status_output=$?

    # Display test result
    test_count=$((test_count + 1))
    echo "Test Case #$test_count:"
    echo "  Exit status for file comparison: $exit_status_file"
    echo "  Exit status for output comparison: $exit_status_output"
    
    if [ $exit_status_file -eq 0 ] && [ $exit_status_output -eq 0 ]; then
        echo "Test Passed: Actual and expected outputs match."
    else
        echo "Test Failed:"
        if [ $exit_status_file -ne 0 ]; then
            echo "File contents do not match."
            echo "Differences in file:"
            echo "$diff_file"
        fi
        if [ $exit_status_output -ne 0 ]; then
            echo "Program outputs do not match."
            echo "Expected output:"
            echo "$expected_output"
            echo "Actual output:"
            echo "$actual_output"
            echo "Differences in output:"
            echo "$diff_output"
        fi
        overall_exit_status=1  # Update overall exit status to indicate failure
    fi
    echo ""
    
    # Delete the output file
    rm -f "$output_file"
}

# Main script

# Check if argument provided
if [ $# -eq 0 ]; then
    echo "Error: No argument provided."
    echo "Usage: $0 <language: c++ or rust>"
    echo "Example: \"./testing2.2/tester.sh c++\""
    exit 1
fi
if [ "$1" != "c++" ] && [ "$1" != "rust" ]; then
    echo "Error: Invalid argument provided."
    echo "Usage: $0 <language: c++ or rust>"
    echo "Example: \"./testing2.2/tester.sh c++\""
    exit 1
fi
if [ "$1" == "c++" ]; then
    # Compile the C++ program
    clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 main.cpp -o main
    binaries="./main"
fi
if [ "$1" == "rust" ]; then
    # Build the Rust program using Cargo
    cargo build --quiet
    binaries="cargo run --quiet"
fi

# Test cases

run_test "1.txt" \
"1,7,3" \
"./testing2.2/1o.txt" \
"./testing2.2/1t.txt" \
"Error opening file 1.txt"

run_test "./testing2.2/1i.txt" \
"1,7,3" \
"./testing2.2/1o.txt" \
"./testing2.2/1t.txt" \
"Please, enter the name of the file with the image: Please, enter your favorite color (format \"0,0,0\"): Please, enter the output file name: Image saved to ./testing2.2/1o.txt"

run_test "./testing2.2/2i.txt" \
"255,34,153" \
"./testing2.2/2o.txt" \
"./testing2.2/2t.txt" \
"Please, enter the name of the file with the image: Please, enter your favorite color (format \"0,0,0\"): Please, enter the output file name: Image saved to ./testing2.2/2o.txt"

run_test "./testing2.2/3i.txt" \
"1,2,3" \
"./testing2.2/3o.txt" \
"./testing2.2/3t.txt" \
"Please, enter the name of the file with the image: Please, enter your favorite color (format \"0,0,0\"): Please, enter the output file name: Image saved to ./testing2.2/3o.txt"

run_test "./testing2.2/4i.txt" \
"128,128,128" \
"./testing2.2/4o.txt" \
"./testing2.2/4t.txt" \
"Please, enter the name of the file with the image: Please, enter your favorite color (format \"0,0,0\"): Please, enter the output file name: Image saved to ./testing2.2/4o.txt"

run_test "./testing2.2/5i.txt" \
"1,2,3" \
"./testing2.2/5o.txt" \
"./testing2.2/5t.txt" \
"Please, enter the name of the file with the image: Please, enter your favorite color (format \"0,0,0\"): Please, enter the output file name: Image saved to ./testing2.2/5o.txt"

# Exit with overall exit status
exit $overall_exit_status
