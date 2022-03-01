#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pq.h"
#include "node.h"

//followed struct creation format from the lecture
//head is place in the queue
//size is size of the queue
//**Q is the node
struct PriorityQueue {
	uint32_t head;
	uint32_t size;
	Node **Q;
};

PriorityQueue *pq_create(uint32_t capacity) {
	PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
	if (q) {
		q->head = NULL;
		q->size = capacity;
		q->Q = (Node **)malloc(capacity *  sizeof(Node *));
		if (q->Q) {
			return q;
		}
		free(q);
	}
	return (PriorityQueue *) 0;
} 

void pq_delete(PriorityQueue **q) {
	if (*q) {
		free(*q);
		*q = NULL;
	}
}

bool pq_empty(PriorityQueue *q) {
	if (q->head == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool pq_full(PriorityQueue *q) {
	if (q->head == q->size) {
		return true;
	}
	else {
		return false;
	}

uint32_t pq_size(PrioirtyQueue *q) {
	return q->size;
}

void insert_sort(PriorityQueue *q) {
	

bool enqueue(PriorityQueue *q, Node *n) {
	if (q) {
		if (pq_full(q)) {
			return false:
		}
		q->Q[q->head] = *n;
		q->head += 1;
		
		return true;
	}
	else {
		return false;
	}
}

bool dequeue(PriorityQueue *q, Node **n) {
	if (q) {
		if (pq_empty(q)) {
			return false;
		}
		*n = q->Q[q->head - 1];
		q->head -= 1;
		return true;
	}
	else {
		return false;
	}
}

void pq_print(PriorityQueue *q) {
	for (uint32_t i = 0; i < q->head; i += 1) {
		node_print(q->Q[i]);
	}
}
