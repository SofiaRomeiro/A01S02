#!/bin/sh

for input in ./tests/*.in
do
    output="results/"
    output+=$(basename "$input")
    output+=".out"
    echo "============================="
    echo "$input"
    echo "_"
    ./Kanban < "$input" > "$output"
    echo "............................."
done