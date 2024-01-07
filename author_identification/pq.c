#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pq.h"
#include "author.h"

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    Distance **dt;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->head = q->tail = 0;
        q->capacity = capacity;
        q->dt = (Distance **) malloc(capacity * sizeof(Distance *));
    }
    return (PriorityQueue *) 0;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->dt) {
        free((*q)->dt);
        free(*q);
        *q = NULL;
    }
}

bool pq_empty(PriorityQueue *q) {
    if (q->tail == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    if (q->tail == q->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return q->tail;
}

bool enqueue(PriorityQueue *q, char *author, double dist) {
    if (pq_full(q)) {
        return false;
    }
    Distance *dt = dt_create(author, dist);
    q->dt[q->tail] = dt;
    q->tail += 1;
    Distance *temp;
    uint32_t n = q->tail;
    for (uint32_t i = 0; i < n; i += 1) {
        uint32_t j = i;
        temp = q->dt[i];
        while (j > 0 && dt_length(q->dt[i]) > dt_length(q->dt[j - 1])) {
            q->dt[j] = q->dt[j - 1];
            j -= 1;
        }
        q->dt[j] = temp;
    }
    return true;
}

bool dequeue(PriorityQueue *q, char **author, double *dist) {
    if (pq_empty(q)) {
        return false;
    }
    author += 1;
    dist += 1;
    return true;
}

void pq_print(PriorityQueue *q) {
    int i = 1;
    if (pq_full(q)) {
        i = 3;
    }
    i += 1;
}
