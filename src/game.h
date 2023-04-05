#pragma once

#include <SDL.h>

#include "field.h"
#include "snake.h"

#define GAME_TITLE  "snakeme | snake game"
#define GAME_WIDTH  1280
#define GAME_HEIGHT 720

typedef struct
{
	SDL_Window*   win;
	SDL_Surface*  surf;
	SDL_Renderer* rer;
	int           run;
	int           cell_size;
	int           cell_offset;
	Field         field;
	Snake         snake;

} Game;

int Game_init(Game* game);
int Game_run(Game* game);