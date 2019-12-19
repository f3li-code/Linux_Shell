#!/bin/sh

inputs=(
"test []"
"test -e .gitignore"
"test -f .gitignore"
"test -d .gitignore"
"test -d header/classes"
"test -f ../header/classes/amp.hpp"
"test"
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done
