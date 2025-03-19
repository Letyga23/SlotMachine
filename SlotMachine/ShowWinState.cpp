#include "ShowWinState.h"
#include "MainGameForm.h"

void ShowWinState::handle()
{
	MainGameForm::getResultGame()->calculationsScore();
	MainGameForm::getResultGame()->show();

	std::thread([this]
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			GameStateMachine& stateMachine = GameStateMachine::getInstance();
			stateMachine.setState(std::make_unique<WaitingForPlayerState>());
		}
        ).detach();
}

StateType ShowWinState::getType() const
{
	return StateType::ShowWinState;
}