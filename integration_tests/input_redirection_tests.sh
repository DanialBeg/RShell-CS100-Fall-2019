#!/bin/bash

CORRECT_INPUTS=("echo \"hello there\" > output.txt; exit" "cat < output.txt; exit" "rm output.txt; exit")

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
