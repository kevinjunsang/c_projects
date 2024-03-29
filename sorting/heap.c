#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

uint32_t max_child(Stats *stats, uint32_t A[], uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    //compare right and left array values, return larger value
    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) > 0) {
        return right;
    } else {
        return left;
    }
}

void fix_heap(Stats *stats, uint32_t A[], uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);
    while (mother <= (last / 2) && found == false) {
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            //stop loop when array value of mother is greater than value of great
            found = true;
        }
    }
}

void build_heap(Stats *stats, uint32_t A[], uint32_t first, uint32_t last) {
    //build heap
    for (uint32_t father = (last / 2); father > first - 1; father -= 1) {
        fix_heap(stats, A, father, last);
    }
}

void heap_sort(Stats *stats, uint32_t A[], uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    //run through build heap from 1 to length
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf -= 1) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
