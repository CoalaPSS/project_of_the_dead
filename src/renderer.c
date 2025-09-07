#include "../include/renderer.h"

void set_render_color(SDL_Renderer *renderer, color_t color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void clear_render(SDL_Renderer *renderer, color_t color) {
    set_render_color(renderer, color);
    SDL_RenderClear(renderer);
}

void render_world_objects(SDL_Renderer *renderer, world_objects_t *world_objs) {
    vec2_t render_pos;
    static_object_t *obj;
    SDL_Rect rect;

    //Draw floors

    for (int i = 0; i < world_objs->floors->lenght; i++) {
        obj = (static_object_t*)array_list_get(world_objs->floors, i);
        // printf("FLOOR TILE %d:", i);
        // print_object(obj);
        aabb_to_sdl_rect(obj->aabb, &rect);
        set_render_color(renderer, tile_color_table[obj->color_id]);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Draw walls

    for (int i = 0; i < world_objs->walls->lenght; i++) {
        obj = (static_object_t*)array_list_get(world_objs->walls, i);        
        aabb_to_sdl_rect(obj->aabb, &rect);
        set_render_color(renderer, tile_color_table[obj->color_id]);
        SDL_RenderDrawRect(renderer, &rect);
    }
    // ERROR_RETURN(1, "Debug exit");
}