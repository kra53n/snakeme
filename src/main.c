#include "game.h"
#include "main_menu_state.h"

int main(int argc, char** argv)
{
	Game game;
	Game_init(&game);

	StateMachine* machine = StateMachine_init(&game);
	State* main_menu_state = MainMenuState_init(machine);
	StateMachine_push(machine, main_menu_state);
	StateMachine_enter(machine);

	return 0;
}