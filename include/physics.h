#pragma once

#include <stdbool.h>
#include "types.h"
#include "arraylist.h"

// typedef (*body_collision_callback_func)(body_t *self, body_t *other);
// typedef (*static_body_collision_callback_func)(body_t *self, static_body_t *other);

typedef struct _aabb {
    vec2_t position;
    vec2_t half_size;
} aabb_t;

typedef struct _body {
    aabb_t aabb;
    vec2_t velocity;
    vec2_t acceleration;
    usize type_id;

    void *owner;
    // body_collision_callback_func body_collision_cb;
    // static_body_collision_callback_func static_body_collision_cb;
} body_t;

typedef struct _static_body {
    aabb_t aabb;
} static_body_t;

typedef struct _physics_state {
    array_list_t *body_list;
    array_list_t *static_body_list;
    void (*body_collision_callback_func)(body_t *self, body_t *other);
    void (*static_body_collision_callback_func)(body_t *self, static_body_t *static_other);
} physics_state_t;

void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect);

bool physics_point_aabb_intersect(vec2_t point, aabb_t box);
bool physics_aabb_aabb_intersect(aabb_t box_a, aabb_t box_b);

physics_state_t *init_physics_state(void (*collision_cb_func)(body_t *self, body_t *other), void (*static_collision_cb_func)(body_t *self, static_body_t *static_body));

void physics_add_static_body(physics_state_t *state, aabb_t aabb); 
void physics_add_body(physics_state_t *state, body_t *body);
// void physics_add_body(physics_state_t *state, vec2_t position, vec2_t size, usize body_id, void *owner);
void physics_update_entities(physics_state_t *state);
void physics_collision_update(physics_state_t *state);

void dbg_print_physics_state(physics_state_t *state);