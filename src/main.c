#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../include/game.h"
#include "../include/utils.h"
#include "../include/input.h"
#include "../include/renderer.h"
#include "../include/physics.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


//MAIN LOOP
int main(int argument_counter, char **arguments) {
    game_state_t *state = init_game(SCREEN_WIDTH, SCREEN_HEIGHT, 120);
    

    state->tilemap = create_base_tilemap(floors, walls, MAP_WIDTH, MAP_HEIGTH, TILE_SIZE, state->physics_state);

    state->player = create_player(40, 300.0, 300.0, COLOR_YELLOW);

    physics_add_body(state->physics_state, &(state->player->body));
    
    dbg_print_physics_state(state->physics_state);

    aabb_t test_aabb = {
        .position = (vec2_t){300, 300},
        .half_size = (vec2_t){50, 50}
    };

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
        process_key_presses(&state->input->keys, state->player, 0);
        update_player_movement(state->player, state->clock->dt);
        physics_collision_update(state->physics_state);

        //Rendering
        clear_render(state->renderer, get_color(COLOR_DARK_GRAY));

        if (physics_point_aabb_intersect(state->input->mouse.position, test_aabb)) {
            render_aabb(state->renderer, test_aabb, get_color(COLOR_RED));
        }
        else {
            render_aabb(state->renderer, test_aabb, get_color(COLOR_GRAY));
        }
        render_quad(state->renderer, state->input->mouse.position, 10, COLOR_RED);
        render_tilemap(state->renderer, state->tilemap);
        t_render_player(state->player, state->renderer);
        SDL_RenderPresent(state->renderer);

        //ENFORCE FRAME RATE
        enforce_frame_time(state->clock);
    }
}