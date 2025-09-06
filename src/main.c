#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../include/game.h"
#include "../include/utils.h"
#include "../include/keyboard.h"
#include "../include/player.h"


#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720


// #define RGB_TO_INT(r, g, b) ((int)((255 & 0xFF) | (((b) & 0xFF) << 8) | (((g) & 0xFF) << 16) | (((r) & 0xFF) << 24)))

#define BACKGROUND_COLOR (color_t){50, 50, 50}
#define PLAYER_COLOR (color_t){250, 50, 50}

//MAIN LOOP
int main(int argument_counter, char **arguments) {
    core_game_t *game_inst = init_game(1080, 720, 60);
    SDL_Event event;

    //INIT WORLD AND PLAYER
    player_t player;
    init_player(&player, (vec2_t){30, 30}, (vec2_t){500, 300}, PLAYER_COLOR);
    world_tilemap_t *world_tilemap = create_world_tilemap(world_tiles, 16, 16, 40);

    
    while (game_inst->running) {
        get_tick(game_inst->clock);

        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN:
                handle_key_press(event.key.keysym.scancode, game_inst->key_states, KEY_DOWN);
                break;
            case SDL_KEYUP:
                handle_key_press(event.key.keysym.scancode, game_inst->key_states, KEY_UP);
                break;
            case SDL_QUIT:
                game_inst->running = false;
                break;
            default:
                // printf("Unknown event type.\n");
        }

        process_key_presses(game_inst->key_states, &player, 0);
        update_player_movement(&player, game_inst->clock->dt);
        set_background_color(game_inst->renderer, BACKGROUND_COLOR);
        draw_tiles(world_tilemap, game_inst->renderer);
        draw_player(&player, game_inst->renderer);
        SDL_RenderPresent(game_inst->renderer);

        //ENFORCE FRAME RATE
        enforce_frame_time(game_inst->clock);
    }
}