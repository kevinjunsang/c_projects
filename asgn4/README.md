# Assignment 4 - The Game of Life

## Short Description

Simulate the game of life as it was created by John Conway.

## Build
Building the life program manually
```
$clang -o life life.c -lncurses
```
Also need to link the header files
```
$clang -o life life.c universe.o -lncurses
```
Need to build the header files that link to the main file
```
universe: universe.o
	$clang -o universe universe.o

universe.o: universe.c
	$clang -Wall -Wpedantic -Werror -Wextra -c universe.c
```
We can compile alternatively with the Makefile itself
```
$make all
$make
$make life
```
These three commands are equivalent and build the life program and the universe program

## Running
To run the sorting program
```
./life
```

## Command Line Options
```
[tsn:i:o:]
-t                      sets Universe to toroidal
-s                      silences ncurses
-n                      sets number of generations, default number is 100
-i                      sets input file, default is stdin
-o                      sets output file, dfault is stdout

## Cleaning
```
$make clean
```
.
