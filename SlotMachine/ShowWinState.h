#pragma once
#include "State.h"

//Состояние показа выигрыша
class ShowWinState : public State 
{
public:
    void handle() override;
};

