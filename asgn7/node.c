#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

Node *node_create(char *word) {
	Node *n = (Node *) malloc(sizeof(Node));
	if (n) {
		n->count = 1;
		n->word = strdup(word);
	}
	return n;
}

void node_delete(Node **n) {
	free((*n)->word);
	free(*n);
	*n = NULL;
}

void node_print(Node *n) {
	if (n) {
		printf("%s ", n->word);
		printf("%d\n", n->count);
	}
	else {
		printf("-------\n");
	}
}

