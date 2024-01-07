#include "code.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Code code_init(void) {
    Code c = { 0, { 0 } };
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    if (code_full(c) != true) {
        c->bits[i / 8] |= (0x1 << (i % 8));
        return true;
    } else {
        return false;
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (code_full(c) != true) {
        c->bits[i / 8] &= ~(0x1 << (i % 8));
        return true;
    } else {
        return false;
    }
}

bool code_get_bit(Code *c, uint32_t i) {
    if (code_full(c) != true) {
        uint32_t temp = c->bits[i / 8] << (i % 8);
        if (temp == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c) != true) {
        if (bit != 1) {
            code_clr_bit(c, c->top);
        } else {
            code_set_bit(c, c->top);
        }
        c->top += 1;
        return true;
    } else {
        return false;
    }
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c) != true) {
        *bit = code_get_bit(c, c->top);
        code_clr_bit(c, c->top);
        c->top -= 1;
        return true;
    } else {
        return false;
    }
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < code_size(c); i += 1) {
        printf("%" PRIu8 "\n", c->bits[i]);
    }
}
