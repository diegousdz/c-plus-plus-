#include "GUIHandler.h"
#include "ResourceManager.h"

GUIHandler::GUIHandler()
{
}

void GUIHandler::mainMenuInit(ResourceManager& resourceManager)
{
    if (!resourceManager.font.loadFromFile("res/fonts/PressStart2P-Regular.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
    else
    {
        std::cout << "Font loaded successfully" << std::endl;
    }

    resourceManager.title.setFont(resourceManager.font);
    resourceManager.title.setString("Frost & Stone");
    resourceManager.title.setCharacterSize(32);
    resourceManager.title.setFillColor(sf::Color::White);
    
    resourceManager.title.setPosition(50, 50);
}

void GUIHandler::gameHeaderInit(ResourceManager& resourceManager) {
    resourceManager.header.setSize(sf::Vector2f(resourceManager.windowBounds.x, resourceManager.windowBounds.y / 4));
    resourceManager.header.setPosition(0.0f, 0);
    resourceManager.header.setFillColor(sf::Color::Green);
}

void GUIHandler::drawMainMenu(sf::RenderWindow &window, ResourceManager &resourceManager)
{
    // Set up the menu items
    resourceManager.menu[0].setFont(resourceManager.font);
    resourceManager.menu[0].setCharacterSize(16);
    resourceManager.menu[0].setString("Start Game");
    resourceManager.menu[0].setPosition(sf::Vector2f(50, 180));

    resourceManager.menu[1].setFont(resourceManager.font);
    resourceManager.menu[1].setCharacterSize(16);
    resourceManager.menu[1].setString("Open Tilemap Editor");
    resourceManager.menu[1].setPosition(sf::Vector2f(50, 280));

    resourceManager.menu[2].setFont(resourceManager.font);
    resourceManager.menu[2].setCharacterSize(16);
    resourceManager.menu[2].setString("Exit");
    resourceManager.menu[2].setPosition(sf::Vector2f(50, 380));

    window.draw(resourceManager.title);

    for (int i = 0; i < ResourceManager::maxItemsMenu; i++) {
        if (i == resourceManager.currentOptionSelected) {
            resourceManager.menu[i].setFillColor(sf::Color::Yellow);
        } else {
            resourceManager.menu[i].setFillColor(sf::Color::White);
        }
        window.draw(resourceManager.menu[i]);
    }
}

void GUIHandler::drawGameHeader(sf::RenderWindow& window, ResourceManager& resourceManager) {
    window.draw(resourceManager.header);
}
// window.clear(sf::Color(20, 12, 28));

void GUIHandler::draw(sf::RenderWindow& window, ResourceManager& resourceManager) {
    if (!resourceManager.variablesDrawInitializedMainMenu && !resourceManager.isInGame) {
        setWindowBounds(resourceManager);
        mainMenuInit(resourceManager);
        drawMainMenu(window, resourceManager);
        resourceManager.variablesDrawInitializedMainMenu = true;
    }

    if (!resourceManager.variablesDrawInitializedGame && resourceManager.isInGame) {
        gameHeaderInit(resourceManager);
        resourceManager.variablesDrawInitializedGame = true;
    }

    if (resourceManager.isInGame) {
        drawGameHeader(window, resourceManager);
    } else {
        drawMainMenu(window, resourceManager);
    }
}

void GUIHandler::setWindowBounds(ResourceManager& resourceManager) {
    resourceManager.windowBounds = sf::Vector2<float>(
        static_cast<float>(resourceManager.windowWidth),
        static_cast<float>(resourceManager.windowHeight)
    );
}

void GUIHandler::setIsInGame(ResourceManager& resourceManager, bool value) {
    resourceManager.isInGame = value;
}

void GUIHandler::gameOverInit(ResourceManager& resourceManager) {
    // Set up game over text
    resourceManager.gameOverText.setFont(resourceManager.font);
    resourceManager.gameOverText.setString("GAME OVER");
    resourceManager.gameOverText.setCharacterSize(64);
    resourceManager.gameOverText.setFillColor(sf::Color::Red);
    
    // Center game over text
    sf::FloatRect textBounds = resourceManager.gameOverText.getLocalBounds();
    resourceManager.gameOverText.setPosition(
        (resourceManager.windowWidth - textBounds.width) / 2,
        (resourceManager.windowHeight - textBounds.height) / 2
    );

    // Set up restart prompt
    resourceManager.restartPrompt.setFont(resourceManager.font);
    resourceManager.restartPrompt.setString("Press SPACEBAR to restart");
    resourceManager.restartPrompt.setCharacterSize(20);
    resourceManager.restartPrompt.setFillColor(sf::Color::White);
    
    // Position restart prompt below game over text
    sf::FloatRect promptBounds = resourceManager.restartPrompt.getLocalBounds();
    resourceManager.restartPrompt.setPosition(
        (resourceManager.windowWidth - promptBounds.width) / 2,
        resourceManager.gameOverText.getPosition().y + textBounds.height + 30
    );
}


void GUIHandler::drawGameOver(sf::RenderWindow& window, ResourceManager& resourceManager) {
    // Debug print to verify this method is being called
    window.setView(window.getDefaultView());
    if (!resourceManager.gameOverInitialized) {
        gameOverInit(resourceManager); // Check if gameOverInit is called
        resourceManager.gameOverInitialized = true;
        std::cout << "Drawing game INITIALIZED over screen" << std::endl;
    }
    
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(resourceManager.windowWidth), resourceManager.windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 50));
    window.draw(overlay);

    // Make sure text is properly initialized
    if (!resourceManager.gameOverInitialized) {
        gameOverInit(resourceManager);
        resourceManager.gameOverInitialized = true;
    }
    
    window.draw(resourceManager.gameOverText);
    window.draw(resourceManager.restartPrompt);
}


void GUIHandler::handleGameOverInput(ResourceManager& resourceManager)
{
}
