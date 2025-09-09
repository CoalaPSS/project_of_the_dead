#include "../include/tile_manager.h"

const u8 floors[MAP_WIDTH * MAP_HEIGTH] = {0};

const u8 walls[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 4, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

vec2_t absolute_pos(vec2_t relative_pos, vec2_t half_size) {
    vec2_t position;
    
    position = vec2_mult(relative_pos, TILE_SIZE);
    position = vec2_add(position, half_size);

    return position;
}

tilemap_t *create_base_tilemap(const u8 *floor_tiles, const u8 *wall_tiles, u32 width, u32 height, u32 tile_size, physics_state_t *p_state) {
    tilemap_t *tilemap = (tilemap_t*)malloc(sizeof(tilemap_t));

    tilemap->floors = array_list_create(sizeof(tile_t), DEFAULT_INITIAL_CAPACITY);
    tilemap->walls = array_list_create(sizeof(tile_t), DEFAULT_INITIAL_CAPACITY);

    u32 x, y, index;

    tile_t temp_tile;
    temp_tile.body.aabb.half_size = (vec2_t){(f32)tile_size/2.0, (f32)tile_size/2.0};

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            temp_tile.body.aabb.position = absolute_pos((vec2_t){x, y}, temp_tile.body.aabb.half_size);
            index = (y * width) + x;

            //Floors
            temp_tile.color_id = floor_tiles[index];
            array_list_append(tilemap->floors, &temp_tile);

            //Walls
            temp_tile.color_id = wall_tiles[index];

            if (temp_tile.color_id > 0) {
                array_list_append(tilemap->walls, &temp_tile);
                physics_add_static_body(p_state, &temp_tile.body);
            }

        }
    }

    return tilemap;
}

void render_tilemap(SDL_Renderer *renderer, tilemap_t *tilemap) {
    vec2_t render_pos;
    tile_t *obj;
    SDL_Rect rect;

    //Draw floors

    for (int i = 0; i < tilemap->floors->lenght; i++) {
        obj = (tile_t*)array_list_get(tilemap->floors, i);

        aabb_to_sdl_rect(obj->body.aabb, &rect);
        set_render_color(renderer, get_color(obj->color_id));
        SDL_RenderFillRect(renderer, &rect);
    }

    //Draw walls

    for (int i = 0; i < tilemap->walls->lenght; i++) {
        obj = (tile_t*)array_list_get(tilemap->walls, i);        
        aabb_to_sdl_rect(obj->body.aabb, &rect);
        set_render_color(renderer, get_color(obj->color_id));
        SDL_RenderDrawRect(renderer, &rect);
    }
    // ERROR_RETURN(1, "Debug exit");
}