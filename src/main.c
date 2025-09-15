#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../include/game.h"
#include "../include/utils.h"
#include "../include/input.h"
#include "../include/renderer.h"
#include "../include/physics.h"

typedef struct _player {
    body_t body;

    SDL_Texture *sprite_texture;
    u8 color_id;
} player_t;

void player_on_hit_static(body_t *player_body, aabb_t *tile_aabb, void *context) {
    array_list_t *aabb_collision_list = (array_list_t*)context;

    array_list_append(aabb_collision_list, tile_aabb);
}

player_t *create_player(u32 size, f32 x_pos, f32 y_pos, u8 color_id) {
    player_t *player = (player_t*)malloc(sizeof(player_t));

    player->body.aabb.half_size = (vec2_t){.x = (f32)size/2.0, .y = (f32)size/2.0};
    player->body.aabb.position = (vec2_t){.x = x_pos, .y = y_pos};
    player->body.velocity = (vec2_t){0};
    player->body.acceleration = (vec2_t){0};
    player->body.entity_id = ID_PLAYER;
    player->body.owner = player;

    player->color_id = color_id;
}

void t_render_player(player_t *player) {
    SDL_Rect rect;

    aabb_to_sdl_rect(player->body.aabb, &rect);

    rect.x -= (g_render_state.viewport.position.x - g_render_state.viewport.width/2);
    rect.y -= (g_render_state.viewport.position.y - g_render_state.viewport.height/2);

    set_render_color(get_color(player->color_id));
    SDL_RenderFillRect(g_render_state.renderer, &rect);
}

//MAIN LOOP
int main(int argument_counter, char **arguments) {
    init_game(SCREEN_WIDTH, SCREEN_HEIGHT, 120);
    

    tilemap_t tilemap;
    tilemap_init(&tilemap, MAP_WIDTH, MAP_HEIGTH, TILE_SIZE, 3);
    tilemap_load_layer(&tilemap, ground_tiles, sizeof(ground_tiles), LAYER_GROUND);
    tilemap_load_layer(&tilemap, object_tiles, sizeof(object_tiles), LAYER_OBJECT);

    player_t *player = create_player(24, 300.0, 300.0, COLOR_YELLOW);
    player->body.on_hit_static = player_on_hit_static;
    tilemap_get_collision_list(&tilemap, LAYER_OBJECT);

    physics_add_body(&(player->body));

    array_list_t *aabb_collision_list = array_list_create(sizeof(aabb_t), DEFAULT_INITIAL_CAPACITY);

    texture_sheet_t *tilemap_texture_sheet = render_load_texture_sheet("assets/tilemap_atlas.png", 32, 128, 128);
    

    SDL_Event event;
    
    while (g_state.running) {
        get_tick(g_state.clock);

        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN:
                update_keys_state(g_state.input, event.key.keysym.scancode, KEY_DOWN);
                break;
            case SDL_KEYUP:
                update_keys_state(g_state.input, event.key.keysym.scancode, KEY_UP);
                break;
            case SDL_MOUSEMOTION:
                update_mouse_state(g_state.input);
                break;

            case SDL_QUIT:
                g_state.running = false;
                break;
            default:
                // printf("Unknown event type.\n");
        }

        SDL_ShowCursor(SDL_DISABLE);
        process_key_presses(&g_state.input->keys, &player->body, 0);
        physics_update(g_state.clock->dt, PLAYER_SPEED, aabb_collision_list);
        // physics_update(g_state.clock->dt, PLAYER_SPEED, NULL);
        

        //Rendering
        update_camera(player->body.aabb.position);
        clear_render(get_color(COLOR_DARK_GRAY));
        render_tilemap(&tilemap, tilemap_texture_sheet);
        t_render_player(player);
        render_aabb_list(aabb_collision_list, COLOR_RED);  
        
        array_list_clear(aabb_collision_list);

        SDL_RenderPresent(g_render_state.renderer);

        //ENFORCE FRAME RATE
        enforce_frame_time(g_state.clock);
    }
}