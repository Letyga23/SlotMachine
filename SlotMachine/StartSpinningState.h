#pragma once
#include "State.h"

//Состояние начала вращения барабанов
class StartSpinningState : public State
{
public:
    void handle() override;
};


