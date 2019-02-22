# Parallel K Means

An implementation of K-Means and TF-IDF in C++.

Parallelized using _____. 

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [To-Do](#to-do)

## Installation

Download to your project directory and compile.

`g++ -fopenmp src/kmeans.cpp -o bin/kmeans`

Might require the C++ Boost libraries to compile.

## Usage

`./kmeans 0 0 4 50`

First param: number of points to generate. Only used for random point generation.

Second param: number of attributes for each point. Only used for random point generation.

Third param: `k` number of clusters.

Fourth param: max iterations.

Note: the numbers are in colors I've not yet tested to work in a white-color terminal (like macOS's Terminal.app).

## To-Do

- [ ] Improve README.md
- [ ] Replace `sscanf` with `getopt`
- [ ] Implement document directory as runtime argument
- [ ] Clean up `vectorizer.cpp`
- [ ] Use better variable names in `vectorizer.cpp`
- [ ] Configure guards
- [ ] Optimize sequential program
- [ ] Benchmark sequential program
- [ ] Parallelize everything lol