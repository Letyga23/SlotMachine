#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include "Reel.h"

class GameReels
{
    float x, y;         
    float width, height;
    std::vector<std::shared_ptr<Reel>> reels;
    int countReels = 5;

public:
    GameReels(float x, float y, float width, float height);
    void draw();
    void start();
    void stop();

private:
    void startStopReels(void(Reel::* action)());
    void drawBackground();
    void drawFrame();
    void drawReelSeparators();
    void drawBlackout();
};

