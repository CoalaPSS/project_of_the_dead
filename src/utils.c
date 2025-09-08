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

vec2_t vec2_div(vec2_t v, f32 factor) {
    return (vec2_t){.x = v.x/factor, .y = v.y/factor};
}

