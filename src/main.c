#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../include/game.h"
#include "../include/utils.h"
#include "../include/keyboard.h"
#include "../include/renderer.h"
#include "../include/physics.h"


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


#define BACKGROUND_COLOR (color_t){50, 50, 50}
#define PLAYER_COLOR (color_t){0, 200, 0}

//MAIN LOOP
int main(int argument_counter, char **arguments) {
    game_state_t *state = init_game(SCREEN_WIDTH, SCREEN_HEIGHT, 60);
    SDL_Event event;

    //INIT GAME
    
    
    
    state->physics_state = init_physics_state(NULL, NULL);
    
    state->world_objects = init_world_objects(state->physics_state, floors, walls, MAP_WIDTH, MAP_HEIGTH, TILE_SIZE);
    
    state->player = create_player(40, 300.0, 300.0, TILE_COLOR_YELLOW_WALL);

    physics_add_body(state->physics_state, &(state->player->body));
    dbg_print_physics_state(state->physics_state);

    while (state->running) {
        get_tick(state->clock);

        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN:
                handle_key_press(event.key.keysym.scancode, state->key_states, KEY_DOWN);
                break;
            case SDL_KEYUP:
                handle_key_press(event.key.keysym.scancode, state->key_states, KEY_UP);
                break;
            case SDL_QUIT:
                state->running = false;
                break;
            default:
                // printf("Unknown event type.\n");
        }

        process_key_presses(state->key_states, state->player, 0);
        update_player_movement(state->player, state->clock->dt);
        
        clear_render(state->renderer, BACKGROUND_COLOR);
        render_world_objects(state->renderer, state->world_objects);
        t_render_player(state->player, state->renderer);
        SDL_RenderPresent(state->renderer);

        //ENFORCE FRAME RATE
        enforce_frame_time(state->clock);
    }
}