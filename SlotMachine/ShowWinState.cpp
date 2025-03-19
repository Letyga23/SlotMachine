#include "ShowWinState.h"
#include "MainGameForm.h"

void ShowWinState::handle()
{
	DebugLog("ShowWinState");
	MainGameForm::getStopButton()->hide();
}
