#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "arraylist.h"
#include "physics.h"

#define MAP_WIDTH 32
#define MAP_HEIGTH 18
#define TILE_SIZE 60

#define MAX_TILE_COLOR_TYPES 255

// extern const u8 world_tiles[];
extern const u8 floors[];
extern const u8 walls[];


enum TILE_TYPE {
    TILE_COLOR_EMPTY = 0,
    TILE_COLOR_GRAY_FLOOR,
    TILE_COLOR_BLUE_FLOOR,
    TILE_COLOR_DARK_GREEN_FLOOR,
    TILE_COLOR_RED_WALL,
    TILE_COLOR_YELLOW_WALL
};

// typedef struct _tile_type_table {
//     color_t color;
//     SDL_Texture *texture;
// }
extern color_t tile_color_table[];

typedef struct _static_object {
    aabb_t aabb;
    u8 color_id;
} static_object_t;

typedef struct _world_objects {
    array_list_t *floors;
    array_list_t *walls;
    // array_list_t *objects;
} world_objects_t;

void init_tile_color_table(color_t *table);
world_objects_t *init_world_objects(physics_state_t *physics_state, const u8 *floor_tiles, const u8 *wall_tiles, int width, int height, i32 tile_size);


void print_object(static_object_t *obj);
// typedef struct _tile {
//     float x;
//     float y;
//     int type;
// } tile_t;

// typedef struct _world_tilemap {
//     int width;
//     int height;
//     int tile_size;

//     tile_t *tiles;
// } world_tilemap_t;

// world_tilemap_t *create_world_tilemap(const u8 *tile_coordinates, int w, int h, int tile_size);
// const tile_t *load_world_map_file(char *map_file);
// void print_tilemap(world_tilemap_t *tilemap);