#include <SDL.h>
#include <stdlib.h>

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

	c.r = 122; c.g = 122; c.b = 122;
	game->field.borders.color1 = c;

	c.r = 55; c.g = 55; c.b = 55;
	game->field.borders.color2 = c;

	game->field.borders.num = 0;
	game->field.borders.coords = 0;
	if (FIELD_MAX_BORDER_NUM > 0)
	{
		game->field.borders.num = rand() % FIELD_MAX_BORDER_NUM;
		if (FIELD_MAX_BORDER_NUM != 0)
			game->field.borders.coords = (SDL_Point*)malloc(sizeof(SDL_Point) * game->field.borders.num);
		for (int i = 0; i < game->field.borders.num; i++)
		{
			game->field.borders.coords[i].x = rand() % (GAME_WIDTH  / game->cell_size) * game->cell_size;
			game->field.borders.coords[i].y = rand() % (GAME_HEIGHT / game->cell_size) * game->cell_size;
		}
	}
}

void Game_restart_field(Game* game)
{
	game->field.borders.num = 0;
	if (game->field.borders.coords != 0)
		free(game->field.borders.coords);
	if (FIELD_MAX_BORDER_NUM > 0)
	{
		game->field.borders.num = rand() % FIELD_MAX_BORDER_NUM;
		if (FIELD_MAX_BORDER_NUM != 0)
			game->field.borders.coords = (SDL_Point*)malloc(sizeof(SDL_Point) * game->field.borders.num);
		for (int i = 0; i < game->field.borders.num; i++)
		{
			game->field.borders.coords[i].x = rand() % (GAME_WIDTH  / game->cell_size) * game->cell_size;
			game->field.borders.coords[i].y = rand() % (GAME_HEIGHT / game->cell_size) * game->cell_size;
		}
	}
}

void Game_draw_row(Game* game, int x, int y, int w)
{
	SDL_Rect r = { x, y, game->cell_size, game->cell_size };
	for (int i = x / game->cell_size; i <= w / game->cell_size; i++)
	{
		if (i % 2 == 0) continue;
		r.x = x + i * game->cell_size - game->cell_size;
		SDL_RenderFillRect(game->rer, &r);
	}
	SDL_RenderFillRect(game->rer, &r);
}

void Game_draw_cells(Game* game, int x, int y, int w, int h)
{
	for (int j = y / game->cell_size; j <= h / game->cell_size; j++)
	{
		Game_draw_row(
			game,
			((j % 2 == 0) * game->cell_size) + x,
			j * game->cell_size + y,
			w
		);
	}
}

void Game_draw_border(Game* game, int idx, int offset)
{
	SDL_Rect r = {
		game->field.borders.coords[idx].x + offset,
		game->field.borders.coords[idx].y + offset,
		game->cell_size,
		game->cell_size,
	};
	SDL_RenderFillRect(game->rer, &r);
}

void Game_draw_borders(Game* game)
{
	SDL_SetRenderDrawColor(game->rer, give_color(game->field.borders.color2));
	for (int i = 0; i < game->field.borders.num; i++)
	{
		for (int off = 0; off < game->cell_offset; off++) Game_draw_border(game, i, off);
	}
	SDL_SetRenderDrawColor(game->rer, give_color(game->field.borders.color1));
	for (int i = 0; i < game->field.borders.num; i++)
		Game_draw_border(game, i, 0);
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

	Game_draw_borders(game);
}