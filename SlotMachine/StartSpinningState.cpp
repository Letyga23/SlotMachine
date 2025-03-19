#include "StartSpinningState.h"
#include "MainGameForm.h"

void StartSpinningState::handle()
{
	MainGameForm::getReels()->start();
	MainGameForm::getStartButton()->hide();
	MainGameForm::getResultGame()->hide();
}

StateType StartSpinningState::getType() const
{
	return StateType::StartSpinningState;
}
