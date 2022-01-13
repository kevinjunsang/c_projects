# Assginment 1 - Getting Acquainted with UNIX and C

## Short Description
Program a shell script in bash to create three graphs to represent the collatz series.

## Build
Building the collatz program manually
```
$ clang -Wall -Werror -Wextra -Wpedantic -o collatz collatz.c
```

Building with given Makefile in resources/asgn1
```
$ make collatz
```

## Running
To run the collatz program in the shell after we made the file
```
./collatz
```

To run the script
```
./plot.sh
```

## Cleaning
Cleaning manually
```
$ rm -f collatz *.o
```

## Errors
In order to match the example graphs exactly, outliers are not shown in both the max and histogram graphs.
We needed to set maxes on the axis in order to create a pleasant graphs, leading to a loss of some data.

