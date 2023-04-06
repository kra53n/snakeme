#include <stdlib.h>

#include "game.h"
#include "fruit.h"

void Game_spawn_fruit(Game* game)
{
	game->fruit.p.x = rand() % (GAME_WIDTH  / game->cell_size) * game->cell_size;
	game->fruit.p.y = rand() % (GAME_HEIGHT / game->cell_size) * game->cell_size;
	game->fruit.p.x = rand() % (GAME_WIDTH  / game->cell_size) * game->cell_size;

	// TODO: check collision with snake
}

void Game_eat_fruit(Game* game)
{
	if (game->fruit.p.x == game->snake.head.x && game->fruit.p.y == game->snake.head.y)
	{
		Game_spawn_fruit(game);
		Game_increase_snake(game);
	}
}

void Game_draw_fruit(Game* game)
{
	SDL_Rect r = { game->fruit.p.x, game->fruit.p.y, game->cell_size, game->cell_size };
	SDL_SetRenderDrawColor(game->rer, 128, 0, 0, 255);
	for (int i = 0; i < game->cell_offset; i++)
	{
		r.x = game->fruit.p.x + i;
		r.y = game->fruit.p.y + i;
		SDL_RenderFillRect(game->rer, &r);
	}
	SDL_SetRenderDrawColor(game->rer, 255, 0, 0, 255);
	r.x = game->fruit.p.x;
	r.y = game->fruit.p.y;
	SDL_RenderFillRect(game->rer, &r);
}
