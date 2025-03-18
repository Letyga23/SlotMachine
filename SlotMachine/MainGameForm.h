#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <fstream>
#include "DebugLog.h"
#include "StartButton.h"
#include "StopButton.h"
#include "GameReels.h"
#include "PricesPoints.h"
#include "ResultGame.h"

//основная форма
class MainGameForm
{
	static std::shared_ptr<StartButton> startButton;
	static std::shared_ptr<StopButton> stopButton;
	static std::shared_ptr<GameReels> reels;
	static std::shared_ptr<PricesPoints> pricesPoints;
	static std::shared_ptr<ResultGame> resultGame;

public:
	MainGameForm();
	void renderScene();
	void init();
	static std::shared_ptr<GameReels> getReels();
	static std::shared_ptr<StartButton> getStartButton();
	static std::shared_ptr<StopButton> getStopButton();
	static std::shared_ptr<ResultGame> getResultGame();

private:
	void drawReelsPanel();
	void drawButtons();
	void drawPricesPoints();
	void drawResultGame();
	static void mouseButton(int button, int state, int x, int y);
	static void mouseMotion(int x, int y);
};

