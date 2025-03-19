#pragma once
#include <memory>
#include "DebugLog.h"

enum class StateType 
{
    WaitingForPlayerState,
    StartSpinningState,
    SpinningState,
    StoppingSpinningState,
    ShowWinState
};

//Базовый интерфейс состояния
class State {
public:
    virtual ~State() = default;
    virtual void handle() = 0; //Метод обработки состояния
    virtual StateType getType() const = 0;
};