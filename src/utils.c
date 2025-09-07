#include "../include/utils.h"


vec2_t vec2_add(vec2_t u, vec2_t v) {
    return (vec2_t){.x = u.x + v.x, .y = u.y + v.y};
}
vec2_t vec2_sub(vec2_t u, vec2_t v) {
    return (vec2_t){.x = u.x - v.x, .y = u.y - v.y};
}

vec2_t vec2_mult(vec2_t v, f32 factor) {
    return (vec2_t){.x = v.x * factor, .y = v.y * factor};
}

void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect) {
    (*rect).x = aabb.position.x;
    (*rect).y = aabb.position.y; 
    (*rect).w = aabb.half_size.x * 2;
    (*rect).h = aabb.half_size.x * 2;
}