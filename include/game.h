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
#define TILE_SIZE 64
#define PLAYER_SPEED 200

extern const u16 ground_tiles[MAP_WIDTH * MAP_HEIGTH];
extern const u16 object_tiles[MAP_WIDTH * MAP_HEIGTH];
typedef struct _game game_t;

struct _game {
    int screen_width;
    int screen_height; 

    clock_t *clock;
    SDL_Window *window;
    input_state_t *input;
    bool running;
};

extern game_t g_state;

void init_game(const int sw, const int sh, const int fps);
void process_key_presses(key_states_t *key_states, body_t *player_body, bool debug_flag);
