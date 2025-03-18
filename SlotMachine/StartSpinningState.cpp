#include "StartSpinningState.h"
#include "MainGameForm.h"

void StartSpinningState::handle()
{
	DebugLog("StartSpinningState");
	MainGameForm::getReels()->start();
	MainGameForm::getStartButton()->hide();
}
