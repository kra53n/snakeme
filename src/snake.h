#pragma once

#include <SDL.h>

#include "color.h"

#define DEBUG_SHOW_FPS

enum SNAKE_DIRECTION
{
	SNAKE_UP, SNAKE_DOWN, SNAKE_LEFT, SNAKE_RIGHT
};

typedef struct SnakeBodyElem
{
	SDL_Point             p;
	struct SnakeBodyElem* nxt;
} SnakeBodyElem;

typedef struct Snake
{
	SDL_Point       head;
	SnakeBodyElem*  body;
	Color           color1; // color of head
	Color           color2; // color of body
	Color           color3; // snake shadow
	int             up;
	int             down;
	int             left;
	int             right;
	int             direction;
	int             last_update;
	int             was_increased;
	int             is_died;
} Snake;

typedef struct Game Game_1;

void Game_init_snake(Game_1* game);
void Game_draw_snake(Game_1* game);
void Game_give_snake_direction(Game_1* game, int scancode);
void Game_move_snake(Game_1* game);
void Game_increase_snake(Game_1* game);
void Game_spawn_snake(Game_1* game);