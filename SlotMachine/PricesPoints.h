#pragma once
#include "WorkingWithTextures.h"
#include <list>
#include <GL/freeglut.h>

class PricesPoints
{
	struct ScoringImage
	{
		GLuint textureID;  //Идентификатор текстуры
		int points;        //Количество очков
	};

	float x, y;
	std::list<ScoringImage> scoringImages; //Список изображений и их очков
	float margin = 0.15f;  //Отступ между миниатюрами картинок

public:
	PricesPoints(float x, float y);

	void draw();
	void addImage(GLuint textureID, int points);

private:
	void renderText(const std::string& text, float x, float y);
};

