#pragma once

#include "types.h"
#include "utils.h"
#include <SDL2/SDL.h>

#define WALK_SPEED 180

typedef struct _player {
    vec2_t dimensions;
    vec2_t position;
    vec2_t velocity;

    SDL_Texture *sprite_texture;
    color_t temp_color;
} player_t;

void init_player(player_t *player, vec2_t dimensions, vec2_t init_position, color_t color);