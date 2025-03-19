#include "GameReels.h"

GameReels::GameReels(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height)
{
    float reelWidth = width / countReels;
    float reelHeight = height / countReels;
    float centalPosition = height / 2;

    for(int i = 0; i < countReels; i++)
    {
        float reelX = x + i * reelWidth;  //Смещаем каждый барабан вправо
        reels.push_back(std::make_shared<Reel>(reelX, y, reelWidth, reelHeight, centalPosition));
    }
}

void GameReels::draw()
{
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    int scissorX = static_cast<int>((x + 1.0f) * 0.5f * windowWidth);  
    int scissorY = static_cast<int>((y + 1.0f) * 0.5f * windowHeight); 
    int scissorWidth = static_cast<int>(width * 0.5f * windowWidth);   
    int scissorHeight = static_cast<int>(height * 0.5f * windowHeight);

    glEnable(GL_SCISSOR_TEST);
    glScissor(scissorX, scissorY, scissorWidth, scissorHeight);

    drawBackground();

    for (std::shared_ptr<Reel> reel : reels)
        reel->draw();

    drawReelSeparators();
    drawFrame();
    drawBlackout();

    glDisable(GL_SCISSOR_TEST);
}

void GameReels::start()
{
    startStopReels(&Reel::start);
}

void GameReels::stop()
{
    startStopReels(&Reel::stop);
}

std::list<int> GameReels::getListCurrentIndexs()
{
    std::list<int> valuesList;
    for (std::shared_ptr<Reel> reel : reels)
        valuesList.push_back(reel->getCentralIndex());

    return valuesList;
}

void GameReels::initializeSymbols()
{
    for (std::shared_ptr<Reel> reel : reels)
        reel->initializeSymbols();
}

void GameReels::startStopReels(void (Reel::* action)())
{
    for (size_t i = 0; i < reels.size(); ++i)
    {
        std::thread([this, i, action] {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(100, 300); 

            int delay = dis(gen); 
            std::this_thread::sleep_for(std::chrono::milliseconds(delay * i)); 
            (reels[i].get()->*action)(); 
            }).detach();
    }
}

//Фон
void GameReels::drawBackground()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

//Оконтовка
void GameReels::drawFrame()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(9.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
void GameReels::drawReelSeparators()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(7.0f); 

    float separatorX = x;
    float reelWidth = width / reels.size();

    for (size_t i = 1; i < reels.size(); ++i) 
    {
        separatorX += reelWidth;
        glBegin(GL_LINES);
        glVertex2f(separatorX, y);  
        glVertex2f(separatorX, y + height);  
        glEnd();
    }

    glLineWidth(1.0f);
}

void GameReels::drawBlackout()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float centralPanelHeight = reels[0]->getHeight();
    float centralPanelWidth = width;
    float offsetX = x;
    float offsetY = y + (height - centralPanelHeight) / 2.0f;

    //Затеняем верхнюю область
    glColor4f(0.0f, 0.0f, 0.0f, 0.4f); 
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, offsetY);  //До начала центральной панели
    glVertex2f(x, offsetY);
    glEnd();

    //Затеняем нижнюю область
    glBegin(GL_QUADS);
    glVertex2f(x, offsetY + centralPanelHeight);  //После окончания центральной панели
    glVertex2f(x + width, offsetY + centralPanelHeight);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    //Рисуем окантовку
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(offsetX, offsetY);
    glVertex2f(offsetX + centralPanelWidth, offsetY);
    glVertex2f(offsetX + centralPanelWidth, offsetY + centralPanelHeight);
    glVertex2f(offsetX, offsetY + centralPanelHeight);
    glEnd();

    glDisable(GL_BLEND);
}
