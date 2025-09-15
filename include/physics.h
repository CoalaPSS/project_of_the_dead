#pragma once

#include <stdbool.h>
#include <math.h>
#include <float.h>
#include "types.h"
#include "arraylist.h"

#define COLLISION_LIST_CAPACITY 256

typedef struct _aabb aabb_t;
typedef struct _body body_t;
typedef struct _collision_event collision_event_t;
typedef struct _physics_state physics_state_t;

typedef void (*on_hit_cb)(body_t *self, body_t *other, void *context);
typedef void (*on_hit_static_cb)(body_t *self, aabb_t *other, void *context);

extern physics_state_t g_physics_state;

typedef enum {
    X_AXIS,
    Y_AXIS
} AXIS;

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
    COLLISION_BODY,
    COLLISION_STATIC_BODY
};

struct _aabb {
    vec2_t position;
    vec2_t half_size;
};

struct _body {
    aabb_t aabb;
    vec2_t velocity;
    vec2_t acceleration;
    on_hit_cb on_hit;
    on_hit_static_cb on_hit_static;

    u8 type;
    u16 entity_id;
    // u16 id;
    void *owner;
};


struct _collision_event {
    u8 type;
    body_t *self;

    union  {
        body_t *body;
        aabb_t *static_body;
    } other;
};

struct _physics_state {
    array_list_t *body_list; // Guarda ponteiros para struct body_t
    array_list_t *static_body_list; // Guarda struct aabb_t
    array_list_t *collision_list; // Guarda struct collision_event_t
};


void physics_init();
void physics_add_body(body_t *body);
void physics_update(f32 dt, f32 speed, void *context);
void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect);
void dbg_print_physics_state();