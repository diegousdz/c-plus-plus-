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

void GUIHandler::updateHealthBar(ResourceManager& resourceManager) {
    float healthPercentage = resourceManager.newGamePlayer.health / 100.0f;

    // Ensure healthPercentage is within [0, 1]
    if (healthPercentage < 0.0f) healthPercentage = 0.0f;
    if (healthPercentage > 1.0f) healthPercentage = 1.0f;

    float healthBarWidth = resourceManager.healthBarBorder.getSize().x;
    float healthBarHeight = resourceManager.healthBarBorder.getSize().y;

    // Update the width of the health bar fill
    resourceManager.healthBarFill.setSize(sf::Vector2f(healthBarWidth * healthPercentage, healthBarHeight));

    // Update the color of the health bar fill based on health percentage
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

    // Set up hearts
    float lifeHeartSpacing = 10.0f;
    sf::Sprite tempHeart;
    tempHeart.setTexture(resourceManager.heartTexture);
    float heartWidth = tempHeart.getGlobalBounds().width;
    float heartHeight = tempHeart.getGlobalBounds().height;
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
    
/* WAITING FOR PATCH AND FOR BATTLE 
    // --- HEALTH Text and Bar ---
    // Set up "HEALTH" text 
    resourceManager.healthText.setFont(resourceManager.font);
    resourceManager.healthText.setString("HEALTH");
    resourceManager.healthText.setCharacterSize(16);
    sf::FloatRect healthBounds = resourceManager.healthText.getLocalBounds();

    // Dimensions for health bar
    float healthBarWidth = 100.0f;
    float healthBarHeight = 20.0f;
    float healthBarSpacing = 10.0f;

    // Calculate total width needed
    float totalHealthWidth = healthBarWidth + healthBarSpacing + healthBounds.width;

    // Adjust healthTextX to ensure the combined width fits within the window
    float healthBarX = resourceManager.windowBounds.x - rightPadding - totalHealthWidth;
    float healthTextX = healthBarX + healthBarWidth + healthBarSpacing;
    float healthTextY = topMargin + 32.0f;
    resourceManager.healthText.setPosition(healthTextX, healthTextY);

    // Position health bar
    float healthBarY = healthTextY + (healthBounds.height - healthBarHeight) / 2.0f;
    resourceManager.healthBarBorder.setSize(sf::Vector2f(healthBarWidth, healthBarHeight));
    resourceManager.healthBarBorder.setPosition(healthBarX, healthBarY);
    resourceManager.healthBarBorder.setFillColor(sf::Color::Transparent);
    resourceManager.healthBarBorder.setOutlineColor(sf::Color::White);
    resourceManager.healthBarBorder.setOutlineThickness(2.0f);

    resourceManager.healthBarFill.setSize(sf::Vector2f(healthBarWidth, healthBarHeight));
    resourceManager.healthBarFill.setPosition(healthBarX, healthBarY);
    resourceManager.healthBarFill.setFillColor(sf::Color::Green);
    */
    // --- ENERGY Text ---
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


void GUIHandler::drawMainMenu(sf::RenderWindow &window, ResourceManager &resourceManager)
{
    // Set up the menu items
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
    
  //  window.draw(resourceManager.healthBarBorder);
  //  window.draw(resourceManager.healthBarFill);
    

  //  window.draw(resourceManager.healthText);
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
    gameView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); // Fullscreen viewport
}

void GUIHandler::updateLifeDisplay(ResourceManager& resourceManager) {
    int numberOfHearts = resourceManager.newGamePlayer.life;

    // Clear the existing hearts
    resourceManager.hearts.clear();

    // Recalculate positions and add hearts based on the current life
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
    float heartHeight = tempHeart.getGlobalBounds().height;
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
    // Paso 1: Configurar el viewport y la vista del juego primero
    setGameViewport(window, resourceManager.uiView); // Configura el viewport (Recorte del área del juego)
    window.setView(resourceManager.uiView); // Establecer la vista recortada para el juego

    // Paso 2: Inicializar la interfaz del menú principal si aún no se ha inicializado y no está en el juego
    if (!resourceManager.variablesDrawInitializedMainMenu && !resourceManager.isInGame) {
        setWindowBounds(resourceManager);
        mainMenuInit(resourceManager);
        drawMainMenu(window, resourceManager);
        resourceManager.variablesDrawInitializedMainMenu = true;
    }

    // Paso 3: Inicializar encabezado y pie de página del juego si está en juego pero no inicializados aún
    if (!resourceManager.variablesDrawInitializedGame && resourceManager.isInGame) {
        gameHeaderInit(resourceManager);
     //   gameFooterInit(resourceManager);
        resourceManager.variablesDrawInitializedGame = true;
    }

    // Paso 4: Dibujar los elementos del juego
    if (resourceManager.isInGame) {
       // updateHealthBar(resourceManager);
        updateLifeDisplay(resourceManager);
        drawGameHeader(window, resourceManager); // Dibujar encabezado del juego
        drawGameFooter(window, resourceManager); // Dibujar pie de página del juego
    } else {
        // Si no está en el juego, usar la vista por defecto para dibujar el menú principal
        window.setView(window.getDefaultView());
        drawMainMenu(window, resourceManager);
    }
}


void GUIHandler::setWindowBounds(ResourceManager& resourceManager) {
    resourceManager.windowBounds = sf::Vector2<float>(
        static_cast<float>(resourceManager.windowWidth),
        static_cast<float>(resourceManager.windowHeight)
    );
    
    resourceManager.uiView = sf::View(sf::FloatRect(0, 0, resourceManager.windowWidth, resourceManager.windowHeight));
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