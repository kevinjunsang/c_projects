#include "stats.h"

#include <stdint.h>

void insertion_sort(Stats *stats, uint32_t A[], int n) {
    //run through the length of the array
    for (int i = 1; i < n; i += 1) {
        int j = i;
        //create temp term to take note of value at certain array index
        uint32_t temp = move(stats, A[i]);
        while (j > 0 && cmp(stats, temp, A[j - 1]) < 0) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp);
    }
}
