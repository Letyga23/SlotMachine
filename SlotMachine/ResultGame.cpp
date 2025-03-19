#include "ResultGame.h"
#include "MainGameForm.h"

ResultGame::ResultGame(float x, float y) :
	x(x),
	y(y),
	isVisible(true),
	score(0)
{
	maxIndex = WorkingWithTextures::getCountTexture() - 1;
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
	std::shared_ptr<PricesPoints> pricesPoints = MainGameForm::getPricesPoints();

	for (int index : listIndexs)
	{
		
		index++;
		//index++;
		//index++;


		if (index > maxIndex)
			index = 0;

		DebugLog(index);
		score += pricesPoints->getScore(index);
	}
	DebugLog("-----");
}

void ResultGame::renderText()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	std::string displayText = "Result: " + std::to_string(score) +  " score";
	for (char c : displayText)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}
