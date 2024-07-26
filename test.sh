#! /usr/bin/bash

exec="./read_file_test"

print_return_value() {
    if [ $1 -eq 0 ]; then
        echo -e "\033[1;32m[$1]\033[1;0m" # Green for success
    else
        echo -e "\033[1;31m[$1]\033[1;0m" # Red for failure
    fi
    echo
}

test_case() {
    test_case=$1
    echo -n -e $test_case ">>> "
    $exec $test_case
    print_return_value $?
}

echo without arguments ">>>"
$exec
print_return_value $?

test_case "1"
test_case "1 2"
test_case "."
test_case ".."
test_case "..."
test_case "...."
test_case "....."
test_case "......"
test_case "......."