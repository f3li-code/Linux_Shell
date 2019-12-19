#!/bin/sh

inputs=(
"echo hello world > new.txt"
"date > new.txt"
"echo 1 >> new.txt"
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done