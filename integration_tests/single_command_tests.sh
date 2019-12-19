#!/bin/sh

inputs=(
    "ls" 
    "ls -a" 
    "git status" 
    "echo \"hello && world\"" 
)

echo "SINGLE COMMAND TESTS..."

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done


