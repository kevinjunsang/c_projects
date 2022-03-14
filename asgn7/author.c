#include "author.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

struct Distance {
    char *author;
    float distance;
};

Distance *dt_create(char *author, float distance) {
    Distance *dt = (Distance *) malloc(sizeof(Distance));
    if (dt) {
        dt->distance = distance;
        dt->author = author;
    }
    return dt;
}

void dt_delete(Distance **dt) {
    free(*dt);
    *dt = NULL;
}

float dt_length(Distance *dt) {
    return dt->distance;
}
