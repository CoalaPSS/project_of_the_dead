#include "../include/utils.h"

void vec2_add_to(vec2_t *u, vec2_t v) {
    u->x = u->x + v.x;
    u->y = u->y + v.y;
}

vec2_t vec2_add(vec2_t u, vec2_t v) {
    return (vec2_t){.x = u.x + v.x, .y = u.y + v.y};
}
vec2_t vec2_sub(vec2_t u, vec2_t v) {
    return (vec2_t){.x = u.x - v.x, .y = u.y - v.y};
}

vec2_t vec2_mult(vec2_t v, f32 factor) {
    return (vec2_t){.x = v.x * factor, .y = v.y * factor};
}

vec2_t vec2_div(vec2_t v, f32 factor) {
    return (vec2_t){.x = v.x/factor, .y = v.y/factor};
}

vec2_t vec2_from_int(u32 integer, f32 factor) {
    f32 res = (f32)integer * factor;
    return (vec2_t){res, res};
}

vec2_t vec2_normalize(vec2_t v) {
    f32 mag = sqrtf((v.x * v.x) + (v.y * v.y));

    if (mag > 0) {
        return vec2_div(v, mag);
    }
}