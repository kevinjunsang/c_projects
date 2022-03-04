#include <stdio.h>
#include <stdlib.h>
#include "node.h"

//creating node was part of Dr. Long's slide presentation

//create node by allocating enough memory
//initialize left and right as 0
//initialize symbol and frequency
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->left = n->right = NULL;
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

//delete node by freeing memory
//set pointer as 0
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

//join node with symbol '$' as per documentation
//add frequencies together
//initialize left and right
//return node
Node *node_join(Node *left, Node *right) {
    Node *n = node_create('$', right->frequency + left->frequency);
    n->right = right;
    n->left = left;
    return n;
}

//print node recursively
void node_print(Node *n) {
    if (n) {
        printf("%d", n->symbol);
        node_print(n->left);
        node_print(n->right);
    }
}
