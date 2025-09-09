#pragma once

#include <stdbool.h>
#include <math.h>
#include "types.h"
#include "arraylist.h"
// #include "tile_manager.h"


enum BODY_TYPE {
    BODY_STATIC,
    BODY_DYNAMIC,
};

enum BODY_ID {
    ID_PLAYER,
    ID_ENEMY,
    ID_PROJECTILE,
    ID_COLLECTABLE,
    ID_DOOR,
    ID_CHEST,
    ID_BOX
};

typedef struct _aabb {
    vec2_t position;
    vec2_t half_size;
} aabb_t;

typedef struct _body {
    aabb_t aabb;
    vec2_t velocity;
    vec2_t acceleration;

    u8 type;
    u32 id;
    
    void *owner;
} body_t;

typedef void(*body_collision_cb_func)(body_t *self, body_t *other, void *context);
typedef void(*tile_collision_cb_func)(body_t *body, aabb_t *tile_aabb, void *context);

typedef struct _physics_state {
    array_list_t *body_list;
    array_list_t *tile_list;

    body_collision_cb_func body_collision_callback;
    tile_collision_cb_func tile_collision_callback;
} physics_state_t;

physics_state_t *init_physics_state(body_collision_cb_func body_cb, tile_collision_cb_func tile_cb);

void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect);

bool physics_point_aabb_intersect(vec2_t point, aabb_t box);
bool physics_aabb_aabb_intersect(aabb_t box_a, aabb_t box_b);

void physics_add_body(physics_state_t *state, body_t *body);

void physics_update_entities(physics_state_t *state);
void physics_collision_update(physics_state_t *state, void *context);

void dbg_print_physics_state(physics_state_t *state);