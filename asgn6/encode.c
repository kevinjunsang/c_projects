#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "node.h"
#include "pq.h"
#include "stack.h"
#include "io.h"
#include "huffman.h"

int main(void) {
    return 5;
}

//couldn't do the encode program because I couldn't figure out the io.c and huffman.c
//getopt loop like usual
//I have an idea how the encode program would work
//First we would have to construct the tree and histogram
//using the tree, we would assign values to ascii values depending on the frequency
//we would use a node to represent this
//finally we would use the huffman and io functions to read and write out to different files
//print out if getopt input says so
//destroy the tree
