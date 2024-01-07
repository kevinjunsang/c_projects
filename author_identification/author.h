#pragma once

typedef struct Distance Distance;

Distance *dt_create(char *author, float distance);

void dt_delete(Distance **dt);

float dt_length(Distance *dt);
