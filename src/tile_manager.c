#include "../include/tile_manager.h"

const u8 floors[MAP_WIDTH * MAP_HEIGTH] = {0};

const u8 walls[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 5, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 5, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

tile_type_t tile_type_table[TILE_TABLE_SIZE];

void init_ttt() {
    tile_type_table[TILE_GRASS] = (tile_type_t){TILE_GRASS, COLOR_MOSS_GREEN};
    tile_type_table[TILE_DIRT] = (tile_type_t){TILE_DIRT, COLOR_BROWN};
    tile_type_table[TILE_BUSH] = (tile_type_t){TILE_BUSH, COLOR_GREEN};
    tile_type_table[TILE_TREE] = (tile_type_t){TILE_TREE, COLOR_DARK_GREEN};
    tile_type_table[TILE_STONE_PATH] = (tile_type_t){TILE_STONE_PATH, COLOR_GRAY};
    tile_type_table[TILE_STONE_WALL] = (tile_type_t){TILE_STONE_WALL, COLOR_DARK_GRAY};
    tile_type_table[TILE_BOX] = (tile_type_t){TILE_BOX, COLOR_WOOD_YELLOW};
}

vec2_t absolute_pos(u32 x, u32 y, u32 size) {
    vec2_t position = (vec2_t){(f32)x, (f32)y};
    
    position = vec2_add(position, (vec2_t){(f32)size/2.0, (f32)size/2.0});

    return position;
}

u8 get_tile_color(i32 id) {
    tile_type_t tt = tile_type_table[id];
    return tt.color_id;
}

tilemap_t *create_base_tilemap(const u8 *floor_tiles, const u8 *wall_tiles, u32 width, u32 height, u32 tile_size, physics_state_t *p_state) {
    init_ttt();

    tilemap_t *tilemap = (tilemap_t*)malloc(sizeof(tilemap_t));

    tilemap->tile_size = tile_size;
    tilemap->floors = array_list_create(sizeof(tile_t), DEFAULT_INITIAL_CAPACITY);
    tilemap->walls = array_list_create(sizeof(tile_t), DEFAULT_INITIAL_CAPACITY);
    //TODO: Implement tileects later

    u32 x, y, index;
    tile_t tile;

    aabb_t tile_aabb;
    tile_aabb.half_size = vec2_from_int(tile_size, 0.5);

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            index = (y * width) + x;

            //Floors
            tile.id = floor_tiles[index];
            tile.color_id = get_tile_color(tile.id);
            tile.position = vec2_mult((vec2_t){(f32)x, (f32)y}, (f32)tilemap->tile_size);
            tile.solid = false;
            array_list_append(tilemap->floors, &tile);

            //Walls
            tile.id = wall_tiles[index];
            if (tile.id) {
                tile.color_id = get_tile_color(tile.id);
                tile.solid = true;
                array_list_append(tilemap->walls, &tile);

                tile_aabb.position = vec2_add(tile.position, tile_aabb.half_size);

                array_list_append(p_state->tile_list, &tile_aabb);
            } 
        }
    }
    return tilemap;
}


void render_tilemap(SDL_Renderer *renderer, tilemap_t *tilemap) {
    vec2_t render_pos;
    vec2_t tile_hs = vec2_from_int(tilemap->tile_size, 0.5);
    
    tile_t *tile;
    SDL_Rect rect;

    //Draw floors

    for (int i = 0; i < tilemap->floors->lenght; i++) {
        tile = (tile_t*)array_list_get(tilemap->floors, i);

        rect.x = (u32)tile->position.x;
        rect.y = (u32)tile->position.y;
        rect.w = tilemap->tile_size;
        rect.h = tilemap->tile_size;

        set_render_color(renderer, get_color(tile->color_id));
        SDL_RenderFillRect(renderer, &rect);
    }

    //Draw walls

    for (int i = 0; i < tilemap->walls->lenght; i++) {
        tile = (tile_t*)array_list_get(tilemap->walls, i);

        rect.x = (u32)tile->position.x;
        rect.y = (u32)tile->position.y;
        rect.w = tilemap->tile_size;
        rect.h = tilemap->tile_size;

        set_render_color(renderer, get_color(tile->color_id));
        SDL_RenderFillRect(renderer, &rect);
    }
    // ERROR_RETURN(1, "Debug exit");
}