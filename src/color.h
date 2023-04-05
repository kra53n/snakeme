#pragma once

#include <SDL.h>

typedef struct
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
} Color;

#define give_color(c) c.r, c.g, c.b, 255
