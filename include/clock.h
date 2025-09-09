#pragma once

#include <SDL2/SDL.h>
#include "types.h"

typedef struct _clock {
    u32 target_dt;
    u32 frame_start;
    u32 frame_duration;
    u32 last_frame_time;
    f32 dt;
} clock_t;

clock_t *init_clock(u32 fps);
void get_tick(clock_t *clock);
void enforce_frame_time(clock_t *clock);