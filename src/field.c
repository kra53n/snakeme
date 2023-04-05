#include <SDL.h>

#include "game.h"
#include "field.h"
#include "color.h"

void Game_init_field(Game* game)
{
	Color c;

	c.r = 45; c.g = 92; c.b = 86;
	game->field.color1 = c;

	c.r = 31; c.g = 55; c.b = 65;
	game->field.color2 = c;

	c.r = 30; c.g = 32; c.b = 41;
	game->field.color3 = c;

	game->field.cell_size = 40;
}

void Game_draw_row(Game* game, int x, int y, int w)
{
	SDL_Rect r = { x, y, game->field.cell_size, game->field.cell_size };
	for (int i = x / game->field.cell_size; i <= w / game->field.cell_size; i++)
	{
		if (i % 2 == 0) continue;
		r.x = x + i * game->field.cell_size - game->field.cell_size;
		SDL_RenderFillRect(game->rer, &r);
	}
	SDL_RenderFillRect(game->rer, &r);
}

void Game_draw_cells(Game* game, int x, int y, int w, int h)
{
	for (int j = y / game->field.cell_size; j <= h / game->field.cell_size; j++)
	{
		Game_draw_row(
			game,
			((j % 2 == 0) * game->field.cell_size) + x,
			j * game->field.cell_size + y,
			w
		);
	}
}

void Game_draw_field(Game* game, int x, int y, int w, int h)
{
	SDL_SetRenderDrawColor(game->rer, give_color(game->field.color3));
	SDL_RenderClear(game->rer);

	SDL_SetRenderDrawColor(game->rer, give_color(game->field.color2));
	for (int i = 0; i < game->cell_offset; i++)
	{
		Game_draw_cells(game, x + i, y + i, w, h);
	}

	SDL_SetRenderDrawColor(game->rer, give_color(game->field.color1));
	Game_draw_cells(game, x, y, w, h);
}