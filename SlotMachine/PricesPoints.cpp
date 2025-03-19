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

    for (const auto& scoringImage : scoringImages)
    {
        WorkingWithTextures::drawTexture(scoringImage.textureID, currentX, currentY, 0.1f, 0.1f);
        renderText(std::to_string(scoringImage.points), currentX + 0.11f, currentY + 0.02f);

        count++;
        if (count % 2 == 0)
        {
            currentX = x;
            currentY -= margin;
        }
        else
            currentX += 0.2f;  
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
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); 
}
