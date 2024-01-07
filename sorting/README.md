# Sorting: Putting your affairs in order

## Short Description
Perform four different sorting algorithms. Run sorting algorithms and view number of comparisons and moves

## Build
Building the sorting porgram manually
```
$clang -Wall -Wpedantic -Werror -Wextra -c sorting.c
```
Also need to link the header files
```
$clang -o sorting sorting.o batcher.o heap.o quick.o insert.o stats.o
```
Need to build the header files that link to the main file
```
file: file.o stats.o
    $clang -o file file.o stats.o

file.o: file.c stats.h
    $clang -Wall -Wpedantic -Werror -Wextra -c file.c
```
Need to do this for all four sorting algorithms and make the stats

We can easily build everything with the Makefile I made
```
$make all
$make 
$make sorting
```
These three commands are equivalent and build the sorting program and all sorting algorithms

## Running
To run the sorting program
```
./sorting
```

## Command Line Options
```
[ahbiqr:n:p:H:]
-a                 runs all sorting algorithms
-h                 runs heap sort
-b                 runs batcher sort
-i                 runs insertion sort
-q                 runs quick sort
-r                 sets SEED, default seed is 13371453
-n                 sets size, default size is 100
-p                 sets elements, default elements is 100
-H                 Prints out program usage 
```

## Cleaning
```
$make clean
```
cleans .o files, part of my Makefile

## Errors
No known erros


