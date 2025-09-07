#pragma once

#include <SDL2/SDL.h>
#include "types.h"
#include "utils.h"
#include "keyboard.h"
#include "clock.h"
#include "player.h"
#include "world_objects.h"



typedef struct _game {
    int screen_width, screen_height; 

    clock_t *clock;
    SDL_Window *window;
    SDL_Renderer *renderer;
    key_states_t *key_states;
    bool running;

    world_objects_t *world_objects;
    player_t *player;
} game_state_t;


game_state_t *init_game(const int sw, const int sh, const int fps);
void process_key_presses(key_states_t *key_states, player_t *player, bool debug_flag);
void update_player_movement(player_t *player, f32 delta_time);
// void set_background_color(SDL_Renderer *renderer, color_t color);
void draw_player(player_t *player, SDL_Renderer *renderer);
// void draw_tiles(world_tilemap_t *tilemap, SDL_Renderer *renderer);