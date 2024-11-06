#!/bin/bash

cd $1/build

if [ $2 = "store" ]; then
    ./$1 > ../results.csv
else
    ./$1
fi