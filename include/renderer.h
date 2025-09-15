#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

typedef struct _viewport viewport_t;
typedef struct _texture_sheet texture_sheet_t;
typedef struct _render_state render_state_t;

struct _viewport {
    vec2_t position;
    u32 width;
    u32 height;
};

struct _texture_sheet {
    SDL_Texture *texture;
    int frame_size;
    int cols;
    int rows;
};

struct _render_state {
    SDL_Renderer *renderer;
    viewport_t viewport;
};

extern color_t color_chart[];
extern render_state_t g_render_state;

void render_init(SDL_Renderer *renderer, const u32 screen_width, const u32 screen_height);
void update_camera(vec2_t position);
void clear_render(color_t color);
void set_render_color(color_t color);
void render_quad(vec2_t position, u32 size, u8 color_id);
void render_aabb(aabb_t *box, u8 color_id);
void render_aabb_list(array_list_t *aabb_list, u8 color_id);
void render_body_list(array_list_t *body_list, u8 color_id);
void render_texture_frame(texture_sheet_t *sheet, u32 x, u32 y, int id, u32 dst_size);
texture_sheet_t *render_load_texture_sheet(char *path, u32 frame_size, int width, int height);

void init_color_chart();
color_t get_color(enum COLOR_ID color_id);