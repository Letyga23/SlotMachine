#pragma once
#include "WaitingForPlayerState.h"
#include "ShowWinState.h"
#include "SpinningState.h"
#include "StartSpinningState.h"
#include "StoppingSpinningState.h"

//Класс машины состо¤ний
class GameStateMachine {
private:
    std::unique_ptr<State> currentState;

    GameStateMachine();

    //запрет копирование и перемещение (чтобы не было дубликатов)
    GameStateMachine(const GameStateMachine&) = delete;
    GameStateMachine& operator=(const GameStateMachine&) = delete;
public:
    static GameStateMachine& getInstance();
    void setState(std::unique_ptr<State> newState);
    void update();
};

