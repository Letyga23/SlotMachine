#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "DebugLog.h"

struct Coordinates
{
    float X;
    float Y;

    Coordinates(int mx, int my)
    {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        X = (2.0f * mx) / windowWidth - 1.0f;
        Y = 1.0f - (2.0f * my) / windowHeight;
    }
};

//Базовый класс кнопок
class Button
{
protected:
    float x, y, width, height;
    const char* label;
    bool isHovered = false;
    bool isPressed = false;
    bool isVisible = true;  //флаг видимости кнопки

public:
    Button(float x, float y, float width, float height, const char* label);

    void draw();
    void handleMouse(int button, int state, int mx, int my);
    void handleMotion(int mx, int my);

    //скрыть
    void hide();

    //отобразить
    void show();

protected:
    void drawButtonBody();
    void drawBorder();
    void drawShadow();
    void drawText();
    virtual void onClick() = 0;
};

