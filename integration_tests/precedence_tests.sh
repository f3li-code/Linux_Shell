#!/bin/sh

inputs=(
"(echo A || (false ; echo B))"
"(false ; (echo A  || echo B))"
"(true && (echo A || echo B))"
"([ blab ] || ((echo A) ; echo B))"
"([ -d ../cmake-build-debug ] || ((echo A) ; echo B))"
"([ -f ../cmake-build-debug ] || ((echo A) ; echo B))"
)

for input in "${inputs[@]}"
do
    echo ${input}
    ../src/integ ${input}
done
