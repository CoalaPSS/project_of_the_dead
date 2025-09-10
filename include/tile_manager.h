#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "arraylist.h"
#include "physics.h"
#include "renderer.h"

#define MAX_TILE_IDS 65536
#define TILEINFO_TABLE_SIZE 512
#define MAP_WIDTH 32
#define MAP_HEIGTH 18
#define TILE_SIZE 60

enum TILE_ID {
    TILE_EMPTY,
    TILE_GRASS_ID,
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


extern const u16 ground_tiles[];
extern const u16 object_tiles[];

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


tilemap_t *create_base_tilemap(const u16 *floor_tiles, const u16 *wall_tiles, u32 width, u32 height, u32 tile_size);
void set_tile(tilemap_t *tilemap, int x, int y, u16 id, int layer);
void render_tilemap(SDL_Renderer *renderer, tilemap_t *tilemap);
