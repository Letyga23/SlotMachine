#include "StopButton.h"

StopButton::StopButton(float x, float y, float width, float height, const char* label)
	: Button(x, y, width, height, label), stateMachine(GameStateMachine::getInstance()) 
{
}

void StopButton::onClick()
{
	stateMachine.setState(std::make_unique<StoppingSpinningState>());
	stateMachine.update();
}
