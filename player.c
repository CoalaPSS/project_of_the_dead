#include "player.h"


void init_player(player_t *player, vec2_t dimensions, vec2_t init_position, color_t color) {
    player->dimensions = dimensions;
    player->position = init_position;
    player->temp_color = color;
}