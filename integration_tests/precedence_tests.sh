#!/bin/bash

INPUTS=("(echo hello); exit" "(echo hello && echo bye); exit" "echp hello || (echo good && echo bye); exit" "(echo A && echo B) || (echo C && echo D); exit")

for input in "${INPUTS[@]}"
do
    echo "../rshell ${input}"
    output=$(../rshell ${input})
    if [ "${output}" != "" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
