#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() : currentState(std::make_unique<WaitingForPlayerState>()) 
{
    allowedTransitions = {
    { StateType::WaitingForPlayerState,     { StateType::StartSpinningState } },
    { StateType::StartSpinningState,  { StateType::SpinningState} },
    { StateType::SpinningState,  { StateType::StoppingSpinningState } },
    { StateType::StoppingSpinningState, { StateType::ShowWinState } },
    { StateType::ShowWinState, { StateType::WaitingForPlayerState } }
    };
}

GameStateMachine& GameStateMachine::getInstance() 
{
    static GameStateMachine instance;
    return instance;
}

void GameStateMachine::setState(std::unique_ptr<State> newState)
{
    if (!newState) return;

    StateType newStateType = newState->getType();

    //ѕроверка на установлено ли уже это состо€ние
    if (currentState && currentState->getType() == newStateType)
        return;

    //ѕроверка на допустимость ли перехода
    auto it = allowedTransitions.find(currentState->getType());
    if (it == allowedTransitions.end() || it->second != newStateType) 
        return; 

    currentState = std::move(newState);
    update();
}

void GameStateMachine::update() 
{
    if (currentState)
        currentState->handle();
}
