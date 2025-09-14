#include "../include/tile_manager.h"



void init_tileinfo_table(SDL_Renderer *renderer, tileinfo_t *table) {
    table[TILE_GRASS_ID] = (tileinfo_t){true, 0.0, 0, 1, COLOR_MOSS_GREEN};
    table[TILE_ROCK_WALL_ID] = (tileinfo_t){true, 0.0, 2, 0, COLOR_DARK_GRAY};
    table[TILE_DIRT_ID] = (tileinfo_t){true, 0.5, 0, 0, COLOR_BROWN};
    table[TILE_BUSH_ID] = (tileinfo_t){false, 0.0, 0, 0, COLOR_GREEN};
    table[TILE_TREE_ID] = (tileinfo_t){true, 0.0, 0, 0, COLOR_DARK_GREEN};
    table[TILE_STONE_PATH_ID] = (tileinfo_t){true, 2.5, 0, 0, COLOR_GRAY};
    table[TILE_STONE_WALL_ID] = (tileinfo_t){true, 0.0, 0, 0, COLOR_DARK_GRAY};
    table[TILE_RED_BOX] = (tileinfo_t){true, 0.0, 10, 0, COLOR_RED};
}


vec2_t absolute_pos(u32 x, u32 y, u32 size) {
    vec2_t position = (vec2_t){(f32)x, (f32)y};
    
    position = vec2_add(position, (vec2_t){(f32)size/2.0, (f32)size/2.0});

    return position;
}

tilemap_t *tilemap_create(SDL_Renderer *renderer, u32 width, u32 height, u32 tile_size, int layer_count) {
    tilemap_t *map = (tilemap_t*)malloc(sizeof(tilemap_t));

    map->width = width;
    map->height = height;
    map->tile_size = tile_size;
    map->layer_count = layer_count;
    map->layers = malloc(sizeof(u16*) * layer_count);
    for (int i = 0; i < layer_count; i++) {
        usize layer_size = width * height * sizeof(u16);
        map->layers[i] = (u16*)malloc(layer_size);
        memset(map->layers[i], 0, layer_size);
    }

    map->tileinfo_table = (tileinfo_t*)malloc((usize)TILEINFO_TABLE_SIZE);
    init_tileinfo_table(renderer, map->tileinfo_table);

    return map;
}

void tilemap_load_layer(tilemap_t *map, const u16 *tiles, usize tile_array_size, int layer_id) {
    if ((map->width * map->height * sizeof(u16)) != tile_array_size) {
        printf("TM_SIZE: %ld , TA_SIZE: %ld\n", (map->width * map->height * sizeof(u16)), tile_array_size);
        printf("TMW: %u, TMH: %u\n", map->width, map->height);
        ERROR_RETURN(1, "Tile Array incompatible with Tile Map");
    }
        

    int index;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            index = (y * map->width) + x;
            map->layers[layer_id][index] = tiles[index];
        }
    }
}

void set_tile(tilemap_t *map, u32 x, u32 y, u16 id, int layer) {
    if ((layer <= map->layer_count) && (x < map->width) && (y < map->height)) {
        int index = (y * map->width) + x;
        map->layers[layer][index] = id;
    }
}

u16 get_tile(tilemap_t *map, u32 x, u32 y, int layer) {
    if ((layer <= map->layer_count) && (x < map->width) && (y < map->height)) {
        int index = (y * map->width) + x;
        return map->layers[layer][index];
    }
}

void tilemap_get_collision_list(physics_state_t *p_state, tilemap_t *map, body_t *pb, int layer) {
    aabb_t tile_aabb;
    tile_aabb.half_size = vec2_from_int(map->tile_size, 0.5);

    u16 id;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {

            id = get_tile(map, x, y, layer);

            if (id == TILE_PLAYER_POS) {
                pb->aabb.position = (vec2_t){(f32)x + map->tile_size/2, (f32)y + map->tile_size/2};
                continue;
            }

            if (map->tileinfo_table[id].solid) {
                vec2_t relative_pos = (vec2_t){(f32)(x * map->tile_size), (f32)(y * map->tile_size)};
                tile_aabb.position = vec2_add(relative_pos, tile_aabb.half_size);

                array_list_append(p_state->tile_aabb_list, &tile_aabb);
            }
        }
    }
}

void render_tilemap(SDL_Renderer *renderer, camera_t *camera, tilemap_t *tilemap, texture_sheet_t *sheet) {
    vec2_t render_pos;
    vec2_t tile_hs = vec2_from_int(tilemap->tile_size, 0.5);
    
    SDL_Rect src_rect, dst_rect;
    int index;

    dst_rect.w = tilemap->tile_size;
    dst_rect.h = tilemap->tile_size;

    //Draw ground layer

    for (int y = 0; y < tilemap->height; y++) {
        for (int x = 0; x < tilemap->width; x++) {

            index = (y * tilemap->width) + x;

            u16 id = tilemap->layers[LAYER_GROUND][index];
            u16 texture_id = tilemap->tileinfo_table[id].texture_id;

            if (id == TILE_EMPTY) continue;

            render_texture_frame(renderer, camera, sheet, (x*tilemap->tile_size), (y*tilemap->tile_size), texture_id, tilemap->tile_size);
        }
    }
    // Draw object layer
    for (int y = 0; y < tilemap->height; y++) {
        for (int x = 0; x < tilemap->width; x++) {

            index = (y * tilemap->width) + x;

            u16 id = tilemap->layers[LAYER_OBJECT][index];

            if (id == TILE_EMPTY) continue;

            render_texture_frame(renderer, camera, sheet, (x*tilemap->tile_size), (y*tilemap->tile_size), id, tilemap->tile_size);
        }
    }
}