#include "../include/physics.h"


bool physics_point_aabb_intersect(vec2_t point, aabb_t box) {
    vec2_t min = vec2_sub(box.position, box.half_size);
    vec2_t max = vec2_add(box.position, box.half_size);

    if ((point.x > min.x && point.x < max.x) && (point.y > min.y && point.y < max.y)) {
        return true;
    }

    return false;
}

bool physics_aabb_aabb_intersect(aabb_t box_a, aabb_t box_b) {

}

physics_state_t *init_physics_state(void (*collision_cb_func)(body_t *self, body_t *other), void (*static_collision_cb_func)(body_t *self, static_body_t *static_body)) { 
    physics_state_t *state = (physics_state_t*)malloc(sizeof(physics_state_t));

    state->body_collision_callback_func = collision_cb_func;
    state->static_body_collision_callback_func = static_collision_cb_func;

    state->static_body_list = array_list_create(sizeof(static_body_t), DEFAULT_INITIAL_CAPACITY);
    state->body_list = array_list_create(sizeof(body_t), DEFAULT_INITIAL_CAPACITY);

    return state;
}

void physics_add_static_body(physics_state_t *state, aabb_t aabb) {
    static_body_t s_body;
    s_body.aabb = aabb;

    array_list_append(state->static_body_list, &s_body);
}

void physics_add_body(physics_state_t *state, body_t *body) {
    array_list_append(state->body_list, body);
}

void physics_update_entities(physics_state_t *state) {

}

void physics_collision_update(physics_state_t *state) {

}

void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect) {
    (*rect).x = aabb.position.x;
    (*rect).y = aabb.position.y; 
    (*rect).w = aabb.half_size.x * 2;
    (*rect).h = aabb.half_size.x * 2;
}

void dbg_print_static_body(void *data) {
    static_body_t *body_data = (static_body_t*)data;
    
    printf("\nBODY DATA:\n");
    printf("Position: [%f, %f]\n", body_data->aabb.position.x, body_data->aabb.position.y);
    printf("Half-Size: [%f, %f]\n\n", body_data->aabb.half_size.x, body_data->aabb.half_size.y);
}

void dbg_print_physics_state(physics_state_t *state) {
    printf("Static Body List:\n");
    dbg_print_array_list(state->static_body_list, dbg_print_static_body);
}