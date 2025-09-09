#pragma once

#include <stdbool.h>
#include <math.h>
#include "types.h"
#include "arraylist.h"

enum BODY_TYPE {
    BT_CURSOR,
    BT_PLAYER,
    BT_STATIC_TILE,
    BT_PROJECTILE,
};

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
} body_t;

typedef struct _static_body {
    aabb_t aabb;
    bool is_solid;
} static_body_t;

typedef void(*collision_cb_func)(body_t *self, body_t *other, void *context);
typedef void(*static_collision_cb_func)(body_t *self, static_body_t *static_body, void *context);

typedef struct _physics_state {
    array_list_t *body_list;
    array_list_t *static_body_list;

    collision_cb_func collision_callback;
    static_collision_cb_func static_collision_callback;
} physics_state_t;

void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect);

bool physics_point_aabb_intersect(vec2_t point, aabb_t box);
bool physics_aabb_aabb_intersect(aabb_t box_a, aabb_t box_b);

physics_state_t *init_physics_state(collision_cb_func, static_collision_cb_func);

void physics_add_static_body(physics_state_t *state, static_body_t *s_body); 
void physics_add_body(physics_state_t *state, body_t *body);

void physics_update_entities(physics_state_t *state);
void physics_collision_update(physics_state_t *state, void *context);

void dbg_print_physics_state(physics_state_t *state);