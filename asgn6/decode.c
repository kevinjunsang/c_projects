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
//First we would have to recreate the huffman tree
//We would use the huffman tree to find out the values signed to the ascii values
//we would the read and write out the decoded output to the files specified by the getopt loop
//destroy the tree
//print out values if getopt says so
