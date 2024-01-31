#include "state_machine.h"

#include <malloc.h>

#include "main_menu_state.h"

StateMachine* StateMachine_init(Game* game)
{
	StateMachine* machine = malloc(sizeof(StateMachine));
	machine->head = 0;
	machine->game = game;
	return machine;
}

void StateMachine_destroy(StateMachine* machine)
{
	while (!StateMachine_empty(machine))
	{
		StateMachine_pop(machine);
	}
}

State* StateMachine_pop(StateMachine* machine)
{
	State* buf = machine->head;
	machine->head = machine->head->prv;
	return buf;
}

State* StateMachine_peek(StateMachine* machine)
{
	return machine->head;
}

void StateMachine_push(StateMachine* machine, State* state)
{
	if (!state) return;

	state->prv = machine->head;
	machine->head = state;
}

int StateMachine_empty(StateMachine* machine)
{
	return machine->head == 0;
}

void StateMachine_enter(StateMachine* machine)
{
	if (StateMachine_empty(machine)) return;

	switch (machine->head->kind)
	{
	case StateKind_Menu:
		MainMenuState_enter(machine);
	default:
		return;
	}
}