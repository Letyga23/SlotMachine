#pragma once
#include "State.h"

//—осто¤ние остановки вращени¤ барабанов
class StoppingSpinningState : public State
{
public:
    void handle() override;
};

