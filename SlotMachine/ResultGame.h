#pragma once
#include <GL/freeglut.h>
#include <string>

class ResultGame
{
	float x, y;
	bool isVisible;
	int score;

public:
	ResultGame(float x, float y);

	void draw();
	void show();
	void hide();

private:
	void calculationsScore();
	void renderText(float x, float y);
};

