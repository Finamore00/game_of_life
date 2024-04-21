#ifndef GAME_OF_LIFE_SDL_UTILS_H

#include <SDL2/SDL.h>
#include "constants.h"

void clear_display(SDL_Renderer *renderer);
void display_grid(SDL_Renderer *renderer, int (*grid)[GRID_WIDTH]);

#define GAME_OF_LIFE_SDL_UTILS_H
#endif