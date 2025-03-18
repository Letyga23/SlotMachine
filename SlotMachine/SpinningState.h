#pragma once
#include "State.h"

//Состояние вращения барабанов
class SpinningState : public State 
{
public:
    void handle() override;
};
