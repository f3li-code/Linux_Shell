#!/bin/sh

inputs=(
"[ [] ]"
"[ -e .gitignore ]"
"[ -f .gitignore ]"
"[ -d .gitignore ]"
"[ -d header/classes ]"
"[ -f ../header/classes/amp.hpp ]"
"[ ]"
"[]"
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done
