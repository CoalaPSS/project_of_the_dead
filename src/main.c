#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../include/game.h"
#include "../include/utils.h"
#include "../include/keyboard.h"
#include "../include/player.h"
#include "../include/renderer.h"


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


#define BACKGROUND_COLOR (color_t){50, 50, 50}
#define PLAYER_COLOR (color_t){0, 200, 0}

//MAIN LOOP
int main(int argument_counter, char **arguments) {
    game_state_t *state = init_game(SCREEN_WIDTH, SCREEN_HEIGHT, 60);
    SDL_Event event;

    //INIT WORLD AND PLAYER
    init_tile_color_table(tile_color_table);
    state->world_objects = init_world_objects(floors, walls, MAP_WIDTH, MAP_HEIGTH, TILE_SIZE);

    player_t player;
    init_player(&player, (vec2_t){30, 30}, (vec2_t){500, 300}, PLAYER_COLOR);
    // world_tilemap_t *world_tilemap = create_world_tilemap(world_tiles, 16, 16, 40);

    
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

        process_key_presses(state->key_states, &player, 0);
        update_player_movement(&player, state->clock->dt);
        
        clear_render(state->renderer, BACKGROUND_COLOR);
        render_world_objects(state->renderer, state->world_objects);
        draw_player(&player, state->renderer);
        SDL_RenderPresent(state->renderer);

        //ENFORCE FRAME RATE
        enforce_frame_time(state->clock);
    }
}