#!/bin/sh

inputs=(
"ls | cut -b 1-5"
"cat new.txt | false && echo hello everyone"
"(date | wc && echo hi) || exit && exit"
"(date | wc && echo hi || exit) && exit"
"ls | false || echo \"when last term is false, exit value is false\" "
"ls | exit && echo \"when last term is exit, exit value of pipe true, shell does not exit\" "
"false | ls -a && echo \"when last term is not false, exit value is true\" "
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done