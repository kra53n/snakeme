#include <stdio.h>

#include "game.h"
#include "field.h"

int Game_init(Game* game)
{
	int status;

	if (status = SDL_Init(SDL_INIT_EVERYTHING))
	{
		return status;
	}

	game->win = SDL_CreateWindow(
		GAME_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		GAME_WIDTH,
		GAME_HEIGHT,
		0
	);
	if (!game->win) return 1;

	game->rer = SDL_CreateRenderer(game->win, -1, 0);
	if (!game->rer) return 1;

	game->run = 1;
	Game_init_field(game);
	game->cell_offset = game->field.cell_size / 8;

	return 0;
}

int Game_uninit(Game* game)
{
	SDL_DestroyWindow(game->win);
	SDL_Quit();
	return 0;
}

int Game_process_events(Game* game)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT: Game_uninit(game); break;
		}
		Game_draw_field(game, 0, 0, GAME_WIDTH, GAME_HEIGHT);
		SDL_RenderPresent(game->rer);
	}
}

int Game_run(Game* game)
{
	while (game->run)
	{
		SDL_UpdateWindowSurface(game->win);
		Game_process_events(game);
	}
	Game_uninit(game);
	return 0;
}
