#include "../include/input.h"


// KEYBOARD EVENT SYSTEM


void print_key_states(key_states_t key_states) {
    printf("--KEY STATES--\n");
    printf("\tLEFT KEY: %d\n", key_states.left);
    printf("\tRIGHT KEY: %d\n", key_states.right);
    printf("\tUP KEY: %d\n", key_states.up);
    printf("\tDOWN KEY: %d\n", key_states.down);
    printf("\n");
}

input_state_t *init_input_state() {
    input_state_t *input = (input_state_t*)malloc(sizeof(input_state_t));
    input->keys = (key_states_t){0};
    input->mouse = (mouse_state_t){0};

    return input;
}

void update_keys_state(input_state_t *input, SDL_Scancode key_scancode, KEY_STATE_E state) {
    switch (key_scancode) {
        case SDL_SCANCODE_A:
            input->keys.left = state;
            break;
        case SDL_SCANCODE_D:
            input->keys.right = state;
            break;
        case SDL_SCANCODE_W:
            input->keys.up = state;
            break;
        case SDL_SCANCODE_S:
            input->keys.down = state;
            break;
    }
}

void update_mouse_state(input_state_t *input) {
    int x, y;
    u32 buttons = SDL_GetMouseState(&x, &y);
    
    input->mouse.position = (vec2_t){.x = (f32)x, .y = (f32)y};
    input->mouse.left_button = BUTTON_UNPRESSED;
    input->mouse.right_button = BUTTON_UNPRESSED;

    if (buttons && SDL_BUTTON(SDL_BUTTON_LEFT)) {
        input->mouse.left_button = BUTTON_PRESSED;
    }

    if (buttons && SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        input->mouse.right_button = BUTTON_PRESSED;
    }
}