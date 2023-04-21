#include <malloc.h>

#include "game.h"
#include "snake.h"

void Game_init_snake(Game* game)
{
	Color c;

	c.r = 232; c.g = 241; c.b = 166;
	game->snake.color1= c;

	c.r = 163; c.g = 194; c.b = 85;
	game->snake.color2= c;

	c.r = 111; c.g = 163; c.b = 65;
	game->snake.color3 = c;

	game->snake.up    = SDL_SCANCODE_W;
	game->snake.down  = SDL_SCANCODE_S;
	game->snake.left  = SDL_SCANCODE_A;
	game->snake.right = SDL_SCANCODE_D;

	game->snake.body = NULL;
	Game_spawn_snake(game);
}

void Game_draw_body(Game* game, int offset_x, int offset_y)
{
	SDL_Rect r = { 0, 0, game->cell_size, game->cell_size };
	for (SnakeBodyElem* i = game->snake.body; i; i = i->nxt)
	{
		r.x = i->p.x + offset_x;
		r.y = i->p.y + offset_y;
		SDL_RenderFillRect(game->rer, &r);
	}
}

void Game_draw_snake(Game* game)
{
	SDL_Rect r = { game->snake.head.x, game->snake.head.y, game->cell_size, game->cell_size };

	SDL_SetRenderDrawColor(game->rer, give_color(game->snake.color3));
	for (int i = 0; i < game->cell_offset; i++)
	{
		SDL_Rect r = { game->snake.head.x + i, game->snake.head.y + i, game->cell_size, game->cell_size };
		SDL_RenderFillRect(game->rer, &r);
		Game_draw_body(game, i, i);
	}

	SDL_SetRenderDrawColor(game->rer, give_color(game->snake.color2));
	Game_draw_body(game, 0, 0);

	SDL_SetRenderDrawColor(game->rer, give_color(game->snake.color1));
	SDL_RenderFillRect(game->rer, &r);

}

int Game_snake_possible_to_move(Game* game, int supposed_direction)
{
	if (!game->snake.body) return 1;

	int dx = game->snake.head.x - game->snake.body->p.x;
	int dy = game->snake.head.y - game->snake.body->p.y;

	switch (supposed_direction)
	{
	case SNAKE_UP:    if (dy > 0) return 0; break;
	case SNAKE_DOWN:  if (dy < 0) return 0; break;
	case SNAKE_LEFT:  if (dx > 0) return 0; break;
	case SNAKE_RIGHT: if (dx < 0) return 0; break;
	};

	return 1;
}

void Game_give_snake_direction(Game* game, int scancode)
{
	int direction = -1;

	if      (game->snake.up == scancode)    direction = SNAKE_UP;
	else if (game->snake.down == scancode)  direction = SNAKE_DOWN;
	else if (game->snake.left == scancode)  direction = SNAKE_LEFT;
	else if (game->snake.right == scancode) direction = SNAKE_RIGHT;

	if (direction < 0) return;
	if (!Game_snake_possible_to_move(game, direction)) return;

	game->snake.direction = direction;
}

void Game_move_snake_cell(Game* game, SDL_Point* cell)
{
	switch (game->snake.direction)
	{
	case SNAKE_UP:    cell->y -= game->cell_size; break;
	case SNAKE_DOWN:  cell->y += game->cell_size; break;
	case SNAKE_LEFT:  cell->x -= game->cell_size; break;
	case SNAKE_RIGHT: cell->x += game->cell_size; break;
	}
}

void Game_increase_snake(Game* game)
{
	SnakeBodyElem* tmp = (SnakeBodyElem*)malloc(sizeof(SnakeBodyElem));
	tmp->p = game->snake.head;
	tmp->nxt = game->snake.body;
	game->snake.body = tmp;
	game->snake.was_increased = 1;
}

void Game_decrease_snake(Game* game)
{
	if (!game->snake.body) return;
	if (!game->snake.body->nxt)
	{
		free(game->snake.body);
		game->snake.body = NULL;
		return;
	}
	for (SnakeBodyElem* i = game->snake.body; i; i = i->nxt)
	{
		if (i->nxt->nxt) continue;
		free(i->nxt);
		i->nxt = 0;
	}
}

void Game_update_snake_death_satus(Game* game)
{
	SDL_Rect r = { game->snake.head.x, game->snake.head.y, game->cell_size, game->cell_size };
	SDL_Rect screen = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	if (!SDL_HasIntersection(&screen, &r))
	{
		game->snake.is_died = 1;
		return;
	}

	for (int i = 0; i < game->field.borders.num; i++)
	{
		SDL_Point p = { game->field.borders.coords[i].x, game->field.borders.coords[i].y };
		int cond = p.x == game->snake.head.x && p.y == game->snake.head.y;
		if (!cond) continue;
		game->snake.is_died = 1;
		break;
	}

	if (!game->snake.body) return;

	for (SnakeBodyElem* i = game->snake.body; i; i = i->nxt)
	{
		if (i->p.x == game->snake.head.x && i->p.y == game->snake.head.y)
		{
			game->snake.is_died = 1;
			break;
		}
	}
}

void Game_move_snake(Game* game)
{
	if (SDL_GetTicks() - game->snake.last_update <= 100) return;
	game->snake.last_update = SDL_GetTicks();

	SDL_Point to_cell = game->snake.head;
	Game_move_snake_cell(game, &game->snake.head);
	Game_update_snake_death_satus(game);

	if (game->snake.was_increased)
	{
		game->snake.was_increased = 0;
		return;
	}

	for (SnakeBodyElem* i = game->snake.body; i; i = i->nxt)
	{
		SDL_Point tmp = i->p;
		i->p = to_cell;
		to_cell = tmp;
	}
}


void Game_spawn_snake(Game* game)
{
	SDL_Point p = { GAME_WIDTH / 2 - game->cell_size, GAME_HEIGHT / 2 - game->cell_size };
	game->snake.head = p;

	while (game->snake.body)
	{
		SnakeBodyElem* tmp = game->snake.body->nxt;
		free(game->snake.body);
		game->snake.body = tmp;
	}
	game->snake.body = NULL;

	game->snake.last_update = SDL_GetTicks();
	game->snake.was_increased = 0;
	game->snake.is_died = 0;
}
