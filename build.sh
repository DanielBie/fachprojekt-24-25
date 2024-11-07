#!/bin/bash

cd $1


if [[ "$*" == *"-clean" ]]; then
    rm -r build
fi

mkdir -p build
cd build
cmake ..
make
