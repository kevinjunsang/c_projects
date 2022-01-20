# Assignment 2 - Numerical Integration

## Short Description
Perform numerical integration for 10 given functions.
Create our own math library containing 5 distinct math operations.

## Build
Building the integrate program manually
'''
$clang -Wall -Wextra -Wpedantic -Wextra -c integrate.c 
'''
You also need to build the header programs
'''
$clang -Wall -Wextra -Wpedantic -Wextra -c functions.c
$clang -Wall -Wextra -Wpedantic -Wextra -c mathlib.c
'''
Finally you have to link the header files with integrate
'''
clang -o integrate integrate.o functions.o mathlib.o
'''

Building with Makefile that we created
'''
$make all
$make
$make integrate
'''
All of these work in building integrate, all of the header files and linking

## Running
To run the integrate program
'''
./integrate
'''

### Command Line Options
[abcdefghij] choose functions
 -a                sqrt(1 - x^4)
 -b                1/log(x)
 -c                exp(-x^2)
 -d                sin(x^2)
 -e                cos(x^2)
 -f                log(log(x))
 -g                sin(x)/x
 -h                exp(-x)/x
 -i                exp(exp(x))
 -j                sqrt(sin^2(x) + cos^2(x))

[n:p:q:] choose bounds and partition count
 -n partitions     Sets Maximum number of partitions
 -p low            Sets lower bound of integral interval
 -q high           Sets higher end of integral interval

[H] Displays synopsis and usage
 -H                Display protram synopsis and usage

## Cleaning
'''
$make clean
'''
Inside of my Makefile

## Errors
No known errors
