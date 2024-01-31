#include "main_menu_state.h"

#include <stdio.h>
#include <malloc.h>

State* MainMenuState_init(StateMachine* machine)
{
	State* state = malloc(sizeof(State));
	state->kind = StateKind_Menu;
	state->exit = 0;
	return state;
}

void MainMenuState_enter(StateMachine* machine)
{
	State* state = machine->head;
	while (1)
	{
		MainMenuState_update(machine);
		if (state->exit)
		{
			MainMenuState_exit(machine);
			break;
		}
	}
}

void MainMenuState_exit(StateMachine* machine)
{
	machine->head->exit = 1;
	StateMachine_pop(machine);
}

void MainMenuState_update(StateMachine* machine)
{
	State* state = machine->head;
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT:
			state->exit = 1;
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			case SDLK_q:
				state->exit = 1;
			case SDLK_RETURN:
			case SDLK_RETURN2:
			case SDLK_SPACE:
				;
				//StateMachine_push(GameState_init());
			}
		}
	}
}