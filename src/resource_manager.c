#include "../include/resource_manager.h"

texture_table_t *create_texture_table(int object_atlas_count) {
    texture_table_t *table = (texture_table_t*)malloc(sizeof(texture_table_t));

    if (object_atlas_count > 0)
        table->object_atlas_list = (texture_atlas_t*)malloc(sizeof(texture_atlas_t) * object_atlas_count);
    else
        table->object_atlas_list = NULL;

    return table;
}

void init_texture_table(SDL_Renderer *renderer, texture_table_t *table) {
    table->tilemap_atlas.atlas = IMG_LoadTexture(renderer, "assets/tilemap_atlas.png");
    table->tilemap_atlas.grid_size = 4;
    table->tilemap_atlas.texture_size = 32;

}

void get_src_texture_from_id(texture_atlas_t *atlas, SDL_Rect *src_rect, int offset) {
    int row_offset = (offset-1) / atlas->grid_size;
    int col_offset = (offset-1) % atlas->grid_size;

    src_rect->x = col_offset * atlas->texture_size;
    src_rect->y = row_offset * atlas->texture_size;
    src_rect->w = atlas->texture_size;
    src_rect->h = atlas->texture_size;
}