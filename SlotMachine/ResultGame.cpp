#include "ResultGame.h"

ResultGame::ResultGame(float x, float y) :
	x(x),
	y(y),
	isVisible(true)
{
}

void ResultGame::draw()
{
	if (!isVisible) return;

	calculationsScore();
	renderText(x, y);
}

void ResultGame::show()
{
	isVisible = true;
}

void ResultGame::hide()
{
	isVisible = false;
}

void ResultGame::calculationsScore()
{
}

void ResultGame::renderText(float x, float y)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	std::string displayText = "–езультат: " + std::to_string(10) +  " очков";
	for (char c : displayText)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}
