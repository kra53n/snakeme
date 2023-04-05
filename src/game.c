#include "game.h"

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
	game->run = 1;
	return 0;
}

int Game_uninit(Game* game)
{
	SDL_FreeSurface(game->surf);
	SDL_DestroyWindow(game->win);
	SDL_Quit();
	return 0;
}

int Game_run(Game* game)
{
	while (game->run)
	{
		SDL_UpdateWindowSurface(game->win);
	}
	Game_uninit(game);
	return 0;
}
