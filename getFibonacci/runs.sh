#!/bin/sh

echo "Enter you OpenMP program filename (without extension): "
read filename

for i in $(seq 1 8);
do
    echo "THREAD NUMBER: $i"
    for j in $(seq 1 5);
    do
    clang -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp "$filename.c" -o "$filename"
    ./"$filename" $i
    done
done
