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

	game->snake.up    = SDL_SCANCODE_W;
	game->snake.down  = SDL_SCANCODE_S;
	game->snake.left  = SDL_SCANCODE_A;
	game->snake.right = SDL_SCANCODE_D;

	game->snake.last_update = SDL_GetTicks();
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
}

void Game_give_snake_direction(Game* game, int scancode)
{
	if      (game->snake.up == scancode)    game->snake.direction = SNAKE_UP;
	else if (game->snake.down == scancode)  game->snake.direction = SNAKE_DOWN;
	else if (game->snake.left == scancode)  game->snake.direction = SNAKE_LEFT;
	else if (game->snake.right == scancode) game->snake.direction = SNAKE_RIGHT;
}

void Game_move_snake(Game* game)
{
	if (SDL_GetTicks() - game->snake.last_update <= 100) return;
	game->snake.last_update = SDL_GetTicks();

	switch (game->snake.direction)
	{
	case SNAKE_UP:    game->snake.head.y -= game->cell_size; break;
	case SNAKE_DOWN:  game->snake.head.y += game->cell_size; break;
	case SNAKE_LEFT:  game->snake.head.x -= game->cell_size; break;
	case SNAKE_RIGHT: game->snake.head.x += game->cell_size; break;
	}
}
