#include "SpinningState.h"
#include "MainGameForm.h"

void SpinningState::handle()
{
	MainGameForm::getStopButton()->show();
}

StateType SpinningState::getType() const
{
	return StateType::SpinningState;
}