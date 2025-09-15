#include "../include/renderer.h"

color_t color_chart[COLOR_CHART_SIZE];

void init_color_chart() {
    color_chart[COLOR_WHITE] = (color_t){255, 255, 255};
    color_chart[COLOR_OFFWHITE] = (color_t){200, 200, 200};
    color_chart[COLOR_BLACK] = (color_t){0, 0, 0};
    color_chart[COLOR_DARK_GRAY] = (color_t){40, 40, 40};
    color_chart[COLOR_GRAY] = (color_t){120, 120, 120};
    color_chart[COLOR_BLUE] = (color_t){51, 51, 255};
    color_chart[COLOR_GREEN] = (color_t){0, 200, 0};
    color_chart[COLOR_MOSS_GREEN] = (color_t){76, 150, 0};
    color_chart[COLOR_DARK_GREEN] = (color_t){51, 102, 0};
    color_chart[COLOR_RED] = (color_t){255, 0, 0};
    color_chart[COLOR_WOOD_YELLOW] = (color_t){202, 158, 38};
    color_chart[COLOR_YELLOW] = (color_t){255, 255, 55};
    color_chart[COLOR_BROWN] = (color_t){105, 55, 10};
}

render_state_t g_render_state;

void render_init(SDL_Renderer *renderer, const u32 screen_width, const u32 screen_height) {
    g_render_state.renderer = renderer;
    g_render_state.viewport.width = screen_width;
    g_render_state.viewport.height = screen_height;

    init_color_chart();
}

void update_camera(vec2_t position) {
    g_render_state.viewport.position = position;
}

color_t get_color(enum COLOR_ID color_id) {
    return color_chart[color_id];
}

void set_render_color(color_t color) {
    SDL_SetRenderDrawColor(g_render_state.renderer, color.r, color.g, color.b, color.a);
}

void clear_render(color_t color) {
    set_render_color(color);
    SDL_RenderClear(g_render_state.renderer);
}

void render_aabb(aabb_t *box, u8 color_id) {
    SDL_Rect rect;

    aabb_to_sdl_rect(*(box), &rect);
    rect.x -= (int)(g_render_state.viewport.position.x - g_render_state.viewport.width/2);
    rect.y -= (int)(g_render_state.viewport.position.y - g_render_state.viewport.height/2);

    set_render_color(get_color(color_id));
    SDL_RenderDrawRect(g_render_state.renderer, &rect);
}

void render_aabb_list(array_list_t *aabb_list, u8 color_id) {
    for (int i = 0; i < aabb_list->lenght; i++) {
        aabb_t *aabb = (aabb_t*)array_list_get(aabb_list, i);

        render_aabb(aabb, color_id);
    }
}

void render_body_list(array_list_t *body_list, u8 color_id) {
    for (int i = 0; i < body_list->lenght; i++) {
        body_t *b = *(body_t**)array_list_get(body_list, i);
        // dbg_print_body_pos(b);
        render_aabb(&b->aabb, color_id);
    }
}

void render_quad(vec2_t position, u32 size, u8 color_id) {
    SDL_Rect rect = {
        .x = position.x - (g_render_state.viewport.position.x - g_render_state.viewport.width/2),
        .y = position.y - (g_render_state.viewport.position.y - g_render_state.viewport.height/2),
        .w = size,
        .h = size,
    };
    set_render_color(get_color(color_id));
    SDL_RenderDrawRect(g_render_state.renderer, &rect);
}

void render_texture_frame(texture_sheet_t *sheet, u32 x, u32 y, int id, u32 dst_size) {
    SDL_Rect src, dst;

    src.x = (id % sheet->cols) * sheet->frame_size;
    src.y = (id / sheet->rows) * sheet->frame_size;
    src.w = sheet->frame_size;
    src.h = sheet->frame_size;

    dst.x = x - (g_render_state.viewport.position.x - g_render_state.viewport.width/2);
    dst.y = y - (g_render_state.viewport.position.y - g_render_state.viewport.height/2);
    dst.w = dst_size;
    dst.h = dst_size;

    SDL_RenderCopy(g_render_state.renderer, sheet->texture, &src, &dst);
}

texture_sheet_t *render_load_texture_sheet(char *path, u32 frame_size, int width, int height) {
    texture_sheet_t *sheet = (texture_sheet_t*)malloc(sizeof(texture_sheet_t));
    sheet->texture = IMG_LoadTexture(g_render_state.renderer, path);
    sheet->frame_size = frame_size;
    sheet->cols = width / frame_size;
    sheet->rows = height / frame_size;

    return sheet;
}