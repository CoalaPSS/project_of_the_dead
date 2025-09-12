#pragma once

#include <SDL2/SDL.h>
#include "types.h"
#include "utils.h"
#include "input.h"
#include "clock.h"
#include "tile_manager.h"
#include "physics.h"
#include "renderer.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAP_WIDTH 32
#define MAP_HEIGTH 18
#define TILE_SIZE 32
#define PLAYER_SPEED 200

extern const u16 ground_tiles[MAP_WIDTH * MAP_HEIGTH];
extern const u16 object_tiles[MAP_WIDTH * MAP_HEIGTH];

typedef struct _player {
    body_t body;

    SDL_Texture *sprite_texture;
    u8 color_id;
} player_t;

typedef struct _game {
    int screen_width, screen_height; 

    clock_t *clock;
    SDL_Window *window;
    SDL_Renderer *renderer;
    input_state_t *input;
    bool running;

    physics_state_t *physics_state;
    tilemap_t *tilemap;
    texture_table_t *texture_table;
} game_state_t;


game_state_t *init_game(const int sw, const int sh, const int fps);
player_t *create_player(u32 size, f32 x_pos, f32 y_pos, u8 color_id);
void process_key_presses(key_states_t *key_states, player_t *player, bool debug_flag);
void update_player_movement(player_t *player, f32 delta_time);
void t_render_player(player_t *player, SDL_Renderer *renderer);
