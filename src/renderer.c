#include "../include/renderer.h"

color_t color_chart[COLOR_CHART_SIZE];

void init_color_chart() {
    color_chart[COLOR_BLACK] = (color_t){0, 0, 0};
    color_chart[COLOR_DARK_GRAY] = (color_t){40, 40, 40};
    color_chart[COLOR_GRAY] = (color_t){120, 120, 120};
    color_chart[COLOR_BLUE] = (color_t){51, 51, 255};
    color_chart[COLOR_DARK_GREEN] = (color_t){51, 102, 0};
    color_chart[COLOR_RED] = (color_t){255, 0, 0};
    color_chart[COLOR_YELLOW] = (color_t){255, 255, 55};
}

color_t get_color(enum COLOR_ID color_id) {
    return color_chart[color_id];
}

void set_render_color(SDL_Renderer *renderer, color_t color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void clear_render(SDL_Renderer *renderer, color_t color) {
    set_render_color(renderer, color);
    SDL_RenderClear(renderer);
}

void render_aabb(SDL_Renderer *renderer, aabb_t box, color_t color) {
    SDL_Rect rect;

    aabb_to_sdl_rect(box, &rect);
    set_render_color(renderer, color);
    SDL_RenderDrawRect(renderer, &rect);
}

void render_quad(SDL_Renderer *renderer, vec2_t position, u32 size, u8 color_id) {
    SDL_Rect rect = {
        .x = position.x,
        .y = position.y,
        .w = size,
        .h = size,
    };

    set_render_color(renderer, get_color(color_id));
    SDL_RenderDrawRect(renderer, &rect);
}
