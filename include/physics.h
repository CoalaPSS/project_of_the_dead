#pragma once

#include "types.h"
#include "arraylist.h"


typedef struct _aabb {
    vec2_t position;
    vec2_t half_size;
} aabb_t;

typedef struct _body {
    aabb_t aabb;
    vec2_t velocity;
    vec2_t acceleration;
} body_t;

typedef struct _static_body {
    aabb_t aabb;
} static_body_t;