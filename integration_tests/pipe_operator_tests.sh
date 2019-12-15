#!/bin/bash

CORRECT_INPUTS=(" ls -la | more; exit" "echo hello > output.txt; exit" "cat output.txt | grep \"hello\"; exit" "rm output.txt; exit")

for corr_input in "${CORRECT_INPUTS[@]}"
do
    echo "../rshell ${corr_input}"
    output=$(../rshell ${corr_input})
    if [ "${output}" != "" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
