##Assignment 7 - Author Identification

#Short Description
This program uses various algorithms in order to determine the author of a work, using hashtables to store and access data quickly

#Build Files
```
clang -Wall -Werror -Wpedantic -Wextra
```
Make identify
```
make
make all
make identify
```

#Running
To run the identify program
```
./identify
```
command line options
```
-d : Specify path to database of authors and texts. The default is lib.db.
-n : Specify path to file of noise words to filter out. The default is noise.txt.
-k : Specify the number of matches. The default is 5.
-l : Specify the number of noise words to filter out. The default is 100.
-e : Set the distance metric to use as the Euclidean distance. This should be the default metric if
	no other distancemetric is specified.
-m : Set the distance metric to use as theManhattan distance.
-c : Set the distance metric to use as the cosine distance.
-h : Display program help and usage.
```

#errors
Errors when freeing memory does not pass valgrind
Errors when computing distance, values are not exactly the same as the given source code
