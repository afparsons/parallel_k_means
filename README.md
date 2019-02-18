# Parallel K Means

An implementation of K-Means and TF-IDF in C++.
Parallelized using _____. 

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)

## Installation

Download to your project directory and compile.

`g++ -fopenmp kmeans.cpp -o kmeans`

## Usage

`./kmeans 0 0 4 50`

First param: number of points to generate. Only used for random point generation.
Second param: number of attributes for each point. Only used for random point generation.
Third param: `k` number of clusters
Fourth param: max iterations