#pragma once

#include "types.h"

typedef struct _player_data {
    u8 pov;
    u16 xp_level;
} player_data_t;

typedef struct _projectile_data {
    int damage;
    f32 lifetime;
} projectile_data_t;

typedef struct _entity {
    u32 body_id;
    u32 animation_id;
    bool is_active;
    u8 health;

    union {
        player_data_t player;
        projectile_data_t projectile;
    } data;
    
} entity_t;