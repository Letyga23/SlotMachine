#include "SpinningState.h"
#include "MainGameForm.h"

void SpinningState::handle()
{
	DebugLog("SpinningState");
	MainGameForm::getStopButton()->show();
}
