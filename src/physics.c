#include "../include/physics.h"

physics_state_t g_physics_state;

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


void physics_add_body(body_t *body) {
    array_list_append(g_physics_state.body_list, &body);
}

void physics_collision_update(AXIS axis) {
    collision_event_t col_event;

    for (int i = 0; i < g_physics_state.body_list->lenght; i++) {
        body_t *body = *(body_t**)array_list_get(g_physics_state.body_list, i);

        for (int j = 0; j < g_physics_state.static_body_list->lenght; ++j) {
            aabb_t *static_body = (aabb_t*)array_list_get(g_physics_state.static_body_list, j);

            if (!physics_aabb_aabb_intersect(body->aabb, *(static_body))) continue;

            col_event.type = COLLISION_STATIC_BODY;
            col_event.self = body;
            col_event.other.static_body = static_body;
            array_list_append(g_physics_state.collision_list, &col_event);

            vec2_t penetration_vector = {0, 0};

            aabb_penetration_vector(&penetration_vector, body->aabb, *(static_body));

            if (axis == X_AXIS) {
                body->aabb.position.x += penetration_vector.x;
                body->velocity.x = 0.0;
            }
            
            else if (axis == Y_AXIS) {
                body->aabb.position.y += penetration_vector.y;
                body->velocity.y = 0.0;
            }
        }
    }
}

void physics_collision_cb(void *context) {
    for (int i = 0; i < g_physics_state.collision_list->lenght; i++) {
        collision_event_t event = *(collision_event_t*)array_list_get(g_physics_state.collision_list, i);

        if (event.type == COLLISION_STATIC_BODY) {
            event.self->on_hit_static(event.self, event.other.static_body, context);
        }
        else if (event.type == COLLISION_BODY) {
            event.self->on_hit(event.self, event.other.body, NULL);
        }
    }

    array_list_clear(g_physics_state.collision_list);
}

void physics_update_movement(f32 dt, f32 speed, AXIS axis) {
    for (int i = 0; i < g_physics_state.body_list->lenght; i++) {
    body_t *body = *(body_t**)array_list_get(g_physics_state.body_list, i);

    body->velocity = vec2_normalize(body->velocity);
    body->velocity = vec2_mult(body->velocity, speed);

    if (axis == X_AXIS)
        body->aabb.position.x += body->velocity.x * dt;

    else if (axis == Y_AXIS)
        body->aabb.position.y += body->velocity.y * dt;
    }
}

void physics_update(f32 dt, f32 speed, void *context) {
    physics_update_movement(dt, speed, X_AXIS);
    physics_collision_update(X_AXIS);
    physics_update_movement(dt, speed, Y_AXIS);
    physics_collision_update(Y_AXIS);

    physics_collision_cb(context);
}

void physics_init() { 
    g_physics_state.body_list = array_list_create(sizeof(body_t*), DEFAULT_INITIAL_CAPACITY);
    g_physics_state.static_body_list = array_list_create(sizeof(aabb_t), DEFAULT_INITIAL_CAPACITY);
    g_physics_state.collision_list = array_list_create(sizeof(collision_event_t), COLLISION_LIST_CAPACITY);
}

void dbg_print_body_pos(void *data) {
    body_t *body_data = *(body_t**)data;
    printf("Position: [%f, %f]\n", body_data->aabb.position.x, body_data->aabb.position.y);
}

void dbg_print_tile_pos(void *data) {
    aabb_t *static_body = (aabb_t*)data;

    printf("Position: [%f, %f]\n", static_body->position.x, static_body->position.y);
}

void dbg_print_physics_state() {
    printf("Body List:\n\n");
    dbg_print_array_list(g_physics_state.body_list, dbg_print_body_pos);

    printf("\n\n\n");

    printf("Tile AABB List:\n\n");
    dbg_print_array_list(g_physics_state.static_body_list, dbg_print_tile_pos);
}


