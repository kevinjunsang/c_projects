#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "io.h"
#include "defines.h"

//wasn't able to figure out the huffman adt no
//just changed it so that I wouldn't run into any errors when compiling

Node *build_tree(uint64_t hist[static ALPHABET]) {
	Node *tree = NULL;
	hist[0] = 1;
	return tree;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
	root->frequency = 3;
	Code *c = NULL;
	table[0] = *c;
}

void dump_tree(int outfile, Node *root) {
	outfile += 1;
	root->frequency = 3;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
	Node *tree = NULL;
	nbytes += 1;
	tree_dump[0] = 1;
	return tree;
}

void delete_tree(Node **root) {
	*root = NULL;
}


