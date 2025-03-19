#include "PricesPoints.h"

PricesPoints::PricesPoints(float x, float y) : 
	x(x), 
	y(y)
{
}

void PricesPoints::draw()
{
    float currentX = x;
    float currentY = y;
    int count = 0;

    //Количество столбцов
    int columns = 2;
    int rows = (scoringImages.size() + columns - 1) / columns; //Расчёт количество строк
    float columnSpacing = 0.22f;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int index = j * rows + i; 

            if (index >= scoringImages.size())
                break; 

            WorkingWithTextures::drawTexture(scoringImages[index].textureID, currentX + j * columnSpacing, currentY - i * margin, 0.1f, 0.1f);
            renderText(std::to_string(scoringImages[index].points), currentX + j * columnSpacing + 0.11f, currentY - i * margin + 0.02f);
        }
    }
}

void PricesPoints::addImage(GLuint textureID, int points)
{
	scoringImages.push_back({ textureID, points });
}

int PricesPoints::getScore(int index)
{
    return scoringImages[index].points;
}

void PricesPoints::renderText(const std::string& text, float x, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    std::string displayText = '-' + text;
    for (char c : displayText)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); 
}
