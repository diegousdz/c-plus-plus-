#include "GUIHandler.h"
#include "ResourceManager.h"

GUIHandler::GUIHandler() {
}

void GUIHandler::mainMenuInit(ResourceManager& resourceManager) {
    
    if (!resourceManager.font.loadFromFile("res/fonts/PressStart2P-Regular.ttf")) {
        std::cout << "Error loading font" << std::endl;
    } else {
        std::cout << "Font loaded successfully" << std::endl;
    }
    
    resourceManager.backgroundMainMenu.setTexture(resourceManager.backgroundMainMenuTexture);
    
    resourceManager.backgroundMainMenu.setPosition(0.0f, 0.0f);
    
    sf::Vector2u textureSize = resourceManager.backgroundMainMenuTexture.getSize();
    sf::Vector2u windowSize(resourceManager.windowWidth, resourceManager.windowHeight);
    
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    
    resourceManager.backgroundMainMenu.setScale(scaleX, scaleY);

    resourceManager.title.setFont(resourceManager.font);
    resourceManager.title.setString("Frost & Stone");
    resourceManager.title.setCharacterSize(32);
    resourceManager.title.setFillColor(sf::Color::White);
    
    resourceManager.menu[0].setFont(resourceManager.font);
    resourceManager.menu[0].setCharacterSize(16);
    resourceManager.menu[0].setString("Start new Game");
    resourceManager.menu[0].setPosition(sf::Vector2f(50, 180));

    resourceManager.menu[1].setFont(resourceManager.font);
    resourceManager.menu[1].setCharacterSize(16);
    resourceManager.menu[1].setString("Load Game");
    resourceManager.menu[1].setPosition(sf::Vector2f(50, 280));

    resourceManager.menu[2].setFont(resourceManager.font);
    resourceManager.menu[2].setCharacterSize(16);
    resourceManager.menu[2].setString("Exit");
    resourceManager.menu[2].setPosition(sf::Vector2f(50, 380));
    
    resourceManager.title.setPosition(50, 50);
  
}

void GUIHandler::updateHealthBar(ResourceManager& resourceManager) {
    
    float healthPercentage = resourceManager.newGamePlayer.health / 100.0f;
    
    if (healthPercentage < 0.0f) healthPercentage = 0.0f;
    if (healthPercentage > 1.0f) healthPercentage = 1.0f;

    float healthBarWidth = resourceManager.healthBarBorder.getSize().x;
    float healthBarHeight = resourceManager.healthBarBorder.getSize().y;
    
    resourceManager.healthBarFill.setSize(sf::Vector2f(healthBarWidth * healthPercentage, healthBarHeight));
    
    if (healthPercentage > 0.75f) {
        resourceManager.healthBarFill.setFillColor(sf::Color::Green);
    } else if (healthPercentage > 0.5f) {
        resourceManager.healthBarFill.setFillColor(sf::Color::Yellow);
    } else if (healthPercentage > 0.25f) {
        resourceManager.healthBarFill.setFillColor(sf::Color(255, 165, 0)); // Orange
    } else {
        resourceManager.healthBarFill.setFillColor(sf::Color::Red);
    }
}

void GUIHandler::gameHeaderInit(ResourceManager& resourceManager) {
    
    resourceManager.header.setSize(sf::Vector2f(resourceManager.windowBounds.x, 140.0f));
    resourceManager.header.setPosition(0.0f, 0.0f); 
    resourceManager.header.setFillColor(sf::Color(0, 0, 0, 64));

    float topMargin = 32.0f;
    float rightPadding = 32.0f;

    int numberOfHearts = resourceManager.newGamePlayer.life;
    resourceManager.hearts.clear();
    
    resourceManager.lifeText.setFont(resourceManager.font);
    resourceManager.lifeText.setString("LIFE");
    resourceManager.lifeText.setCharacterSize(16);
    
    sf::FloatRect lifeBounds = resourceManager.lifeText.getLocalBounds();
    float lifeTextX = resourceManager.windowBounds.x - rightPadding - lifeBounds.width;
    resourceManager.lifeText.setPosition(lifeTextX, topMargin);

    float lifeHeartSpacing = 10.0f;
    sf::Sprite tempHeart;
    tempHeart.setTexture(resourceManager.heartTexture);
    float heartWidth = tempHeart.getGlobalBounds().width;
    float heartSpacing = 8.0f; 
    float totalHeartsWidth = numberOfHearts * heartWidth + (numberOfHearts - 1) * heartSpacing;
    float heartStartX = lifeTextX - lifeHeartSpacing - totalHeartsWidth;
    
    for (int i = 0; i < numberOfHearts; ++i) {
        sf::Sprite heart;
        heart.setTexture(resourceManager.heartTexture);
        float heartX = heartStartX + i * (heartWidth + heartSpacing);
        float heartY = topMargin;
        heart.setPosition(heartX, heartY);
        resourceManager.hearts.push_back(heart);
    }
}

void GUIHandler::gameFooterInit(ResourceManager& resourceManager) {
    
    resourceManager.footer.setSize(sf::Vector2f(resourceManager.windowBounds.x, 128.0f));
    resourceManager.footer.setPosition(0.0f, resourceManager.windowBounds.y - 128.0f); 
    resourceManager.footer.setFillColor(sf::Color::Yellow);

    float slotWidth = 60;
    for (int i = 0; i < 5; ++i) {
        sf::RectangleShape slot;
        slot.setSize(sf::Vector2f(slotWidth, resourceManager.footer.getSize().y - 20));
        slot.setFillColor(sf::Color(50, 50, 50)); 
        slot.setPosition(20 + i * (slotWidth + 10), resourceManager.footer.getPosition().y + 10);
        resourceManager.inventorySlots.push_back(slot);

        sf::Sprite itemIcon;
        itemIcon.setTexture(resourceManager.itemTextures[i]);
        itemIcon.setPosition(25 + i * (slotWidth + 10), resourceManager.footer.getPosition().y + 15);
        resourceManager.inventoryIcons.push_back(itemIcon);

        sf::Text itemCount;
        itemCount.setFont(resourceManager.font);
        itemCount.setString("x0"); 
        itemCount.setCharacterSize(14);
        itemCount.setPosition(50 + i * (slotWidth + 10), resourceManager.footer.getPosition().y + 50);
        resourceManager.inventoryCounts.push_back(itemCount);
    }
}

void GUIHandler::drawMainMenu(sf::RenderWindow &window, ResourceManager &resourceManager) {
    
    window.draw(resourceManager.backgroundMainMenu);
    
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
    
    for (const auto& heart : resourceManager.hearts) {
        window.draw(heart);
    }

    window.draw(resourceManager.lifeText);
}

void GUIHandler::drawGameFooter(sf::RenderWindow& window, ResourceManager& resourceManager) {
    
    window.draw(resourceManager.footer);

    for (const auto& slot : resourceManager.inventorySlots) {
        window.draw(slot);
    }
    
    for (const auto& icon : resourceManager.inventoryIcons) {
        window.draw(icon);
    }
    
    for (const auto& count : resourceManager.inventoryCounts) {
        window.draw(count);
    }
}

void GUIHandler::setGameViewport(sf::RenderWindow& window, sf::View& gameView) {
    
    gameView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); 
}

void GUIHandler::updateLifeDisplay(ResourceManager& resourceManager) {
    
    int numberOfHearts = resourceManager.newGamePlayer.life;

    resourceManager.hearts.clear();

    float rightPadding = 32.0f;
    float topMargin = 32.0f;
    float lifeHeartSpacing = 10.0f;
    float heartSpacing = 8.0f;

    resourceManager.lifeText.setFont(resourceManager.font);
    resourceManager.lifeText.setString("LIFE");
    resourceManager.lifeText.setCharacterSize(16);
    sf::FloatRect lifeBounds = resourceManager.lifeText.getLocalBounds();
    float lifeTextX = resourceManager.windowBounds.x - rightPadding - lifeBounds.width;
    resourceManager.lifeText.setPosition(lifeTextX, topMargin);

    sf::Sprite tempHeart;
    tempHeart.setTexture(resourceManager.heartTexture);
    float heartWidth = tempHeart.getGlobalBounds().width;
    float totalHeartsWidth = numberOfHearts * heartWidth + (numberOfHearts - 1) * heartSpacing;
    float heartStartX = lifeTextX - lifeHeartSpacing - totalHeartsWidth;

    for (int i = 0; i < numberOfHearts; ++i) {
        sf::Sprite heart;
        heart.setTexture(resourceManager.heartTexture);
        float heartX = heartStartX + i * (heartWidth + heartSpacing);
        float heartY = topMargin;
        heart.setPosition(heartX, heartY);
        resourceManager.hearts.push_back(heart);
    }
}

void GUIHandler::draw(sf::RenderWindow& window, ResourceManager& resourceManager) {

    setGameViewport(window, resourceManager.uiView);
    window.setView(resourceManager.uiView); 

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
        updateLifeDisplay(resourceManager);
        drawGameHeader(window, resourceManager);
        drawGameFooter(window, resourceManager);
    } else {
        window.setView(window.getDefaultView());
        drawMainMenu(window, resourceManager);
    }
}


void GUIHandler::setWindowBounds(ResourceManager& resourceManager) {
    
    resourceManager.windowBounds = sf::Vector2<float>(static_cast<float>(resourceManager.windowWidth), static_cast<float>(resourceManager.windowHeight));
    resourceManager.uiView = sf::View(sf::FloatRect(0, 0, resourceManager.windowWidth, resourceManager.windowHeight));
}


void GUIHandler::setIsInGame(ResourceManager& resourceManager, bool value) {
    
    resourceManager.isInGame = value;
}

void GUIHandler::gameOverInit(ResourceManager& resourceManager) {
  
    resourceManager.gameOverText.setFont(resourceManager.font);
    resourceManager.gameOverText.setString("GAME OVER");
    resourceManager.gameOverText.setCharacterSize(64);
    resourceManager.gameOverText.setFillColor(sf::Color::Red);
    
    sf::FloatRect textBounds = resourceManager.gameOverText.getLocalBounds();
    resourceManager.gameOverText.setPosition((resourceManager.windowWidth - textBounds.width) / 2, (resourceManager.windowHeight - textBounds.height) / 2);
    
    resourceManager.restartPrompt.setFont(resourceManager.font);
    resourceManager.restartPrompt.setString("Press SPACEBAR to restart");
    resourceManager.restartPrompt.setCharacterSize(20);
    resourceManager.restartPrompt.setFillColor(sf::Color::White);
    
    sf::FloatRect promptBounds = resourceManager.restartPrompt.getLocalBounds();
    resourceManager.restartPrompt.setPosition((resourceManager.windowWidth - promptBounds.width) / 2, resourceManager.gameOverText.getPosition().y + textBounds.height + 30);
}

void GUIHandler::winInit(ResourceManager& resourceManager) {
    
    resourceManager.winText.setFont(resourceManager.font);
    resourceManager.winText.setString("CONGRATULATIONS");
    resourceManager.winText.setCharacterSize(64);
    resourceManager.winText.setFillColor(sf::Color::Yellow);
    
    sf::FloatRect congratsBounds = resourceManager.winText.getLocalBounds();
    resourceManager.winText.setPosition((resourceManager.windowWidth - congratsBounds.width) / 2,(resourceManager.windowHeight - congratsBounds.height) / 2 - 50 );

    resourceManager.winTextInstruction.setFont(resourceManager.font);
    resourceManager.winTextInstruction.setString("Level Passed!");
    resourceManager.winTextInstruction.setCharacterSize(32);
    resourceManager.winTextInstruction.setFillColor(sf::Color::White);
    
    sf::FloatRect levelBounds = resourceManager.winTextInstruction.getLocalBounds();
    resourceManager.winTextInstruction.setPosition(
        (resourceManager.windowWidth - levelBounds.width) / 2,
        resourceManager.winText.getPosition().y + congratsBounds.height + 20
    );

    resourceManager.restartPrompt.setFont(resourceManager.font);
    resourceManager.restartPrompt.setString("Press SPACEBAR to restart");
    resourceManager.restartPrompt.setCharacterSize(20);
    resourceManager.restartPrompt.setFillColor(sf::Color::White);
    

    sf::FloatRect promptBounds = resourceManager.restartPrompt.getLocalBounds();
    resourceManager.restartPrompt.setPosition((resourceManager.windowWidth - promptBounds.width) / 2, resourceManager.winTextInstruction.getPosition().y + levelBounds.height + 30);
}

void GUIHandler::drawGameOver(sf::RenderWindow& window, ResourceManager& resourceManager) {

    window.setView(window.getDefaultView());
    if (!resourceManager.gameOverInitialized) {
        gameOverInit(resourceManager); 
        resourceManager.gameOverInitialized = true;
        std::cout << "Drawing game INITIALIZED over screen" << std::endl;
    }
    
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(resourceManager.windowWidth), resourceManager.windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 50));
    window.draw(overlay);
    
    if (!resourceManager.gameOverInitialized) {
        gameOverInit(resourceManager);
        resourceManager.gameOverInitialized = true;
    }
    
    window.draw(resourceManager.gameOverText);
    window.draw(resourceManager.restartPrompt);
    resourceManager.hasRenderGameOverScreen = true;
}


void GUIHandler::drawWinScreen(sf::RenderWindow& window, ResourceManager& resourceManager) {
    
    window.setView(window.getDefaultView());
    if (!resourceManager.winScreenInitialized) {
        winInit(resourceManager); 
        resourceManager.winScreenInitialized = true;
    }
    
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(resourceManager.windowWidth), resourceManager.windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 255));
    window.draw(overlay);
    window.draw(resourceManager.winText);
    window.draw(resourceManager.winTextInstruction);
    window.draw(resourceManager.restartPrompt);
    resourceManager.hasRenderWinScreen = true;
}