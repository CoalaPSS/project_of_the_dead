#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include "types.h"
#include "physics.h"

#define DEBUG(MSG, ...) fprintf(stderr, "DEBUG %s:%d: " MSG "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define ERROR_RETURN(EXIT_CODE, MSG, ...) \
    do { \
        fprintf(stderr, "Error %s:%d: " MSG "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        exit(EXIT_CODE); \
    } while(0)

vec2_t vec2_add(vec2_t u, vec2_t v);
vec2_t vec2_sub(vec2_t u, vec2_t v);
vec2_t vec2_mult(vec2_t v, f32 factor);
void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect);