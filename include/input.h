#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "types.h"

typedef enum KEY_STATE {
    KEY_UP, 
    KEY_DOWN
} KEY_STATE_E;

typedef enum MOUSE_BUTTON_STATE {
    BUTTON_PRESSED,
    BUTTON_UNPRESSED
} MOUSE_BUTTON_STATE_E;

typedef struct _key_states {
    bool left;
    bool right;
    bool up;
    bool down;
    bool space_bar;
} key_states_t;

typedef struct _mouse_state {
    vec2_t position;
    bool left_button;
    bool right_button;
} mouse_state_t;

typedef struct _input_state {
    key_states_t keys;
    mouse_state_t mouse;
} input_state_t;


input_state_t *init_input_state();

void update_mouse_state(input_state_t *input);
void update_keys_state(input_state_t *input, SDL_Scancode key_scancode, KEY_STATE_E state);

void print_key_states(key_states_t key_states);

