#pragma once

#include <SDL.h>

#include "field.h"

#define GAME_TITLE  "snakeme | snake game"
#define GAME_WIDTH  1280
#define GAME_HEIGHT 720

typedef struct
{
	SDL_Window*   win;
	SDL_Surface*  surf;
	SDL_Renderer* rer;
	int           run;
	Field         field;
	int           cell_offset;
} Game;

int Game_init(Game* game);
int Game_run(Game* game);