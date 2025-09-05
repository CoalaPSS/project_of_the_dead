#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define FLOOR_COLOR (color_t){125, 115, 75}
#define WALL_COLOR (color_t){0, 200, 0}
#define BOX_COLOR (color_t){230, 200, 30}
#define DEFAULT_COLOR (color_t){0, 0, 0}

extern const u8 world_tiles[];

enum TILE_TYPES {
    FLOOR,
    WALL,
    BOX
};

typedef struct _tile {
    float x;
    float y;
    int type;
} tile_t;

typedef struct _world_tilemap {
    int width;
    int height;
    int tile_size;

    tile_t *tiles;
} world_tilemap_t;

world_tilemap_t *create_world_tilemap(const u8 *tile_coordinates, int w, int h, int tile_size);
const tile_t *load_world_map_file(char *map_file);
void print_tilemap(world_tilemap_t *tilemap);

#endif