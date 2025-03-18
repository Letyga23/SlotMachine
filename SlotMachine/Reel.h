#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <ctime>
#include <map>
#include "DebugLog.h"
#include "WorkingWithTextures.h"
#include "GameStateMachine.h"

class Reel
{
	float x, y;         
	float width, height;
	float currentSpeed;			//“екуща¤ скорость
	float targetSpeed;			//÷елева¤ скорость (максимальна¤ скорость)
	float currentIndex;			//»ндекс текущего изображени¤ на экране
	float offset;				//—мещение дл¤ анимации (дл¤ плавного движени¤)
	int countFigures;			// оличество фигур
	bool isSpinning;			//‘лаг определ¤ющий крутитс¤ барабан или нет
	bool isStarting;			//‘лаг определ¤ющий запускаетс¤ ли барабан
	bool isStoping;				//‘лаг определ¤ющий останавливаетс¤ ли барабан
	const float margin = 0.2f;	//ќтступ
	const float accelerationValue;	//”скорение при старте
	const float decelerationValue;	//«амедление при остановке
	float cell_W;				//Ўирина ¤чейки
	float cell_H;				//¬ысота ¤чейки
	float offsetX;
	float offsetY;
	float centralPosition;		//÷ентрпальна¤ позици¤ барабана
	static std::map<Reel*, int> allCurrentIndexs;	//¬се текушие индексы


public:
	Reel(float x, float y, float width, float height, float centralPosition);
	void draw();
	void start(); 
	void stop();
	float getHeight();
	float getWidth();

private:
	void drawShape(float x, float y, int index);
	void drawFrame(float x, float y, float width, float height);
	void alignToCentralPosition();
	void speedChange();
	void acceleration();
	void deceleration();
	void initializeIndex();
};

