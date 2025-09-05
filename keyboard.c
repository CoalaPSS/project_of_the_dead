#include "keyboard.h"


// KEYBOARD EVENT SYSTEM


void print_key_states(key_states_t key_states) {
    printf("--KEY STATES--\n");
    printf("\tLEFT KEY: %d\n", key_states.left);
    printf("\tRIGHT KEY: %d\n", key_states.right);
    printf("\tUP KEY: %d\n", key_states.up);
    printf("\tDOWN KEY: %d\n", key_states.down);
    printf("\n");
}

void init_key_states(key_states_t *keys) {
    memset(keys, 0, sizeof(key_states_t));
}

void handle_key_press(SDL_Scancode key_scancode, key_states_t *key_states, bool state) {
    switch (key_scancode) {
        case SDL_SCANCODE_A:
            key_states->left = state;
            break;
        case SDL_SCANCODE_D:
            key_states->right = state;
            break;
        case SDL_SCANCODE_W:
            key_states->up = state;
            break;
        case SDL_SCANCODE_S:
            key_states->down = state;
            break;
    }
}