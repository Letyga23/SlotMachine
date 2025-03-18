#pragma once
#include "Button.h"
#include "GameStateMachine.h"

class StartButton : public Button
{
	GameStateMachine& stateMachine;

public:
	StartButton(float x, float y, float width, float height, const char* label);

private:
	void onClick() override;
};

