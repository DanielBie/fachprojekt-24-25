#!/bin/bash

cd $1

mkdir -p build
cd build
cmake ..
make
