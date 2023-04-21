#pragma once

#include "color.h"

#define FIELD_MAX_BORDER_NUM 4

typedef struct
{
	int   x;
	int   y;
	Color color;
} Cell;

typedef struct
{
	Color      color1; // foreground color
	Color      color2; // shadow color
	SDL_Point* coords;
	int        num;
} Borders;

typedef struct
{
	Color   color1; // foreground color
	Color   color2; // shadow of color1
	Color   color3; // background color
	Borders borders;
} Field;

typedef struct Game Game_1;

void Game_init_field(Game_1* game);
void Game_draw_field(Game_1* game, int x, int y, int w, int h);