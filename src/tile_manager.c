#include "../include/tile_manager.h"

const u16 ground_tiles[MAP_WIDTH * MAP_HEIGTH] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

const u16 object_tiles[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 5, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 5, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

tileinfo_t *create_tileinfo_table() {
    tileinfo_t *tileinfo_table = (tileinfo_t*)malloc(TILEINFO_TABLE_SIZE * sizeof(tileinfo_t));

    tileinfo_table[TILE_GRASS_ID] = (tileinfo_t){true, 0.0, 0, 0, COLOR_MOSS_GREEN};
    tileinfo_table[TILE_DIRT_ID] = (tileinfo_t){true, 0.5, 0, 0, COLOR_BROWN};
    tileinfo_table[TILE_BUSH_ID] = (tileinfo_t){false, 0.0, 0, 0, COLOR_GREEN};
    tileinfo_table[TILE_TREE_ID] = (tileinfo_t){true, 0.0, 0, 0, COLOR_DARK_GREEN};
    tileinfo_table[TILE_STONE_PATH_ID] = (tileinfo_t){true, 2.5, 0, 0, COLOR_GRAY};
    tileinfo_table[TILE_STONE_WALL_ID] = (tileinfo_t){true, 0.0, 0, 0, COLOR_DARK_GRAY};
    tileinfo_table[TILE_GRASS_ID] = (tileinfo_t){true, 0.0, 0, 0, COLOR_WOOD_YELLOW};
    tileinfo_table[TILE_RED_BOX] = (tileinfo_t){true, 0.0, 10, 0, COLOR_RED};

    return tileinfo_table;
}


vec2_t absolute_pos(u32 x, u32 y, u32 size) {
    vec2_t position = (vec2_t){(f32)x, (f32)y};
    
    position = vec2_add(position, (vec2_t){(f32)size/2.0, (f32)size/2.0});

    return position;
}

tilemap_t *create_base_tilemap(const u16 *ground_tiles, const u16 *object_tiles, u32 width, u32 height, u32 tile_size) {
    tilemap_t *tilemap = (tilemap_t*)malloc(sizeof(tilemap_t));

    tilemap->width = width;
    tilemap->height = height;
    tilemap->layer_count = 2;
    tilemap->tile_size = tile_size;
    tilemap->layers = (u16**)malloc(tilemap->layer_count * sizeof(u16*));

    tilemap->layers[LAYER_GROUND] = (u16*)malloc((width * height) * sizeof(u16));
    tilemap->layers[LAYER_OBJECT] = (u16*)malloc((width * height) * sizeof(u16));

    tilemap->tileinfo_table = create_tileinfo_table();

    int index;

    //Ground layer
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = (y * width) + x;
            tilemap->layers[LAYER_GROUND][index] = ground_tiles[index];
        }
    }

    //Object layer
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = (y * width) + x;
            tilemap->layers[LAYER_OBJECT][index] = object_tiles[index];
        }
    }

    return tilemap;
}

void set_tile(tilemap_t *tilemap, int x, int y, u16 id, int layer) {
    if ((layer <= tilemap->layer_count) && (x < tilemap->width) && (y < tilemap->height)) {
        int index = (y * tilemap->width) + x;
        tilemap->layers[layer][index] = id;
    }
}

void render_tilemap(SDL_Renderer *renderer, tilemap_t *tilemap) {
    vec2_t render_pos;
    vec2_t tile_hs = vec2_from_int(tilemap->tile_size, 0.5);
    
    SDL_Rect rect;
    int index;

    rect.w = tilemap->tile_size;
    rect.h = tilemap->tile_size;

    //Draw ground layer

    for (int y = 0; y < tilemap->height; y++) {
        for (int x = 0; x < tilemap->width; x++) {

            index = (y * tilemap->width) + x;

            u16 id = tilemap->layers[LAYER_GROUND][index];

            if (id != TILE_EMPTY) {
                color_t color = get_color((tilemap->tileinfo_table[id]).debug_color_id);

                rect.x = x * tilemap->tile_size;
                rect.y = y * tilemap->tile_size;
                set_render_color(renderer, color);
                SDL_RenderFillRect(renderer, &rect);
            }
                
        }
    }
    // Draw object layer
    for (int y = 0; y < tilemap->height; y++) {
        for (int x = 0; x < tilemap->width; x++) {

            index = (y * tilemap->width) + x;

            u16 id = tilemap->layers[LAYER_OBJECT][index];

            if (id != TILE_EMPTY) {
                color_t color = get_color((tilemap->tileinfo_table[id]).debug_color_id);

                rect.x = x * tilemap->tile_size;
                rect.y = y * tilemap->tile_size;
                set_render_color(renderer, color);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}