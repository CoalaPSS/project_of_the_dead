#pragma once

#include <SDL2/SDL.h>
// #include "player"
#include "types.h"
#include "arraylist.h"
#include "tile_manager.h"

#define COLOR_CHART_SIZE 255

enum COLOR_ID {
    COLOR_EMPTY = 0,
    COLOR_BLACK,
    COLOR_DARK_GRAY,
    COLOR_GRAY,
    COLOR_BLUE,
    COLOR_DARK_GREEN,
    COLOR_RED,
    COLOR_YELLOW
};

extern color_t color_chart[];

void clear_render(SDL_Renderer *renderer, color_t color);
void set_render_color(SDL_Renderer *renderer, color_t color);
void render_quad(SDL_Renderer *renderer, vec2_t position, u32 size, u8 color_id);
void render_aabb(SDL_Renderer *renderer, aabb_t box, color_t color);

void init_color_chart();
color_t get_color(enum COLOR_ID color_id);