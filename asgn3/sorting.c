#include "insert.h"
#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "stats.h"
#include "set.h"

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<inttypes.h>

typedef enum { INSERT, BATCHER, HEAP, QUICK } Algorithm;

int main(int argc, char **argv) {
	Stats stats;
	Set s = empty_set();
	srandom(13371453);
	uint32_t size = 100;
	uint32_t elements = 100;
	bool H = false;
	int opt = 0;
	while ((opt = getopt(argc, argv, "ahbiqr:n:p:H:")) != -1) {
		switch (opt) {
		case 'a':
			s = complement_set(empty_set());
			break;
		case 'h':
			s = insert_set(HEAP, s);
			break;
		case 'b':
			s = insert_set(BATCHER, s);
			break;
		case 'i':
			s = insert_set(INSERT, s);
			break;
		case 'q':
			s = insert_set(QUICK, s);
			break;
		case 'r':
			srandom(atoi(optarg));
			break;
		case 'n':
			size = atoi(optarg);
			break;
		case 'p':
			elements = atoi(optarg);
			break;
		case 'H':
			H = true;
			break;
		default:
			fprintf(stderr, "error\n");
			return 1;
		}
	}
	if (size < elements) {
		 elements = size;
	}
	uint32_t a[size];
	for (uint32_t i = 0; i < size; i += 1) {
		a[i] = (random() & 0x3FFFFFFF);
	}
	for (int i = 0; i < 4; i += 1) {
		if (member_set(i, s)) {
			switch(i) {
			case INSERT:
				reset(&stats);
				insertion_sort(&stats, a, size);
				printf("Insertion Sort,"" %" PRIu32 " elements, ", elements);
				printf("%" PRIu64 " moves, ", stats.moves);
				printf("%" PRIu64 " compares\n", stats.compares);
				for (uint32_t i = 0; i < size; i += 1) {
					printf("%13" PRIu32, a[i]);
					if ((i + 1) % 5 == 0) {
						printf("\n");
					}
				}
				break;
			case QUICK:
				reset(&stats);
				quick_sort(&stats, a, size);
                                printf("Quick Sort,"" %" PRIu32 " elements, ", elements);
                                printf("%" PRIu64 " moves, ", stats.moves);
                                printf("%" PRIu64 " compares\n", stats.compares);
                                for (uint32_t i = 0; i < size; i += 1) {
                                        printf("%13" PRIu32, a[i]);
                                        if ((i + 1) % 5 == 0) {
                                                printf("\n");
                                        }
                                }
				break;
			}
		}
		
	}
}	



