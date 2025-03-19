#pragma once
#include <string>
#include <memory>
#include "PricesPoints.h"

class ResultGame
{
	float x, y;
	bool isVisible;
	int score;
	int maxIndex;
	std::shared_ptr<PricesPoints> pricesPoints;

public:
	ResultGame(float x, float y);

	void draw();
	void show();
	void hide();

private:
	void calculationsScore();
	void renderText();
};

