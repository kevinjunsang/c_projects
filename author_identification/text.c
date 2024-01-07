#include "text.h"
#include "node.h"
#include "ht.h"
#include "bf.h"
#include "salts.h"
#include "speck.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <regex.h>
#include <string.h>
#include <math.h>
#include "metric.h"

struct Text {
    HashTable *ht;
    BloomFilter *bf;
    uint32_t word_count;
};

uint32_t noiselimit;
#define ht_size 524288
#define bf_size 2097152
#define WORD    "[a-zA-Z]+((-|')[a-zA-Z]+)*"

Text *text_create(FILE *infile, Text *noise) {
    Text *text = (Text *) malloc(sizeof(Text));
    text->ht = ht_create(ht_size);
    text->bf = bf_create(bf_size);
    text->word_count = 0;
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        text = NULL;
    }
    char *word = NULL;
    uint32_t counter = 0;
    if (noise == NULL) {
        while ((word = next_word(infile, &re)) != NULL && counter < noiselimit) {
            for (uint32_t i = 0; word[i]; i += 1) {
                word[i] = tolower(word[i]);
            }
            bf_insert(text->bf, word);
            ht_insert(text->ht, word);
            counter += 1;
        }
    } else {
        while ((word = next_word(infile, &re)) != NULL) {
            for (uint32_t i = 0; word[i]; i += 1) {
                word[i] = tolower(word[i]);
            }
            if (text_contains(noise, word) == false) {
                bf_insert(text->bf, word);
                ht_insert(text->ht, word);
                text->word_count += 1;
            }
        }
    }
    regfree(&re);
    return text;
}

void text_delete(Text **text) {
    ht_delete(&(*text)->ht);
    bf_delete(&(*text)->bf);
    free((*text)->ht);
    free((*text)->bf);
    free(*text);
    *text = NULL;
}

double text_dist(Text *text1, Text *text2, Metric metric) {
    double sum_m, sum_e, sum_c, t_1, t_2, freq;
    sum_m = 0;
    sum_e = 0;
    sum_c = 0;
    Node *n = NULL;
    HashTableIterator *hti_1 = hti_create(text1->ht);
    HashTableIterator *hti_2 = hti_create(text2->ht);
    while ((n = ht_iter(hti_1)) != NULL) {
        if (text_contains(text2, n->word) == true) {
            t_1 = text_frequency(text1, n->word);
            t_2 = text_frequency(text2, n->word);
            freq = fabs(t_1 - t_2);
            sum_c += fabs(t_1 * t_2);
        } else {
            freq = text_frequency(text1, n->word);
        }
        sum_m += freq;
        sum_e += freq * freq;
    }
    while ((n = ht_iter(hti_2)) != NULL) {
        if (text_contains(text1, n->word) == false) {
            freq = text_frequency(text2, n->word);
            sum_m += freq;
            sum_e += freq * freq;
        }
    }
    hti_delete(&hti_1);
    hti_delete(&hti_2);
    sum_e = sqrt(sum_e);
    if (metric == 1) {
        return sum_m;
    }
    if (metric == 0) {
        return sum_e;
    }
    if (metric == 2) {
        return 1 - sum_c;
    }
    return 0.0;
}

double text_frequency(Text *text, char *word) {
    if (text_contains(text, word)) {
        uint32_t num = ht_lookup(text->ht, word)->count;
        double frequency;
        frequency = (double) num / (double) text->word_count;
        return frequency;
    } else {
        return 0.0;
    }
}

bool text_contains(Text *text, char *word) {
    if (bf_probe(text->bf, word)) {
        Node *n = ht_lookup(text->ht, word);
        if (n != NULL) {
            return true;
        }
        return false;
    } else {
        return false;
    }
}

void text_print(Text *text) {
    ht_print(text->ht);
}
