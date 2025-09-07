#pragma once

#include <SDL2/SDL.h>
// #include "player"
#include "types.h"
#include "arraylist.h"
#include "world_objects.h"


void clear_render(SDL_Renderer *renderer, color_t color);
void set_render_color(SDL_Renderer *renderer, color_t color);
void render_world_objects(SDL_Renderer *renderer, world_objects_t *world_objs);