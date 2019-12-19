#!/bin/sh

inputs=(
"#echo hello world" 
"ls#-a" 
"ls # -lR && echo hello" 
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done
