#include "input.h"

#include <stdio.h>

#include <SDL.h>

void Input_process()
{
	SDL_Event ev;
	static int time = 0;
	while (SDL_PollEvent(&ev))
	{
		printf("(Input_process) %d\n", ++time);
	}
}