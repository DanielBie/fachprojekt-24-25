# Fachprojekt Scientific Computing 24/25

This repository contains the micro benchmarks for the Fachprojekt Scientific Computing. The goal is to find one or multiple bottlenecks in performance for each of the benchmarks and try to rewrite the code in a way which increases performance.

## How to build and run a benchmark

The `run.sh` script is used to both build and run. The first argument to the script should always be the name of the folder of the benchmark. E.g. if the benchmark `initial` should be used, the call is 
```console
./run.sh initial
```
To build the benchmark the flag `-build` is used. An additional flag `-clean` can be used to first clean the build folder and rebuild everything. This can be a useful first step in debugging. E.g. when building `initial` without a clean build the call would be
```console
./run.sh initial -build
```

To run a benchmark the flag `-run` is used. Per default the results printed to the terminal. If the results should instead be stored in a `result.csv` file in the benchmark folder, the flag `-store` can be used. All flags can be combined. E.g. first clean building and then running the benchmark without storing to the file, the call is
```console
./run.sh initial -build -clean -run 
```
The order of the flags is irrelevant, but the benchmark folder has to be the first argument to give.
