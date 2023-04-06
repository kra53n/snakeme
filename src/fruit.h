#pragma once

#include <SDL.h>

enum FRUIT_TYPES
{
	DEFAULT,
	FRUIT_TYPE_SPEED_UP,
	FRUIT_TYPE_SPEED_DOWN,
};

typedef struct Fruit
{
	int       type;
	SDL_Point p;
} Fruit;

typedef struct Game Game_1;

void Game_eat_fruit(Game_1* game);
void Game_spawn_fruit(Game_1* game);
void Game_draw_fruit(Game_1* game);