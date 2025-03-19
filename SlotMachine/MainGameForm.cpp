#include "MainGameForm.h"

std::shared_ptr<StartButton> MainGameForm::startButton = nullptr;
std::shared_ptr<StopButton> MainGameForm::stopButton = nullptr;
std::shared_ptr<GameReels> MainGameForm::reels = nullptr;
std::shared_ptr<PricesPoints> MainGameForm::pricesPoints = nullptr;
std::shared_ptr<ResultGame> MainGameForm::resultGame = nullptr;

MainGameForm::MainGameForm()
{
    startButton = std::make_shared<StartButton>(0.6f, 0.9f, 0.3f, 0.15f, "Start");
    stopButton = std::make_shared<StopButton>(0.6f, 0.9f, 0.3f, 0.15f, "Stop");
    reels = std::make_shared<GameReels>(-0.95f, -0.9f, 1.5f, 1.8f);
    pricesPoints = std::make_shared<PricesPoints>(0.58f, 0.55f);
    resultGame = std::make_shared<ResultGame>(0.58f, -0.4f);

    stopButton->hide();
}

void MainGameForm::renderScene()
{
    glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    drawReelsPanel();
    drawButtons();
    drawPricesPoints();
    drawResultGame();
}

void MainGameForm::drawReelsPanel()
{
    reels->draw();
}

void MainGameForm::drawButtons()
{
    startButton->draw();
    stopButton->draw();
}

void MainGameForm::drawPricesPoints()
{
    pricesPoints->draw();
}

void MainGameForm::drawResultGame()
{
    resultGame->draw();
}

void MainGameForm::mouseButton(int button, int state, int x, int y)
{
    startButton->handleMouse(button, state, x, y);
    stopButton->handleMouse(button, state, x, y);
}

void MainGameForm::mouseMotion(int x, int y)
{
    startButton->handleMotion(x, y);
    stopButton->handleMotion(x, y);
}

void MainGameForm::init()
{
    glutMouseFunc(mouseButton); //–егистрация обработки кликов
    glutPassiveMotionFunc(mouseMotion); //–егистрация обработки движения мыши

    HINSTANCE hInstance = GetModuleHandle(NULL);
    std::vector<int> points = { 10, 20, 30, 40, 50, 60, 70 };
    for (int i = 0; i < points.size(); ++i)
    {
        GLuint textureID = WorkingWithTextures::getTextureFromCache(hInstance, i);
        pricesPoints->addImage(textureID, points[i]);
    }

    reels->initializeSymbols();
}

std::shared_ptr<GameReels> MainGameForm::getReels()
{
    return reels;
}

std::shared_ptr<StartButton> MainGameForm::getStartButton()
{
    return startButton;
}

std::shared_ptr<StopButton> MainGameForm::getStopButton()
{
    return stopButton;
}

std::shared_ptr<PricesPoints> MainGameForm::getPricesPoints()
{
    return pricesPoints;
}

std::shared_ptr<ResultGame> MainGameForm::getResultGame()
{
    return resultGame;
}
