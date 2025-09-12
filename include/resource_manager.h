#pragma once

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "types.h"

enum TEXTURE_ATLAS_CATEGORY {
    ATLAS_TILEMAP,
    ATLAS_PLAYER,
    ATLAS_ENEMY,
    ATLAS_DOOR,
    ATLAS_CHEST
};

typedef struct _texture_atlas {
    u32 grid_size;
    u32 texture_size;
    SDL_Texture *atlas;
} texture_atlas_t;

typedef struct _texture_table {
    texture_atlas_t tilemap_atlas;
    texture_atlas_t *object_atlas_list;
    int object_atlas_count;
} texture_table_t;

texture_table_t *create_texture_table(int object_atlas_count);
void init_texture_table(SDL_Renderer *renderer, texture_table_t *table);
void get_src_texture_from_id(texture_atlas_t *atlas, SDL_Rect *src_rect, int offset);