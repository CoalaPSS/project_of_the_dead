#include "../include/physics.h"

void dbg_print_body_pos(void *data);
void dbg_print_tile_pos(void *data);

physics_state_t *init_physics_state(body_collision_cb body_cb, tile_collision_cb tile_cb) { 
    physics_state_t *state = (physics_state_t*)malloc(sizeof(physics_state_t));

    state->body_collision_callback = body_cb;
    state->tile_collision_callback = tile_cb;

    state->body_list = array_list_create(sizeof(body_t*), DEFAULT_INITIAL_CAPACITY);
    state->tile_aabb_list = array_list_create(sizeof(aabb_t), DEFAULT_INITIAL_CAPACITY);

    return state;
}

bool physics_point_aabb_intersect(vec2_t point, aabb_t box) {
    vec2_t min = vec2_sub(box.position, box.half_size);
    vec2_t max = vec2_add(box.position, box.half_size);

    if ((point.x > min.x && point.x < max.x) && (point.y > min.y && point.y < max.y)) {
        return true;
    }

    return false;
}

bool physics_aabb_aabb_intersect(aabb_t box_a, aabb_t box_b) {
    f32 dx = fabs(box_a.position.x - box_b.position.x);
    f32 dy = fabs(box_a.position.y - box_b.position.y);

    f32 px = box_a.half_size.x + box_b.half_size.x - dx;
    f32 py = box_a.half_size.y + box_b.half_size.y - dy;

    return (px > 0 && py > 0);
}




void physics_add_body(physics_state_t *state, body_t *body) {
    array_list_append(state->body_list, &body);
}

void physics_collision_update(physics_state_t *state, void *context) {
    //Body x Tile collision
    for (int i = 0; i < state->body_list->lenght; i++) {
        body_t *body = *(body_t**)array_list_get(state->body_list, i);
        

        for (int j = 0; j < state->tile_aabb_list->lenght; j++) {
            aabb_t tile_aabb = *(aabb_t*)array_list_get(state->tile_aabb_list, j);

            if (physics_aabb_aabb_intersect(body->aabb, tile_aabb)) {
                state->tile_collision_callback(body, &tile_aabb, context);
            }
        }
    }
}

void physics_update_entities(physics_state_t *state) {

}



void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect) {
    vec2_t relative_pos = vec2_sub(aabb.position, aabb.half_size);
    vec2_t size = vec2_mult(aabb.half_size, 2.0);

    (*rect).x = relative_pos.x;
    (*rect).y = relative_pos.y; 
    (*rect).w = size.x;
    (*rect).h = size.y;
}

void dbg_print_body_pos(void *data) {
    body_t *body_data = (body_t*)data;

    printf("Position: [%f, %f]\n", body_data->aabb.position.x, body_data->aabb.position.y);
}

void dbg_print_tile_pos(void *data) {
    aabb_t *tile_aabb = (aabb_t*)data;

    printf("Position: [%f, %f]\n", tile_aabb->position.x, tile_aabb->position.y);
}

void dbg_print_physics_state(physics_state_t *state) {
    printf("Body List:\n\n");
    dbg_print_array_list(state->body_list, dbg_print_body_pos);

    printf("\n\n\n");

    printf("Tile AABB List:\n\n");
    dbg_print_array_list(state->tile_aabb_list, dbg_print_tile_pos);
}

