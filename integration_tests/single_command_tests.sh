#!/bin/bash

INPUTS=("echo hello; exit" "echo \"hello there\"; exit" "ls; exit" "ls -la; exit" "mkdir bin/; exit")

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
