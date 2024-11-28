#pragma once

#include "ResourceManager.h"
#include "../Game/Game.h"

class NexusManager {
public:
    static NexusManager& getInstance() {
        static NexusManager instance;
        return instance;
    }

    ResourceManager& getResourceManager() {
        return resourceManager;
    }
    
    void init();
    void update(float deltaTime);
    void draw(sf::RenderWindow& gameWindow);
    void handleInput();
    void updatePlayerAnimation();
    void initializeWindow(sf::RenderWindow& gameWindow, int width, int height, std::string windowName);

private:
    NexusManager() {}

    ResourceManager resourceManager;
    Game game;
};