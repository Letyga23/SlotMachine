#include "ResultGame.h"
#include "MainGameForm.h"

ResultGame::ResultGame(float x, float y) :
	x(x),
	y(y),
	isVisible(true),
	score(0)
{
	maxIndex = WorkingWithTextures::getCountTexture() - 1;
	pricesPoints = MainGameForm::getPricesPoints();
}

void ResultGame::draw()
{
	if (!isVisible) return;

	calculationsScore();
	renderText();
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
	std::list<int> listIndexs = MainGameForm::getReels()->getListCurrentIndexs();
	score = 0;

	for (int index : listIndexs)
	{
		if (index > maxIndex)
			index = 0;
		score += pricesPoints->getScore(index);
	}
}

void ResultGame::renderText()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	std::string displayText = "Result: " + std::to_string(score) +  " score";
	for (char c : displayText)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}
