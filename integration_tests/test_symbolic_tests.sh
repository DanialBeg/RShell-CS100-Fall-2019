#!/bin/bash
CORRECT_INPUTS=("[-e single_command_tests.sh] && echo success; exit" "[ -f rshell.cpp ] && echo success; exit" "[-d ../src] && echo success; exit" "[and.cpp] && echo success; exit")
INCORRECT_INPUTS=("[-e ls] || echo failure; exit" " [-f rand.cpp] || echo failure; exit" "[-d trash] || echo failure; exit" "[rand] || echo failure; exit")

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
