#include "main_menu_state.h"

#include <stdio.h>
#include <malloc.h>

State* MainMenuState_init(StateMachine* machine)
{
	State* state = malloc(sizeof(State));
	state->kind = StateKind_Menu;
	return state;
}

void MainMenuState_enter(StateMachine* machine)
{
	while (1)
	{
		printf("(MainMenuState_enter) hello\n");
	}
}