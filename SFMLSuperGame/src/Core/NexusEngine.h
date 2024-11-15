#pragma once

#include "HelperFunctions.h"
#include "FileManager.h"
#include "ResourceManager.h"
#include "AnimationSequencer.h"
#include "../Game/Game.h"
#include "../Tools/WorldEditor.h"

class NexusEngine
{
public:
    // Singleton access
    
    static NexusEngine& getInstance()
    {
        static NexusEngine instance;
        return instance;
    }

    ResourceManager& getResourceManager() { return resourceManager; }
    
    void init();
    void update(float deltaTime);
    void draw(sf::RenderWindow& gameWindow);
    void handleInput();
    void initializeWindow(sf::RenderWindow& gameWindow, int width, int height, std::string windowName);

private:
    NexusEngine()
    {
    } // Singleton pattern

    ResourceManager resourceManager; // The central resource manager
        
    Game game;

};
