#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "arraylist.h"
#include "physics.h"
#include "renderer.h"

#define TILE_TABLE_SIZE 256
#define MAP_WIDTH 32
#define MAP_HEIGTH 18
#define TILE_SIZE 60

enum TILE_TYPE {
    TILE_GRASS,
    TILE_DIRT,
    TILE_BUSH,
    TILE_TREE,
    TILE_STONE_PATH,
    TILE_STONE_WALL,
    TILE_BOX,
    
};

typedef struct _tile_type {
    i32 id;
    u8 color_id;
} tile_type_t;

// extern const u8 world_tiles[];
extern const u8 floors[];
extern const u8 walls[];


typedef struct _tile {
    vec2_t position;
    u32 id;
    u8 color_id;
    bool solid;
} tile_t;


typedef struct _tilemap {
    u32 width, height;
    u32 tile_size;

    array_list_t *floors;
    array_list_t *walls;
    array_list_t *objects;
} tilemap_t;

tilemap_t *create_base_tilemap(const u8 *floor_tiles, const u8 *wall_tiles, u32 width, u32 height, u32 tile_size, physics_state_t *p_state);
void render_tilemap(SDL_Renderer *renderer, tilemap_t *tilemap);
