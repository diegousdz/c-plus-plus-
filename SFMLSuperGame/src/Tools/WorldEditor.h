#pragma once
#include <string>
using namespace std;

class GameEditor
{
public:
    
    GameEditor(int screenHeight);

    int tileMapWidth;
    int tileMapHeight;
    int tileSize;

    int gameAreaPadding = 64;
    
    // Player start position
    int gameStartPositionX = gameAreaPadding;

    //Level end Position achieved
    int gameEndPositionX = -gameAreaPadding;
    
    int gameArea = tileMapWidth - gameAreaPadding * 2;

    int gameOverLine;

    int modules = 0;

    // Fixed Array size
    int modulesPositionX[4] = {0, 0, 0, 0};
    int modulesPositionY[4] = {0, 0, 0, 0};

    // Memory Dynamically Allocated to enable module resize
    int* moduleWidth = new int[4] {0, 0, 0, 0};
    int* moduleHeight = new int[4]{0, 0, 0, 0};
    
    string modulesNames[4] = { "Hierarchy", "Game", "Inspector", "Components"};

    void InitializeGameEditor();
    void ExitGameEditor();
};
