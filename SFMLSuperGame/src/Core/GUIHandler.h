#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class ResourceManager;

class GUIHandler {
public:
    GUIHandler();
    void draw(sf::RenderWindow& window, ResourceManager& resourceManager);
    void mainMenuInit(ResourceManager& resourceManager);
    void updateHealthBar(ResourceManager& resourceManager);
    void drawMainMenu(sf::RenderWindow& window, ResourceManager& resourceManager);
    void drawGameHeader(sf::RenderWindow& window, ResourceManager& resourceManager);
    void drawGameFooter(sf::RenderWindow& window, ResourceManager& resourceManager);
    void gameHeaderInit(ResourceManager& resourceManager);
    void gameFooterInit(ResourceManager& resourceManager);
    void setWindowBounds(ResourceManager& resourceManager);
    void setGameViewport(sf::RenderWindow& window, sf::View& gameView);
    void setIsInGame(ResourceManager& resourceManager, bool value);
    void drawGameOver(sf::RenderWindow& window, ResourceManager& resourceManager); 
    void gameOverInit(ResourceManager& resourceManager);

};