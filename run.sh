#!/bin/bash

build () {
    cd $1


    if [[ "$*" == *"-clean" ]]; then
        rm -r build
    fi

    mkdir -p build
    cd build
    cmake ..
    make
    cd ../..
}

run () {
    cd $1/build/

    if [[ "$*" == *"-store" ]]; then
        ./$1 > ../results.csv
    else
        ./$1
    fi
    cd ../..
}



build_flag=false
run_flag=false
clean_flag=false
store_flag=false

for arg in "$@"; do
    case $arg in
        -build) build_flag=true ;;
        -run) run_flag=true ;;
        -clean) clean_flag=true ;;
        -store) store_flag=true ;;
    esac
done

if $build_flag; then
    if $clean_flag; then
        build "$@" -clean
    else
        build "$@"
    fi
fi

if $run_flag; then
    if $store_flag; then
        run "$@" -store
    else
        run "$@"
    fi
fi
