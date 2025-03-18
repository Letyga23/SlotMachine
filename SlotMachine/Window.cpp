#include "Window.h"

std::shared_ptr<MainGameForm> Window::mainGameForm = nullptr;
int Window::minWidth = 0;
int Window::minHeight = 0;

Window::Window(int width, int height, const char* title)
    : windowTitle(title)
{
    minWidth = width;
    minHeight = height;
    mainGameForm = std::make_shared<MainGameForm>();
}

Window::~Window()
{

}

void Window::init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(minWidth, minHeight);
    glutCreateWindow(windowTitle);

    glewInit();

    mainGameForm->init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
}

void Window::startMainLoop()
{
    glutMainLoop();
}

void Window::display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mainGameForm->renderScene();
    glFlush();
    glutSwapBuffers();
}

void Window::idle()
{
    glutPostRedisplay();
}

void Window::reshape(int w, int h)
{
    if (w < minWidth) w = minWidth;
    if (h < minHeight) h = minHeight;
    glViewport(0, 0, w, h);
    glutReshapeWindow(w, h);
}