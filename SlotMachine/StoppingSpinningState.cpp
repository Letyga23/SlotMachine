#include "StoppingSpinningState.h"
#include "MainGameForm.h"

void StoppingSpinningState::handle()
{
	DebugLog("StoppingSpinningState");
	MainGameForm::getReels()->stop();
	MainGameForm::getStopButton()->hide();
}
