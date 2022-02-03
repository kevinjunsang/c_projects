#include "universe.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <ncurses.h>
#include <string.h>

#define DELAY 50000
int main();

//swap function to swap between two universes
void swap(Universe **a, Universe **b) {
    Universe *temp = *a;
    *a = *b;
    *b = temp;
}

void next_gen(Universe *a, Universe *b, uint32_t row, uint32_t col) {
    //loop through the universe
    //if the cell is alive and has 2 or 3 neighbors, it stays alive
    //if the cell is dead and has exactly 3 neighbors, it is alive
    //in all other cases, the cell is dead
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
        }
    }
}

int main(int argc, char **argv) {
    //create getopt
    int opt = 0;
    bool S = true;
    uint32_t gen_num = 100;
    bool toroidal = false;
    //declare both the in and out files
    FILE *in;
    FILE *out;
    out = stdout;
    //getopt
    while ((opt = getopt(argc, argv, "tsn:i:o:")) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': S = false; break;
        case 'n':
            //check for generations out of bounds
            if (atoi(optarg) < 0) {
                printf("generations out of bounds, generations set to 100\n");
                gen_num = 100;
                break;
            }
            gen_num = atoi(optarg);
            break;
        case 'i': in = fopen(optarg, "r"); break;
        case 'o': out = fopen(optarg, "w"); break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    //create two universes A and B dimensions given by the input file
    int r, c;
    fscanf(in, "%d  %d\n", &r, &c);
    if (r < 1 || c < 1) {
        r = 50;
        c = 50;
    }
    uint32_t row = r;
    uint32_t col = c;
    Universe *A = uv_create(row, col, toroidal);
    Universe *B = uv_create(row, col, toroidal);
    //populate universe A and close the in file
    uv_populate(A, in);
    fclose(in);
    //initialize the screen and set the cursor to false
    initscr();
    curs_set(FALSE);
    //for loop through the number of generations
    for (uint32_t count = 0; count < gen_num; count += 1) {
        //go to next generation
        next_gen(A, B, row, col);
        clear();
        //print the resulting universe onto the screan
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
        //swap the Universes
        swap(&A, &B);
        refresh();
        //add delay
        usleep(DELAY);
    }
    //print out the final generation to the outfile
    //end the window
    //close the out file
    uv_print(A, out);
    endwin();
    fclose(out);
    return 0;
}
