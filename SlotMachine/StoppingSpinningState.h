#pragma once
#include "State.h"

//состояние остановки вращения барабанов
class StoppingSpinningState : public State
{
public:
    void handle() override;
    StateType getType() const override;
};

