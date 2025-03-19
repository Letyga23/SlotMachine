#include "Reel.h"

Reel::Reel(float x, float y, float width, float height, float centralPosition) :
    x(x),
    y(y),
    width(width),
    height(height),
    centralPosition(centralPosition),
    offset(0.0f), 
    currentSpeed(0.0f), 
    targetSpeed(0.05f),
    accelerationValue(0.0001f),
    decelerationValue(0.0002f),
    isSpinning(false),
    isStarting(false),
    isStoping(false)
{
    initializeIndex();

    cell_W = width * (1.0f - margin);
    cell_H = height * (1.0f - margin);

    offsetX = (width - cell_W) / 2.0f;
    offsetY = (height - cell_H) / 2.0f;

    alignToCentralPosition();
}

void Reel::initializeIndex()
{
    countFigures = WorkingWithTextures::getCountTexture();
    std::srand(static_cast<unsigned int>(std::time(nullptr)) + reinterpret_cast<std::intptr_t>(this));
    int countFiguresInt = static_cast<int>(countFigures);
    currentIndex = static_cast<float>(std::rand() % countFiguresInt);
}

void Reel::speedChange()
{
    if (isStarting)
        acceleration();
    else if (isStoping)
        deceleration();
}

//Увеличиваем скорость
void Reel::acceleration()
{
    if (currentSpeed < targetSpeed)
        currentSpeed = std::min(currentSpeed + accelerationValue, targetSpeed);
    else
    {
        isSpinning = true;
        isStarting = false;
        GameStateMachine::getInstance().setState(std::make_unique<SpinningState>());
        GameStateMachine::getInstance().update();
    }
}

//Замедляем скорость
void Reel::deceleration()
{
    if (currentSpeed > 0.0f)
        currentSpeed = std::max(currentSpeed - decelerationValue, 0.0f);
    else
    {
        alignToCentralPosition();
        isSpinning = false;
        isStoping = false;
        GameStateMachine::getInstance().setState(std::make_unique<ShowWinState>());
        GameStateMachine::getInstance().update();
    }
}

void Reel::draw()
{
    speedChange();

    //Обновление смещения для вращения
    offset += currentSpeed;

    if (offset >= height / 2.0f)
    {
        offset -= height;
        //currentIndex = static_cast<int>(currentIndex + 1) % countFigures;
    }

    //Рисуем изображения барабана
    for (int i = 0; i < countFigures; ++i) 
    {
        float currentY = y + (i - 1) * height - offset;
        int index = static_cast<int>(fmod(currentIndex + i, countFigures));
        drawShape(x, currentY, index);
    }

    ////Обновление текущего индекса изображения
    currentIndex += currentSpeed / height;
    DebugLog(currentIndex);
    if (currentIndex >= countFigures)
        currentIndex = 0.0f;
}

void Reel::start()
{
    isStarting = true;
}

void Reel::stop()
{
    isStoping = true;
}

void Reel::alignToCentralPosition()
{
    float targetOffset = centralPosition - (height / 2.0f);
    offset = fmod(targetOffset, height);

    if (offset < 0)
        offset += height;

    float targetIndex = round(currentIndex);
    currentIndex = targetIndex;
}

void Reel::drawShape(float x, float y, int index)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    HINSTANCE hInstance = GetModuleHandle(NULL);
    GLuint textureID = WorkingWithTextures::getTextureFromCache(hInstance, index);
    if (textureID != 0)
        WorkingWithTextures::drawTexture(textureID, offsetX, offsetY, cell_W, cell_H);

    drawFrame(offsetX, offsetY, cell_W, cell_H);
    glPopMatrix();
}

float Reel::getHeight()
{
    return cell_H;
}

float Reel::getWidth()
{
    return cell_W;
}

int Reel::getCurrentIndex()
{
    float targetIndex = round(currentIndex);
    return static_cast<int>(targetIndex);
}

void Reel::drawFrame(float x, float y, float width, float height)
{
    GLfloat currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y); 
    glVertex2f(x + width, y);  
    glVertex2f(x + width, y + height); 
    glVertex2f(x, y + height); 
    glEnd();

    glColor4fv(currentColor);
    glLineWidth(1.0f);
}



