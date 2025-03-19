#include "Reel.h"

Reel::Reel(float x, float y, float width, float height, float centralPosition) :
    x(x),
    y(y),
    width(width),
    height(height),
    centralPosition(centralPosition),
    offset(0.0f), 
    currentSpeed(0.0f), 
    targetSpeed(0.03f),
    accelerationValue(0.00005f),
    decelerationValue(0.00009f),
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
    currentIndex = static_cast<float>(std::rand() % countFigures);
}

void Reel::initializeSymbols()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    for (int i = 0; i < countFigures; ++i) 
    {
        ReelSymbol symbol;
        symbol.textureID = WorkingWithTextures::getTextureFromCache(hInstance, i);
        symbol.index = i;
        symbol.y = y + i * cell_H;
        symbols.push_back(symbol);
    }
}

bool Reel::getIsSpinning()
{
    return isSpinning;
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
    }
}

void Reel::draw()
{
    speedChange();

    //Обновление смещения для вращения
    offset += currentSpeed;

    if (offset >= height / 2.0f)
        offset -= height;

    for (int i = 0; i < countFigures; ++i) 
    {
        float currentY = y + (i - 1) * height - offset;
        int index = static_cast<int>(fmod(currentIndex + i, countFigures));
        symbols[index].y = currentY;
        drawShape(x, currentY, symbols[index].textureID);
    }

    //Обновление текущего индекса изображения
    currentIndex += currentSpeed / height;
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

    currentIndex += currentSpeed / height;
    if (currentIndex >= countFigures)
        currentIndex = 0.0f;
}

void Reel::drawShape(float x, float y, GLuint textureID)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

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

int Reel::getCentralIndex() 
{
    std::vector<ReelSymbol> selectedSymbols;
    for (const auto& symbol : symbols)
    {
        //DebugLog(std::to_string(symbol.index) + ": " + std::to_string(symbol.y));
        if (symbol.y > 0.0f)
            continue;

        selectedSymbols.push_back(symbol);
    }

    float minDist = std::numeric_limits<float>::max();
    int bestIndex = -1;
    for (const auto& symbol : selectedSymbols)
    {
        float dist = std::fabs(symbol.y); 
        //DebugLog(std::to_string(symbol.index) + ": " + std::to_string(symbol.y) + " dist: " + std::to_string(dist));

        if (dist < minDist) 
        {
            minDist = dist;
            bestIndex = symbol.index;
        }
    }
    //DebugLog("Best symbol index: " + std::to_string(bestIndex));
    //DebugLog("Best symbol Y: " + std::to_string(symbols[bestIndex].y));
    return bestIndex;
}

