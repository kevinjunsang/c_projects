#include "universe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    //allocating memory for universe given size of rows and cols
    Universe *u = (Universe *) malloc(sizeof(Universe));
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t r = 0; r < rows; r += 1) {
        u->grid[r] = (bool *) calloc(cols, sizeof(bool));
    }
    //declaring rows cols and toroidal
    //return universe
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    return u;
}

void uv_delete(Universe *u) {
    //free the memory alocated to the universe
    //first need to free the contents of the grid
    //then free the grid itself
    free(u->grid);
    free(u);
}

uint32_t uv_rows(Universe *u) {
    return u->rows;
}

uint32_t uv_cols(Universe *u) {
    return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    //if the given coordinates are within the range of the rows and columns
    //set the boolean at that coordinate to be true or alive
    if (r >= 0 && r < uv_rows(u) && c >= 0 && c < uv_cols(u)) {
        u->grid[r][c] = true;
    }
}
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    //same as uv_live_cell but set as false or dead
    if (r >= 0 && r < uv_rows(u) && c >= 0 && c < uv_cols(u)) {
        u->grid[r][c] = false;
    }
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    //if the given coordinates are within the range of the rows and columns
    //get the boolean value from those coordinates
    if (r >= 0 && r < uv_rows(u) && c >= 0 && c < uv_cols(u)) {
        return u->grid[r][c];
    }
    return -1;
}

bool uv_populate(Universe *u, FILE *infile) {
    //loop through the file and set the coordinates as alive using uv_live_cell
    for (uint32_t i = 0; i < uv_rows(u) * uv_cols(u); i += 1) {
        int r, c;
        fscanf(infile, "%d %d\n", &r, &c);
        if (r < 0 || c < 0 || r >= uv_rows(u) || c >= uv_cols(u)) {
            return -1;
        }
        uv_live_cell(u, r, c);
    }
    return 0;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    //for toroidal set boudns for min and max for both rows and columns
    //if the value at the given coordinate is true, increment num
    uint32_t num = 0;
    if (u->toroidal == true) {
        uint32_t r_min = (r + uv_rows(u) - 1) % uv_rows(u);
        uint32_t r_max = (r + 1) % uv_rows(u);
        uint32_t c_min = (c + uv_cols(u) - 1) % uv_cols(u);
        uint32_t c_max = (c + 1) % uv_cols(u);
        if (uv_get_cell(u, r_min, c_min)) {
            num += 1;
        }
        if (uv_get_cell(u, r_min, c)) {
            num += 1;
        }
        if (uv_get_cell(u, r_min, c_max)) {
            num += 1;
        }
        if (uv_get_cell(u, r, c_min)) {
            num += 1;
        }
        if (uv_get_cell(u, r, c_max)) {
            num += 1;
        }
        if (uv_get_cell(u, r_max, c_min)) {
            num += 1;
        }
        if (uv_get_cell(u, r_max, c)) {
            num += 1;
        }
        if (uv_get_cell(u, r_max, c_max)) {
            num += 1;
        }
    } else {
        //if not toroidal loop through one more and one less on both the rows and columns
        //if the index is less than 0, or greater than the range don't pass through uv_get_cell
        //otherwise, if the value there is true, increment num
        int r_min = r - 1;
        int r_max = r + 1;
        int c_min = c - 1;
        int c_max = c + 1;
        for (int row = r_min; row <= r_max; row += 1) {
            for (int col = c_min; col <= c_max; col += 1) {
                if (col < 0 || row < 0 || col >= uv_cols(u) || row >= uv_rows(u)) {
                    continue;
                }
                if (uv_get_cell(u, row, col) == true) {
                    num += 1;
                }
            }
        }
        if (uv_get_cell(u, r, c) == true && num > 0) {
            num -= 1;
        }
    }
    return num;
}

void uv_print(Universe *u, FILE *outfile) {
    //loop through the rows and columns, if the value at the coordinate is true
    //print "o" otherwise, print ". "
    for (uint32_t row = 0; row < uv_rows(u); row += 1) {
        for (uint32_t col = 0; col < uv_cols(u); col += 1) {
            if (uv_get_cell(u, row, col) == true) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
}
