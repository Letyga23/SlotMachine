#pragma once
#include "Button.h"
#include "GameStateMachine.h"

class StopButton : public Button
{
	GameStateMachine& stateMachine;

public:
	StopButton(float x, float y, float width, float height, const char* label);

private:
	void onClick() override;
};

