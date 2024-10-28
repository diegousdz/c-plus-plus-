#pragma once

#include "HelperFunctions.h"
#include "FileManager.h"
#include "ResourceManager.h"
#include "AnimationSequencer.h"
#include "SoundSequencer.h"
#include "RenderAndFXManager.h"

using namespace sf;
using namespace std;

class NexusEngine
{
public:
    // Singleton access
    static NexusEngine& getInstance()
    {
        static NexusEngine instance;
        return instance;
    }

    void init();
    void update(float deltaTime);
    void draw(RenderWindow& gameWindow);
    void handleInput();
    void initializeWindow(RenderWindow& gameWindow, int width, int height, std::string windowName);
    void drawMainMenu(sf::RenderWindow &window);
    bool hasMenuBeenDraw = false;
  //  void initializeWindow(RenderWindow gameWindow, int width, int height, string windowName);
   // void initializeWindow(RenderWindow& gameWindow, int width, int height, std::string windowName);

private:
    NexusEngine()
    {
    } // Singleton pattern

    ResourceManager resourceManager; // The central resource manager

public:
    ResourceManager& getResourceManager() { return resourceManager; }
};
