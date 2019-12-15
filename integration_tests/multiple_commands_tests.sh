# !/bin/bash

INPUTS=("echp hello && ls -la; exit"
        "echo \"hello there\"; echo \"food\" || echo food; exit"
        "ls || echo food; echo bin1/ && echo \"echoed bin\"; exit"
        "ls -la && ls; echo \"will this fail?\" || echo \"no\"; exit"
        "ls; w; ls && echo \"list\"; exit")

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
