#include "StartButton.h"

StartButton::StartButton(float x, float y, float width, float height, const char* label)
	: Button(x, y, width, height, label), stateMachine(GameStateMachine::getInstance())
{
}

void StartButton::onClick()
{
	stateMachine.setState(std::make_unique<StartSpinningState>());
	stateMachine.update();
}
