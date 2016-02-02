#!/bin/bash

make

for f in *.cc
do
    f="${f%.*}"
    echo "#####"
    echo "running "$f
    ./$f
done