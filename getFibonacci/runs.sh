#!/bin/sh

read -p "Enter you OpenMP program filename (without extension): " filename

clang -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp "$filename.c" -o "$filename"
echo "1thExec, 2thExec, 3rdExec, 4thExec, 5thExec" >> data-$filename.csv

for i in {1..8}; do
    for j in {1..5}; do
        time=$(./"$filename" $i)
        if [ $j -eq 5 ]; then end=""
        else end=", "; fi
        printf "$time$end" >> dataTest-$filename.csv
    done
    printf "\n" >> data-$filename.csv
done
