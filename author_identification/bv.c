#include "bv.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define BITS_PER_UNIT 8

//as per the bv8.h file in the Code Comments repo
//Credit to Professor Long
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        uint32_t words = length / BITS_PER_UNIT + (length % BITS_PER_UNIT ? 1 : 0);
        bv->vector = (uint8_t *) calloc(words, sizeof(uint8_t));
        bv->length = length;
        return bv;
    } else {
        return (BitVector *) 0;
    }
}

void bv_delete(BitVector **bv) {
    if ((*bv) && (*bv)->vector) {
        free((*bv)->vector);
    }
    if (*bv) {
        free(*bv);
    }
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    return bv ? bv->length : 0;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (bv && bv->vector) {
        bv->vector[i / BITS_PER_UNIT] |= (0x1 << i % BITS_PER_UNIT);
        return true;
    } else {
        return false;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (bv && bv->vector) {
        bv->vector[i / BITS_PER_UNIT] &= ~(0x1 << i % BITS_PER_UNIT);
        return true;
    } else {
        return false;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    return (bv->vector[i / BITS_PER_UNIT] >> i % BITS_PER_UNIT) & 1;
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv_length(bv); i += 1) {
        if (bv_get_bit(bv, i) == 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}
