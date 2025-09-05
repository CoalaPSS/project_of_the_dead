#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static int debug_count = 0;

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct _vec2 {
    double x;
    double y;
} vec2_t;

typedef struct _color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} color_t;

void throw_exception(char *msg);
void DEBUG(char *msg);

#endif