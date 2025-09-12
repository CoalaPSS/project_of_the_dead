#pragma once

#include <SDL2/SDL.h>
// #include "player"
#include "types.h"
#include "arraylist.h"
#include "physics.h"

#define COLOR_CHART_SIZE 255

enum COLOR_ID {
    COLOR_EMPTY = 0,
    COLOR_WHITE,
    COLOR_OFFWHITE,
    COLOR_BLACK,
    COLOR_DARK_GRAY,
    COLOR_GRAY,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_MOSS_GREEN,
    COLOR_DARK_GREEN,
    COLOR_RED,
    COLOR_YELLOW,
    COLOR_WOOD_YELLOW,
    COLOR_BROWN
};

extern color_t color_chart[];

void clear_render(SDL_Renderer *renderer, color_t color);
void set_render_color(SDL_Renderer *renderer, color_t color);
void render_quad(SDL_Renderer *renderer, vec2_t position, u32 size, u8 color_id);
void render_aabb(SDL_Renderer *renderer, aabb_t box, u8 color_id);
void render_aabb_list(SDL_Renderer *renderer, array_list_t *aabb_list, u8 color_id);
void render_body_list(SDL_Renderer *renderer, array_list_t *body_list, u8 color_id);

void init_color_chart();
color_t get_color(enum COLOR_ID color_id);