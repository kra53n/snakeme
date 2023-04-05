#include "game.h"

int main(int argc, char** argv)
{
	Game game;
	Game_init(&game);
	Game_run(&game);
	return 0;
}