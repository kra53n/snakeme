#include <malloc.h>

#include "game.h"
#include "snake.h"

void Game_init_snake(Game* game)
{
	Color c;

	c.r = 232; c.g = 241; c.b = 166;
	game->snake.color1= c;

	c.r = 202; c.g = 214; c.b = 112;
	game->snake.color2= c;

	c.r = 163; c.g = 194; c.b = 85;
	game->snake.color3 = c;

	SDL_Point p = { GAME_WIDTH / 2 - game->cell_size, GAME_HEIGHT / 2 - game->cell_size };
	game->snake.head = p;

	game->snake.body.head = NULL;
	game->snake.body.tail = NULL;

	game->snake.up    = SDL_SCANCODE_W;
	game->snake.down  = SDL_SCANCODE_S;
	game->snake.left  = SDL_SCANCODE_A;
	game->snake.right = SDL_SCANCODE_D;

	game->snake.last_update = SDL_GetTicks();
	game->snake.was_increased = 0;
}

void Game_draw_snake(Game* game)
{
	SDL_Rect r = { game->snake.head.x, game->snake.head.y, game->cell_size, game->cell_size };

	SDL_SetRenderDrawColor(game->rer, give_color(game->snake.color2));
	for (int i = 0; i < game->cell_offset; i++)
	{
		SDL_Rect r = { game->snake.head.x + i, game->snake.head.y + i, game->cell_size, game->cell_size };
		SDL_RenderFillRect(game->rer, &r);
	}

	SDL_SetRenderDrawColor(game->rer, give_color(game->snake.color1));
	SDL_RenderFillRect(game->rer, &r);

	for (SnakeBodyElem* i = game->snake.body.head; i; i = i->nxt)
	{
		r.x = i->p.x;
		r.y = i->p.y;
		SDL_RenderFillRect(game->rer, &r);
	}
}

void Game_give_snake_direction(Game* game, int scancode)
{
	if      (game->snake.up == scancode)    game->snake.direction = SNAKE_UP;
	else if (game->snake.down == scancode)  game->snake.direction = SNAKE_DOWN;
	else if (game->snake.left == scancode)  game->snake.direction = SNAKE_LEFT;
	else if (game->snake.right == scancode) game->snake.direction = SNAKE_RIGHT;
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
	SnakeBodyElem* head = game->snake.body.head;
	SnakeBodyElem* tail = game->snake.body.tail;

	if (head == tail)
	{
		if (head == NULL)
		{
			tmp->nxt = NULL;
			tmp->prv = NULL;
			head = tail = tmp;
		}
		else
		{
			tmp->nxt = tail;
			tmp->prv = NULL;
			head = tmp;
		}
	}
	else
	{
		tmp->nxt = head;
		tmp->prv = NULL;
		head->prv = tmp;
		head = tmp;
	}

	game->snake.body.head = head;
	game->snake.body.tail = tail;
}

void Game_decrease_snake(Game* game)
{
	if (!game->snake.body.tail) return;
	SnakeBodyElem* tmp = game->snake.body.tail->prv;
	free(game->snake.body.tail);
	if (tmp) tmp->nxt = NULL;
	game->snake.body.tail = tmp;
}

void Game_move_snake(Game* game)
{
	if (SDL_GetTicks() - game->snake.last_update <= 100) return;
	game->snake.last_update = SDL_GetTicks();

	Game_move_snake_cell(game, &game->snake.head);

	if (game->snake.was_increased)
	{
		game->snake.was_increased = 0;
		return;
	}

	for (SnakeBodyElem* i = game->snake.body.head; i; i = i->nxt)
	{
		Game_move_snake_cell(game, &i->p);
	}
	//Game_decrease_snake(game);
}

