#include "StoppingSpinningState.h"
#include "MainGameForm.h"

void StoppingSpinningState::handle()
{
	MainGameForm::getReels()->stop();
	MainGameForm::getStopButton()->hide();
}

StateType StoppingSpinningState::getType() const
{
	return StateType::StoppingSpinningState;
}