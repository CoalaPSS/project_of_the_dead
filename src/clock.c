#include "../include/clock.h"


clock_t *init_clock(u32 fps) {
    clock_t *new_clock = (clock_t*)malloc(sizeof(clock_t));

    new_clock->target_dt = (1000/fps);
    new_clock->dt = ((f32)1/(f32)fps); 

    new_clock->frame_start = 0;
    new_clock->frame_duration = 0;
    new_clock->last_frame_time = 0;

    return new_clock;
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