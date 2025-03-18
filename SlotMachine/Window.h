#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "MainGameForm.h"

//Класс для рендера окна
class Window
{
    static std::shared_ptr<MainGameForm> mainGameForm;
    static int minWidth;
    static int minHeight;
    const char* windowTitle;

public:
    Window(int width, int height, const char* title);
    ~Window();
    void init();
    void startMainLoop();

private:
    static void display();
    static void idle();
    static void reshape(int w, int h);
};
