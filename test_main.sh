#! /usr/bin/bash

exec="./miniRT"

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
    echo -e "test case:" $test_case "\n>>>"
    $exec $test_case
}

rm -f $exec

if make; then
    test_case demo/scene1.rt
else
    echo "$exec compile failed"
fi
