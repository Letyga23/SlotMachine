#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() : currentState(std::make_unique<WaitingForPlayerState>()) {}

GameStateMachine& GameStateMachine::getInstance() 
{
    static GameStateMachine instance;
    return instance;
}

void GameStateMachine::setState(std::unique_ptr<State> newState)
{
    currentState = std::move(newState);
}

void GameStateMachine::update() 
{
    if (currentState)
        currentState->handle();
}
