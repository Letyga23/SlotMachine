#pragma once
#include <string>

class ResultGame
{
	float x, y;
	bool isVisible;
	int score;
	int maxIndex;

public:
	ResultGame(float x, float y);

	void draw();
	void show();
	void hide();

private:
	void calculationsScore();
	void renderText();
};

