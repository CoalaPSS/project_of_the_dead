#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../include/game.h"
#include "../include/utils.h"
#include "../include/input.h"
#include "../include/renderer.h"
#include "../include/physics.h"



//MAIN LOOP
int main(int argument_counter, char **arguments) {
    game_state_t *state = init_game(SCREEN_WIDTH, SCREEN_HEIGHT, 120);
    

    state->tilemap = tilemap_create(state->renderer, MAP_WIDTH, MAP_HEIGTH, TILE_SIZE, 3);
    tilemap_load_layer(state->tilemap, ground_tiles, sizeof(ground_tiles), LAYER_GROUND);
    tilemap_load_layer(state->tilemap, object_tiles, sizeof(object_tiles), LAYER_OBJECT);
    tilemap_get_collision_list(state->physics_state, state->tilemap, LAYER_OBJECT);

    player_t *player = create_player(24, 300.0, 300.0, COLOR_YELLOW);

    physics_add_body(state->physics_state, &(player->body));

    array_list_t *aabb_collision_list = array_list_create(sizeof(aabb_t), DEFAULT_INITIAL_CAPACITY);

    texture_sheet_t *tilemap_texture_sheet = render_load_texture_sheet(state->renderer, "assets/tilemap_atlas.png", 32, 128, 128);
    

    SDL_Event event;
    
    while (state->running) {
        get_tick(state->clock);

        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN:
                update_keys_state(state->input, event.key.keysym.scancode, KEY_DOWN);
                break;
            case SDL_KEYUP:
                update_keys_state(state->input, event.key.keysym.scancode, KEY_UP);
                break;
            case SDL_MOUSEMOTION:
                update_mouse_state(state->input);
                break;

            case SDL_QUIT:
                state->running = false;
                break;
            default:
                // printf("Unknown event type.\n");
        }

        SDL_ShowCursor(SDL_DISABLE);
        process_key_presses(&state->input->keys, player, 0);
        physics_update(state->physics_state, state->clock->dt, PLAYER_SPEED, aabb_collision_list);

        //Rendering
        clear_render(state->renderer, get_color(COLOR_DARK_GRAY));
        render_tilemap(state->renderer, state->tilemap, tilemap_texture_sheet);
        // render_aabb_list(state->renderer, state->physics_state->tile_aabb_list, COLOR_OFFWHITE);
        t_render_player(player, state->renderer);
        // render_body_list(state->renderer, state->physics_state->body_list, COLOR_WHITE);
        render_aabb_list(state->renderer, aabb_collision_list, COLOR_RED);  
        
        array_list_clear(aabb_collision_list);

        SDL_RenderPresent(state->renderer);

        //ENFORCE FRAME RATE
        enforce_frame_time(state->clock);
    }
}