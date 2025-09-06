#include "../include/game.h"

void init_clock(u32 fps, clock_t *new_clock) {
    new_clock->target_dt = (1000/fps);
    new_clock->dt = ((f32)1/(f32)fps); 

    new_clock->frame_start = 0;
    new_clock->frame_duration = 0;
    new_clock->last_frame_time = 0;
}

void get_tick(clock_t *clock) {
    clock->frame_start = SDL_GetTicks();
}

void enforce_frame_time(clock_t *clock) {
    clock->frame_duration = SDL_GetTicks() - clock->frame_start;
 
    if (clock->target_dt > clock->frame_duration) {
        SDL_Delay(clock->target_dt - clock->frame_duration);
    }
}

void process_key_presses(key_states_t *key_states, player_t *player, bool debug_flag) {
    player->velocity.x = 0;
    player->velocity.y = 0;

    //KEY DOWN
    if (key_states->left == KEY_DOWN) {
        player->velocity.x = -WALK_SPEED;
    }

    if (key_states->right == KEY_DOWN) {
        player->velocity.x = WALK_SPEED;
    }

    if (key_states->up == KEY_DOWN) {
        player->velocity.y = -WALK_SPEED;
    }

    if (key_states->down == KEY_DOWN) {
        player->velocity.y = WALK_SPEED;
    }

    if (debug_flag) {
        print_key_states(*key_states);
    }
}

void update_player_movement(player_t *player, f32 delta_time) {
    f32 df = 0.0;
    if (player->velocity.x && player->velocity.y) df = 0.7;

    printf("Player velocity: (%lf, %lf) | dt: %lf\n", (player->velocity.x * delta_time), (player->velocity.y*delta_time), delta_time);
    player->position.x += player->velocity.x * delta_time;
    player->position.y += player->velocity.y * delta_time;
}

void set_background_color(SDL_Renderer *renderer, color_t color) {
    int r, g, b;
    r = color.r;
    g = color.g;
    b = color.b;

    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
    SDL_RenderClear(renderer);
}

void draw_player(player_t *player, SDL_Renderer *renderer) {
    SDL_Rect p_rect;
    u8 r, g, b, a;
    r = player->temp_color.r;
    g = player->temp_color.g;
    b = player->temp_color.b;
    a = player->temp_color.a;

    p_rect.x = player->position.x;
    p_rect.y = player->position.y;
    p_rect.w = player->dimensions.x;
    p_rect.h = player->dimensions.y;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &p_rect);
}

void draw_tiles(world_tilemap_t *tilemap, SDL_Renderer *renderer) {
    int x, y, id;
    color_t dc;
    tile_t temp_tile;
    SDL_Rect tile_rect = {.w = tilemap->tile_size, .h = tilemap->tile_size};

    for (y = 0; y < tilemap->height; y++) {
        for (x = 0; x < tilemap->height; x++) {
            id = (y * tilemap->width) + x;
            temp_tile = tilemap->tiles[id];

            tile_rect.x = temp_tile.x;
            tile_rect.y = temp_tile.y;

            switch (temp_tile.type) {
                case FLOOR:
                    dc = FLOOR_COLOR;
                    break;
                case WALL:
                    dc = WALL_COLOR;
                    break;
                case BOX:
                    dc = BOX_COLOR;
                    break;
                default:
                    dc = DEFAULT_COLOR;
            }

            SDL_SetRenderDrawColor(renderer, dc.r, dc.g, dc.b, dc.a);
            SDL_RenderFillRect(renderer, &tile_rect);
        }
    }
}

core_game_t *init_game(const int sw, const int sh, const int fps) {
    SDL_Init(SDL_INIT_VIDEO);

    core_game_t *game_instance = (core_game_t *)malloc(sizeof(core_game_t));

    game_instance->window = SDL_CreateWindow("ProtGame-Z", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sw, sh, SDL_WINDOW_SHOWN);
    game_instance->renderer = SDL_CreateRenderer(game_instance->window, -1, SDL_RENDERER_ACCELERATED);

    game_instance->key_states = (key_states_t*)malloc(sizeof(key_states_t));
    game_instance->clock = (clock_t*)malloc(sizeof(clock_t));

    init_clock(fps, game_instance->clock);
    init_key_states(game_instance->key_states);
    
    game_instance->running = true;
}