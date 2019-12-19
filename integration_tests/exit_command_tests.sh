#!/bin/sh

inputs=(
"exit" 
"echo hello && exit" 
"false && exit" 
"ls || exit" 
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done


