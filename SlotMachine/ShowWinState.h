#pragma once
#include "State.h"
#include <chrono>
#include <thread>

//Состояние показа выигрыша
class ShowWinState : public State 
{
public:
    void handle() override;
    StateType getType() const override;
};

