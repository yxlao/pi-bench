#!/bin/bash

make
make clean_txt

for f in *.cc
do
    f="${f%.*}"
    echo "#####"
    echo "running "$f
    for i in {1..100}
    do
        # ./$f | tee -a $f".txt"
        ./$f >> $f".txt"
    done
done