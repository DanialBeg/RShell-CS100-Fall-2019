#!/bin/bash

CORRECT_INPUTS=("test -e main.cpp; exit" "test -f rshell.cpp; exit" "test -d command.hpp; exit" "test and.cpp; exit")
INCORRECT_INPUTS=("test -e marn.cpp || echo failure; exit" "test -f rshall.cpp || echo failure; exit" "test -d comm || echo failure; exit")

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

for incorr_input in "${INCORRECT_INPUTS[@]}"
do
    echo "../rshell ${incorr_input}"
    output=$(../rshell ${incorr_input})
    if [ "${output}" != "" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
