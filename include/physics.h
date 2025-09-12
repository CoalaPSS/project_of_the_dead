#pragma once

#include <stdbool.h>
#include <math.h>
#include <float.h>
#include "types.h"
#include "arraylist.h"
// #include "tile_manager.h"

#define COLLISION_LIST_CAPACITY 256

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

enum COLLISION_TYPE {
    COLLISION_BODY_BODY,
    COLLISION_BODY_TILE
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
    u16 id;
    
    void *owner;
} body_t;

typedef void(*body_collision_cb)(body_t *self, body_t *other, void *context);
typedef void(*tile_collision_cb)(body_t *body, aabb_t tile_aabb, void *context);

typedef struct _collision_event {
    body_t *body_01;
    body_t *body_02;
    // vec2_t tile_pos;
    aabb_t tile_aabb;
    u8 type;
} collision_event_t;

typedef struct _physics_state {
    array_list_t *body_list; // Guarda ponteiros para struct body_t
    array_list_t *tile_aabb_list; // Guarda struct aabb_t

    array_list_t *collision_list; // Guarda struct collision_event_t

    body_collision_cb body_collision_callback;
    tile_collision_cb tile_collision_callback;
} physics_state_t;

physics_state_t *init_physics_state(body_collision_cb body_cb, tile_collision_cb tile_cb);
void physics_add_body(physics_state_t *state, body_t *body);
void physics_update(physics_state_t *state, f32 dt, f32 speed, void *context);
void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect);

// bool physics_point_aabb_intersect(vec2_t point, aabb_t box);
// bool physics_aabb_aabb_intersect(aabb_t box_a, aabb_t box_b);
// void physics_update_entities(physics_state_t *state);
// void physics_collision_update(physics_state_t *state, void *context);

void dbg_print_physics_state(physics_state_t *state);