#include "Button.h"

Button::Button(float x, float y, float width, float height, const char* label)
    : x(x), y(y), width(width), height(height), label(label) {}

void Button::draw() 
{
    if (!isVisible) return;

    drawButtonBody();    //Основное тело кнопки
    drawBorder();        //Обводка для эффекта объёма
    drawShadow();        //Тень для кнопки
    drawText();          //Рисование текста
}

void Button::drawButtonBody() 
{
    glBegin(GL_QUADS);

    if (isPressed)
        glColor3f(0.5f, 0.0f, 0.0f);  //Темно-красный (нажатие)
    else if (isHovered)
        glColor3f(1.0f, 0.5f, 0.5f);  //Светло-красный (наведение)
    else
        glColor3f(1.0f, 0.0f, 0.0f);  //Красный цвет (обычное состояние)

    //Рисуем основную часть кнопки (прямоугольник)
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();
}

void Button::drawBorder() 
{
    //Обводка для эффекта объёма
    glLineWidth(3);
    glColor3f(0.8f, 0.6f, 0.2f);  //Оранжево-серый оттенок
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();
}

void Button::drawShadow() 
{
    //Тень 
    glColor3f(0.2f, 0.2f, 0.2f);  //Цвет тени
    glBegin(GL_LINES);
    glVertex2f(x, y - height);      //Нижняя сторона
    glVertex2f(x + width, y - height);
    glVertex2f(x + width, y);       //Правая сторона
    glVertex2f(x + width, y - height);
    glEnd();
}

void Button::drawText() 
{
    //Рисуем текст кнопки
    glColor3f(1.0f, 1.0f, 1.0f);  //Белый цвет текста
    glRasterPos2f(x + width / 4, y - height / 2);  //Позиция текста

    for (size_t i = 0; label[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);  //Рисуем символы
}

void Button::handleMouse(int button, int state, int mx, int my)
{
    if (!isVisible) return;

    Coordinates coor(mx, my);

    if (coor.X >= x && coor.X <= x + width && coor.Y >= y - height && coor.Y <= y)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            isPressed = true;
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            if (isPressed)
                onClick();
            isPressed = false;
        }
    }
}

void Button::handleMotion(int mx, int my)
{
    if (!isVisible) return;
    Coordinates coor(mx, my);
    isHovered = (coor.X >= x && coor.X <= x + width && coor.Y >= y - height && coor.Y <= y);
}

void Button::hide()
{
    isVisible = false;
}

void Button::show()
{
    isVisible = true;
}
