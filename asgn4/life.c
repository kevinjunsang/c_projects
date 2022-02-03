#include "universe.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <ncurses.h>

int main();

void swap(Universe **a, Universe **b) {
    Universe *temp = *a;
    *a = *b;
    *b = temp;
}

void next_gen(Universe *a, Universe *b, uint32_t row, uint32_t col) {
    for (uint32_t r = 0; r < row; r += 1) {
        for (uint32_t c = 0; c < col; c += 1) {
            uint32_t census = uv_census(a, r, c);
            if (uv_get_cell(a, r, c) == true && (census == 2 || census == 3)) {
                uv_live_cell(b, r, c);
            } else if (uv_get_cell(a, r, c) == false && census == 3) {
                uv_live_cell(b, r, c);
            } else {
                uv_dead_cell(b, r, c);
            }
            refresh();
        }
    };
}

int main(int argc, char **argv) {
    int opt = 0;
    bool S = true;
    uint32_t gen_num = 100;
    bool toroidal = false;
    FILE *in;
    FILE *out;
    while ((opt = getopt(argc, argv, "tsn:i:o:")) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': S = false; break;
        case 'n': gen_num = atoi(optarg); break;
        case 'i': in = fopen(optarg, "r"); break;
        case 'o': out = fopen(optarg, "w"); break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    uint32_t row, col;
    fscanf(in, "%" SCNu32 " %" SCNu32 "\n", &row, &col);
    Universe *A = uv_create(row, col, toroidal);
    Universe *B = uv_create(row, col, toroidal);
    uv_populate(A, in);
    fclose(in);
    initscr();
    curs_set(FALSE);
    for (uint32_t count = 0; count < gen_num; count += 1) {
        next_gen(A, B, row, col);
	clear();
        for (uint32_t r = 0; r < row; r += 1) {
            for (uint32_t c = 0; c < col; c += 1) {
                if (uv_get_cell(A, r, c) == true) {
                    mvprintw(r, c, "o");
                } else {
                    mvprintw(r, c, " ");
                }
                refresh();
            }
        }
        swap(&A, &B);
	refresh();
        usleep(50000);
    }
    uv_print(A, out);
    endwin();
    fclose(out);
}
