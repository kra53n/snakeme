#include <stdio.h>

#include "game.h"
#include "field.h"
#include "snake.h"

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
	game->cell_size = 40;
	game->cell_offset = game->cell_size / 5;

	Game_init_field(game);
	Game_init_snake(game);

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
		case SDL_KEYDOWN:
		{
			Game_give_snake_direction(game, ev.key.keysym.scancode);
		} break;
		}
	}
}

void Game_update(Game* game)
{
	SDL_UpdateWindowSurface(game->win);
	Game_process_events(game);
	Game_move_snake(game);
}

void Game_draw(Game* game)
{
	Game_draw_field(game, 0, 0, GAME_WIDTH, GAME_HEIGHT);
	Game_draw_snake(game);
	SDL_RenderPresent(game->rer);
}

int Game_run(Game* game)
{
	while (game->run)
	{
		Game_update(game);
		Game_draw(game);
	}
	Game_uninit(game);
	return 0;
}
