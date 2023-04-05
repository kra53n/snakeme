#pragma once

#include <SDL.h>

#include "color.h"

enum SNAKE_DIRECTION
{
	SNAKE_UP, SNAKE_DOWN, SNAKE_LEFT, SNAKE_RIGHT
};

typedef struct
{
	SDL_Point head;
	Color     color1; // color of head
	Color     color2; // color of body
	Color     color3; // snake shadow
	int       up;
	int       down;
	int       left;
	int       right;
	int       direction;
	int       last_update;
} Snake;

typedef struct Game Game_1;

void Game_init_snake(Game_1* game);
void Game_draw_snake(Game_1* game);
void Game_give_snake_direction(Game_1* game, int scancode);
void Game_move_snake(Game_1* game);