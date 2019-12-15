#!/bin/bash

INPUTS=("exit"
        "echo \"hello there\"; exit"
        "ls; ls -la; exit"
        "ls -la; echo hello && w; exit"
        "echo goodbye && exit")

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
