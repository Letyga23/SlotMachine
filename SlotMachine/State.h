#pragma once
#include <memory>
#include "DebugLog.h"

//Базовый интерфейс состояния
class State {
public:
    virtual ~State() = default;
    virtual void handle() = 0; //Метод обработки состояния
};