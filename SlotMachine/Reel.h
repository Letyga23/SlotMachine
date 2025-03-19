#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <ctime>
#include <map>
#include <vector>
#include "DebugLog.h"
#include "WorkingWithTextures.h"
#include "GameStateMachine.h"

class Reel
{
	float x, y;         
	float width, height;
	float currentSpeed;			//текущая скорость
	float targetSpeed;			//целевая скорость (максимальная скорость)
	float currentIndex;			//индекс текущего изображения на экране
	float offset;				//смещение для анимации (для плавного движения)
	int countFigures;			//количество фигур
	bool isSpinning;			//флаг определяющий крутится барабан или нет
	bool isStarting;			//флаг определяющий запускается ли барабан
	bool isStoping;				//флаг определяющий останавливается ли барабан
	const float margin = 0.2f;	//отступ
	const float accelerationValue;	//ускорение при старте
	const float decelerationValue;	//замедление при остановке
	float cell_W;				//ширина ячейки
	float cell_H;				//высота ячейки
	float offsetX;
	float offsetY;
	float centralPosition;		//центрпальная позиция барабана

	struct ReelSymbol 
	{
		GLuint textureID;  //Идентификатор текстуры
		int index;         //Индекс текстуры в массиве
		float y;           //Текущая координата Y
	};

	std::vector<ReelSymbol> symbols;

public:
	Reel(float x, float y, float width, float height, float centralPosition);
	void draw();
	void start(); 
	void stop();
	float getHeight();
	float getWidth();
	int getCentralIndex();
	void initializeSymbols();
	bool getIsSpinning();

private:
	void drawShape(float x, float y, GLuint textureID);
	void drawFrame(float x, float y, float width, float height);
	void alignToCentralPosition();
	void speedChange();
	void acceleration();
	void deceleration();
	void initializeIndex();
};

