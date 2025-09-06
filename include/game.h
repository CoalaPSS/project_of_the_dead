#pragma once

#include <SDL2/SDL.h>
#include "types.h"
#include "utils.h"
#include "keyboard.h"
#include "player.h"
#include "tiles.h"

typedef struct _clock {
    u32 target_dt;
    u32 frame_start;
    u32 frame_duration;
    u32 last_frame_time;
    f32 dt;
} clock_t;

typedef struct _game {
    int screen_width, screen_height; 

    clock_t *clock;
    SDL_Window *window;
    SDL_Renderer *renderer;
    key_states_t *key_states;
    bool running;

    player_t *player;
} core_game_t;

core_game_t *init_game(const int sw, const int sh, const int fps);
void get_tick(clock_t *clock);
void enforce_frame_time(clock_t *clock);
void process_key_presses(key_states_t *key_states, player_t *player, bool debug_flag);
void update_player_movement(player_t *player, f32 delta_time);
void set_background_color(SDL_Renderer *renderer, color_t color);
void draw_player(player_t *player, SDL_Renderer *renderer);
void draw_tiles(world_tilemap_t *tilemap, SDL_Renderer *renderer);