#pragma once
#include "State.h"

//Состояние ожидания действия игрока
class WaitingForPlayerState : public State 
{
public:
    void handle() override;
    StateType getType() const override;
};
