#include "../include/game.h"

//Declarations
void static_body_collision(body_t *b, static_body_t *sb, void *context);

game_state_t *init_game(const int sw, const int sh, const int fps) {
    SDL_Init(SDL_INIT_VIDEO);

    game_state_t *game_instance = (game_state_t *)malloc(sizeof(game_state_t));

    game_instance->window = SDL_CreateWindow("ProtGame-Z", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sw, sh, SDL_WINDOW_SHOWN);
    game_instance->renderer = SDL_CreateRenderer(game_instance->window, -1, SDL_RENDERER_ACCELERATED);

    game_instance->clock = init_clock(fps);
    game_instance->input = init_input_state();
    game_instance->physics_state = init_physics_state(NULL, static_body_collision);

    init_color_chart();

    game_instance->running = true;
}


void process_key_presses(key_states_t *key_states, player_t *player, bool debug_flag) {
    player->body.velocity.x = 0;
    player->body.velocity.y = 0;

    //KEY DOWN
    if (key_states->left == KEY_DOWN) {
        player->body.velocity.x = -PLAYER_SPEED;
    }

    if (key_states->right == KEY_DOWN) {
        player->body.velocity.x = PLAYER_SPEED;
    }

    if (key_states->up == KEY_DOWN) {
        player->body.velocity.y = -PLAYER_SPEED;
    }

    if (key_states->down == KEY_DOWN) {
        player->body.velocity.y = PLAYER_SPEED;
    }

    if (debug_flag) {
        print_key_states(*key_states);
    }
}

void static_body_collision(body_t *b, static_body_t *sb, void *context) {
    if (b->type_id == BT_PLAYER) {
        SDL_Renderer *renderer = (SDL_Renderer*)context;

        array_list_t *aabb_list = (array_list_t*)context;
        array_list_append(aabb_list, &sb->aabb);
        array_list_append(aabb_list, &b->aabb);
    }
}

player_t *create_player(u32 size, f32 x_pos, f32 y_pos, u8 color_id) {
    player_t *player = (player_t*)malloc(sizeof(player_t));

    player->body.aabb.half_size = (vec2_t){.x = (f32)size/2.0, .y = (f32)size/2.0};
    player->body.aabb.position = (vec2_t){.x = x_pos, .y = y_pos};
    player->body.velocity = (vec2_t){0};
    player->body.acceleration = (vec2_t){0};
    player->body.type_id = BT_PLAYER;
    player->body.owner = player;

    player->color_id = color_id;
}

void update_player_movement(player_t *player, f32 delta_time) {
    f32 df = 0.0;
    if (player->body.velocity.x && player->body.velocity.y) df = 0.7;

    player->body.aabb.position.x += player->body.velocity.x * delta_time;
    player->body.aabb.position.y += player->body.velocity.y * delta_time;
}

void t_render_player(player_t *player, SDL_Renderer *renderer) {
    SDL_Rect rect;

    aabb_to_sdl_rect(player->body.aabb, &rect);

    set_render_color(renderer, get_color(player->color_id));
    SDL_RenderFillRect(renderer, &rect);
}