#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class ResourceManager;

class GUIHandler {
public:
    GUIHandler();
    void draw(sf::RenderWindow& window, ResourceManager& resourceManager);
    void mainMenuInit(ResourceManager& resourceManager);
    void drawMainMenu(sf::RenderWindow& window, ResourceManager& resourceManager);
    void drawGameHeader(sf::RenderWindow& window, ResourceManager& resourceManager);
    void gameHeaderInit(ResourceManager& resourceManager);
    void setWindowBounds(ResourceManager& resourceManager);
    void setIsInGame(ResourceManager& resourceManager, bool value);
};
