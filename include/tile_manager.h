#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "arraylist.h"
#include "physics.h"
#include "renderer.h"
#include "resource_manager.h"

#define MAX_TILE_IDS 65536
#define TILEINFO_TABLE_SIZE 256

enum TILE_ID {
    TILE_EMPTY,
    TILE_GRASS_ID,
    TILE_ROCK_WALL_ID,
    TILE_DIRT_ID,
    TILE_BUSH_ID,
    TILE_TREE_ID,
    TILE_STONE_PATH_ID,
    TILE_STONE_WALL_ID,
    TILE_BOX_ID, 
    TILE_RED_BOX
};

enum TILEMAP_LAYERS {
    LAYER_GROUND,
    LAYER_OBJECT,
    LAYER_FOREGROUND
};


typedef struct _tileinfo {
    bool solid;
    f32 friction;
    i32 damage;

    u16 texture_id;
    u8 debug_color_id;
} tileinfo_t;


typedef struct _tilemap {
    u32 width;
    u32 height;
    u32 tile_size;
    int layer_count;

    u16 **layers;
    tileinfo_t *tileinfo_table;
} tilemap_t;


tilemap_t *tilemap_create(SDL_Renderer *renderer, u32 width, u32 height, u32 tile_size, int layer_count);
void tilemap_load_layer(tilemap_t *map, const u16 *tiles, usize tile_array_size, int layer_id);
void set_tile(tilemap_t *map, u32 x, u32 y, u16 id, int layer);
u16 get_tile(tilemap_t *map, u32 x, u32 y, int layer);
void tilemap_get_collision_list(physics_state_t *p_state, tilemap_t *map, int layer);
void render_tilemap(SDL_Renderer *renderer, tilemap_t *tilemap, texture_atlas_t *tilemap_atlas);