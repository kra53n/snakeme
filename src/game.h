#pragma once

#include <SDL.h>

#include "field.h"
#include "fruit.h"
#include "snake.h"

#define GAME_TITLE  "snakeme | snake game"
#define GAME_WIDTH  1280
#define GAME_HEIGHT 720

typedef struct
{
	SDL_Window*   win;
	SDL_Renderer* rer;
	int           wait_restarting;
	int           cell_size;
	int           cell_offset;
	Field         field;
	Snake         snake;
	Fruit         fruit;

} Game;

int Game_init(Game* game);
int Game_uninit(Game* game);
int Game_run(Game* game);