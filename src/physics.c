#include "../include/physics.h"

void aabb_to_sdl_rect(aabb_t aabb, SDL_Rect *rect) {
    vec2_t relative_pos = vec2_sub(aabb.position, aabb.half_size);
    vec2_t size = vec2_mult(aabb.half_size, 2.0);

    (*rect).x = relative_pos.x;
    (*rect).y = relative_pos.y; 
    (*rect).w = size.x;
    (*rect).h = size.y;
}

void aabb_min_max(vec2_t *min, vec2_t *max, aabb_t aabb) {
    *(min) = vec2_sub(aabb.position, aabb.half_size);
    *(max) = vec2_add(aabb.position, aabb.half_size);
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

bool aabb_penetration_vector(vec2_t *r, aabb_t box_a, aabb_t box_b) {
    f32 dx = box_a.position.x - box_b.position.x;
    f32 dy = box_a.position.y - box_b.position.y;

    f32 px = box_a.half_size.x + box_b.half_size.x - fabs(dx);
    f32 py = box_a.half_size.y + box_b.half_size.y - fabs(dy);

    if (px < py) {
        if (dx < 0.0) 
            *r = (vec2_t){-px, 0};
        else
            *r = (vec2_t){px, 0};
    }
    else {
        if (dy < 0)
            *r = (vec2_t){0, -py};
        else
            *r = (vec2_t){0, py};
    }

    if (r->x == 0.0 && r->y == 0.0) return false;
    return true;
}


void physics_add_body(physics_state_t *state, body_t *body) {
    array_list_append(state->body_list, &body);
}


void physics_collision_update(physics_state_t *state) {
    collision_event_t col_event;

    for (int i = 0; i < state->body_list->lenght; i++) {
        body_t *body = *(body_t**)array_list_get(state->body_list, i);

        for (int j = 0; j < state->tile_aabb_list->lenght; ++j) {
            aabb_t tile_aabb = *(aabb_t*)array_list_get(state->tile_aabb_list, j);

            if (!physics_aabb_aabb_intersect(body->aabb, tile_aabb)) continue;

            col_event.type = COLLISION_BODY_TILE;
            col_event.body_01 = body;
            col_event.body_02 = NULL;
            col_event.tile_aabb = tile_aabb;
            array_list_append(state->collision_list, &col_event);

            vec2_t mtv;
            if (!aabb_penetration_vector(&mtv, body->aabb, tile_aabb)) continue;

            if (mtv.x != 0.0f) {
                body->aabb.position.x += mtv.x;                
                body->velocity.x = 0.0f;
            }
        }

        for (int j = 0; j < state->tile_aabb_list->lenght; ++j) {
            aabb_t tile_aabb = *(aabb_t*)array_list_get(state->tile_aabb_list, j);

            if (!physics_aabb_aabb_intersect(body->aabb, tile_aabb)) continue;
            vec2_t mtv;
            if (!aabb_penetration_vector(&mtv, body->aabb, tile_aabb)) continue;

            
            if (mtv.y != 0.0f) {
                body->aabb.position.y += mtv.y;
                body->velocity.y = 0.0f;
            }
        }
    }

}

void physics_collision_cb(physics_state_t *state, void *context) {
    for (int i = 0; i < state->collision_list->lenght; i++) {
        collision_event_t event = *(collision_event_t*)array_list_get(state->collision_list, i);

        if (event.type == COLLISION_BODY_TILE) {
            state->tile_collision_callback(event.body_01, event.tile_aabb, context);
        }
    }
    array_list_clear(state->collision_list);
}

void physics_update(physics_state_t *state, f32 dt, f32 speed, void *context) {
    for (int i = 0; i < state->body_list->lenght; i++) {
        body_t *body = *(body_t**)array_list_get(state->body_list, i);

        body->velocity = vec2_normalize(body->velocity);
        body->velocity = vec2_mult(body->velocity, speed);

        body->aabb.position.x += body->velocity.x * dt;
        body->aabb.position.y += body->velocity.y * dt;
    }

    physics_collision_update(state);
    physics_collision_cb(state, context);

}

physics_state_t *init_physics_state(body_collision_cb body_cb, tile_collision_cb tile_cb) { 
    physics_state_t *state = (physics_state_t*)malloc(sizeof(physics_state_t));

    state->body_collision_callback = body_cb;
    state->tile_collision_callback = tile_cb;

    state->body_list = array_list_create(sizeof(body_t*), DEFAULT_INITIAL_CAPACITY);
    state->tile_aabb_list = array_list_create(sizeof(aabb_t), DEFAULT_INITIAL_CAPACITY);
    state->collision_list = array_list_create(sizeof(collision_event_t), COLLISION_LIST_CAPACITY);

    return state;
}

void dbg_print_body_pos(void *data) {
    body_t *body_data = *(body_t**)data;
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


