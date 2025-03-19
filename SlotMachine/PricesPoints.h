#pragma once
#include "WorkingWithTextures.h"
#include <vector>
#include <GL/freeglut.h>

class PricesPoints
{
	struct ScoringImage
	{
		GLuint textureID;  //Идентификатор текстуры
		int points;        //Количество очков
	};

	float x, y;
	std::vector<ScoringImage> scoringImages; //Список изображений и их очков
	float margin = 0.15f;  //Отступ между миниатюрами картинок

public:
	PricesPoints(float x, float y);

	void draw();
	void addImage(GLuint textureID, int points);
	int getScore(int index);

private:
	void renderText(const std::string& text, float x, float y);
};

