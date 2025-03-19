#include "WaitingForPlayerState.h"
#include "MainGameForm.h"

void WaitingForPlayerState::handle()
{
	MainGameForm::getStartButton()->show();
}

StateType WaitingForPlayerState::getType() const
{
	return StateType::WaitingForPlayerState;
}

