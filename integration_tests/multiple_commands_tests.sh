#!/bin/sh

inputs=(
"echo \"Multiple_Command_Tests.sh\" || echo \"i dont exist\""
"echo \"Multiple_Command_Tests.sh\" && echo \"i dont exist\""
"ls -a; echo hello && mkdir test || echo world; git status"
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done

