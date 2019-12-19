#!/bin/sh

inputs=(
"cat < input_redirection_tests.sh"
"echo < input_redirection_tests.sh"
"cut -b 1-5 < input_redirection_tests.sh"
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done