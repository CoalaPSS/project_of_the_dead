#pragma once

#include <stdint.h>

typedef int8_t i8;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef size_t usize;


typedef struct _vec2 {
    f32 x;
    f32 y;
} vec2_t;

typedef struct _vec3 {
    f32 x;
    f32 y;
    f32 z;
} vec3_t;

typedef struct _color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} color_t;