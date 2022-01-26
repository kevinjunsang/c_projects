#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//enumerate all four sorting types
typedef enum { INSERT, BATCHER, HEAP, QUICK } Algorithm;

int main(int argc, char **argv) {
    //initialize stats
    Stats stats;
    //initialize empty set for getopt
    Set s = empty_set();
    //set default seed, size, and elements
    srandom(13371453);
    uint32_t size = 100;
    uint32_t elements = 100;
    bool H = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, "ahbiqr:n:p:H:")) != -1) {
        switch (opt) {
        //getopt for all the cases
        case 'a': s = complement_set(empty_set()); break;
        case 'h': s = insert_set(HEAP, s); break;
        case 'b': s = insert_set(BATCHER, s); break;
        case 'i': s = insert_set(INSERT, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'r': srandom(atoi(optarg)); break;
        case 'n': size = atoi(optarg); break;
        case 'p': elements = atoi(optarg); break;
        case 'H': H = true; break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    //makes sure you only print only as many items are in the array
    if (size < elements) {
        elements = size;
    }
    //dynamically allocate memory
    uint32_t *A = (uint32_t *) malloc(size * sizeof(uint32_t));
    uint32_t *a = (uint32_t *) malloc(size * sizeof(uint32_t));
    //get the arry and 30 bit mask
    for (uint32_t i = 0; i < size; i += 1) {
        A[i] = (random() & 0x3FFFFFFF);
        a[i] = A[i];
    }
    //switch case for the four sorting algorithms
    //make sure to reset stats before running each sorting algorithm
    //make sure to unsort the sorted list in case of running multiple sorting algorithms
    for (int i = 0; i < 4; i += 1) {
        if (member_set(i, s)) {
            switch (i) {
            case INSERT:
                reset(&stats);
                insertion_sort(&stats, a, size);
                printf("Insertion Sort,"
                       " %" PRIu32 " elements, ",
                    size);
                printf("%" PRIu64 " moves, ", stats.moves);
                printf("%" PRIu64 " compares\n", stats.compares);
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, a[i]);
                    if ((i + 1) % 5 == 0) {
                        printf("\n");
                    }
                }
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = A[i];
                }
                break;
            case BATCHER:
                reset(&stats);
                batcher_sort(&stats, a, size);
                printf("Batcher Sort,"
                       " %" PRIu32 " elements, ",
                    size);
                printf("%" PRIu64 " moves, ", stats.moves);
                printf("%" PRIu64 " compares\n", stats.compares);
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, a[i]);
                    if ((i + 1) % 5 == 0) {
                        printf("\n");
                    }
                }
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = A[i];
                }
                break;
            case HEAP:
                reset(&stats);
                heap_sort(&stats, a, size);
                printf("Heap Sort,"
                       " %" PRIu32 " elements, ",
                    size);
                printf("%" PRIu64 " moves, ", stats.moves);
                printf("%" PRIu64 " compares\n", stats.compares);
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, a[i]);
                    if ((i + 1) % 5 == 0) {
                        printf("\n");
                    }
                }
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = A[i];
                }
                break;
            case QUICK:
                reset(&stats);
                quick_sort(&stats, a, size);
                printf("Quick Sort,"
                       " %" PRIu32 " elements, ",
                    size);
                printf("%" PRIu64 " moves, ", stats.moves);
                printf("%" PRIu64 " compares\n", stats.compares);
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, a[i]);
                    if ((i + 1) % 5 == 0) {
                        printf("\n");
                    }
                }
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = A[i];
                }
                break;
            }
        }
    }
    //free allocated memory for both arrays
    free(A);
    free(a);
}
