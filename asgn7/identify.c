#include "node.h"
#include "bv.h"
#include "ht.h"
#include "bf.h"
#include "text.h"
#include "parser.h"
//#include "pq.c"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char **argv) {
    uint8_t metric = 0;
    bool H = false;
    uint32_t noiselimit = 100;
    uint8_t K = 5;
    FILE *data = stdin;
    bool data_1 = true;
    FILE *noise_text = stdin;
    bool noise_1 = true;
    int opt = 0;
    while ((opt = getopt(argc, argv, "d:n:k:l:emch")) != -1) {
        switch (opt) {
        case 'd':
            data = fopen(optarg, "r");
            data_1 = false;
            break;
        case 'n':
            noise_text = fopen(optarg, "r");
            noise_1 = false;
            break;
        case 'k': K = atoi(optarg); break;
        case 'l': noiselimit = atoi(optarg); break;
        case 'e': metric = 0; break;
        case 'm': metric = 1; break;
        case 'c': metric = 2; break;
        case 'h': H = true; break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    if (H == true) {
        fprintf(stderr, "SYNOPSIS\n"
                        "	Identifies the authro of some anonymous text passed through stdin\n"
                        "	Basically computes k-nearest neighbors, where k = 1 by defauly.\n"
                        "	The number of noise wods that are removed is tunable.\n"
                        "	Uses either Euclidean, Manhattan, or cosine distance as metric.\n"
                        "\n"
                        "USAGE\n"
                        "	./identify [OPTIONS]\n"
                        "\n"
                        "OPTIONS\n"
                        "	-d database	Ddatabase of authors default is lib.db\n"
                        "	-k matches	Set number of top matches to display default is 5\n"
                        "	-n noisefile	Set file of words to ignore default is noise.txt\n"
                        "	-l limit	Set noise word limit default is 100\n"
                        "	-e		Set distance to Euclidean\n"
                        "	-m		Set distance to Manhattan\n"
                        "	-c		Set distance to cosine\n"
                        "	-h		Display program help and usage\n");
        return 1;
    }
    if (data_1 == true) {
        data = fopen("lib.db", "r");
    }
    if (noise_1 == true) {
        noise_text = fopen("noise.txt", "r");
    }
    Text *noise = text_create(noise_text, NULL);
    fclose(noise_text);
    int file_size = 0;
    char text[100];
    fscanf(data, "%d\n", &file_size);
    double d[file_size];
    char a[file_size][100];
    FILE *infile = stdin;
    Text *test = text_create(infile, noise);
    for (int i = 0; i < file_size; i += 1) {
        fgets(a[i], 100, data);
        fgets(text, 100, data);
        text[strlen(text) - 1] = '\0';
        a[i][strlen(a[i]) - 1] = '\0';
        FILE *temp_file = fopen(text, "r");
        Text *in_1 = text_create(temp_file, noise);
        fclose(temp_file);
        d[i] = text_dist(test, in_1, metric);
        text_delete(&in_1);
    }
    text_delete(&noise);
    text_delete(&test);
    float temp = 0xFFFF;
    uint8_t index = 0;
    if (metric == 0) {
        printf("Top %i, metric: Euclidean distance, noise limit: %i", K, noiselimit);
    }
    if (metric == 1) {
        printf("Top %i, metric: Manhattan distance, noise limit: %i", K, noiselimit);
    }
    if (metric == 2) {
        printf("Top %i, metric: Cosine distance, noise limit: %i", K, noiselimit);
    }
    printf("\n");
    for (uint8_t j = 0; j < K; j += 1) {
        for (uint8_t i = 0; i < file_size; i += 1) {
            if (temp > d[i]) {
                temp = d[i];
                index = i;
            }
        }
        d[index] = 0xFFFF;
        printf("%i) %s [%.14lf]\n", j + 1, a[index], temp);
        temp = 0xFFFF;
    }
    fclose(data);

    return 0;
}
