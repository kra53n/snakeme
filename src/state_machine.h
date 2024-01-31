#pragma once

#include "game.h"

typedef enum StateKind StateKind;
typedef struct State State;


typedef enum StateKind
{
	StateKind_Menu,
	StateKind_Game,
};

typedef struct State
{
	State* prv;
	StateKind kind;
	int exit;
} State;

typedef struct StateMachine
{
	State* head;
	Game* game;
} StateMachine;

StateMachine* StateMachine_init(Game* game);
void StateMachine_destroy(StateMachine* machine);
State* StateMachine_pop(StateMachine* machine);
State* StateMachine_peek(StateMachine* machine);
void StateMachine_push(StateMachine* machine, State* state);
int StateMachine_empty(StateMachine* machine);

void StateMachine_enter(StateMachine* machine);