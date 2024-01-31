#pragma once

#include "state_machine.h"

State* MainMenuState_init(StateMachine* machine);
void MainMenuState_enter(StateMachine* machine);
void MainMenuState_update(StateMachine* machine);
void MainMenuState_draw(StateMachine* machine);
void MainMenuState_handle_input(StateMachine* machine);