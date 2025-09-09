#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "arraylist.h"
#include "physics.h"
#include "renderer.h"

#define MAP_WIDTH 32
#define MAP_HEIGTH 18
#define TILE_SIZE 60


// extern const u8 world_tiles[];
extern const u8 floors[];
extern const u8 walls[];


typedef struct _static_object {
    aabb_t aabb;
    u8 color_id;
} static_object_t;

typedef struct _tile {
    static_body_t body;
    u8 color_id;
} tile_t;

typedef struct _tilemap {
    array_list_t *floors;
    array_list_t *walls;
    // array_list_t *map_objects;
} tilemap_t;

tilemap_t *create_base_tilemap(const u8 *floor_tiles, const u8 *wall_tiles, u32 width, u32 height, u32 tile_size, physics_state_t *p_state);
void render_tilemap(SDL_Renderer *renderer, tilemap_t *tilemap);
