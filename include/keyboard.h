#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct _key_states {
    bool left;
    bool right;
    bool up;
    bool down;
} key_states_t;

enum KEY_STATE {
    KEY_UP, 
    KEY_DOWN
};

void init_key_states(key_states_t *keys);
void handle_key_press(SDL_Scancode key_scancode, key_states_t *key_states, bool state);
void print_key_states(key_states_t key_states);

