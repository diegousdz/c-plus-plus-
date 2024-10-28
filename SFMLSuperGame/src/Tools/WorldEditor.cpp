#include "WorldEditor.h"

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Tilemap.h"

WorldEditor::WorldEditor(int screenHeight): tileMapWidth(0), tileSize(0), gameOverLine(0)
{
    tileMapHeight = screenHeight;
}

void WorldEditor::InitializeGameEditor()
{
}

void WorldEditor::ExitGameEditor()
{
    // Deallocating memory to prevent memory leak
    delete[] moduleWidth;
    delete[] moduleHeight;
    
    // Setting to nullptr to ensure correct clean of space memory otherwise we might get garbage
    moduleWidth = nullptr;
    moduleHeight = nullptr;
}

void WorldEditor::initTileSizeGroup()
{
    int buttonWidth = 64;
    int buttonOnePosX = 16;
    int padding = 16;
    int buttonVerticalPositions = 32;
    
    // --------------------------------------- Tittle
    
    titleEditor.setFont(fontEditor);
    titleEditor.setString("TILE SIZE");
    titleEditor.setCharacterSize(8);
    titleEditor.setPosition(16, 16);
    titleEditor.setFillColor(sf::Color::White);

    // --------------------------------------- Button 1 
    
    ButtonOne.setSize(sf::Vector2f(buttonWidth, 24));  // Button dimensions
    ButtonOne.setPosition(buttonOnePosX, buttonVerticalPositions);  // Button position
    ButtonOne.setFillColor(sf::Color(56, 56, 56));  // Button color (cyan)

    ButtonTextOne.setFont(fontEditor);
    ButtonTextOne.setString("Size 1");
    ButtonTextOne.setCharacterSize(8);
    ButtonTextOne.setPosition(padding + 8  , buttonVerticalPositions + padding /2);
    ButtonTextOne.setFillColor(sf::Color::White);

    // --------------------------------------- Button 2

    ButtonTwo.setSize(sf::Vector2f(buttonWidth, 24));  // Button dimensions
    ButtonTwo.setPosition(buttonOnePosX + buttonWidth + padding , buttonVerticalPositions);  // Button position
    ButtonTwo.setFillColor(sf::Color(56, 56, 56));  // Button color (cyan)

    ButtonTextTwo.setFont(fontEditor);
    ButtonTextTwo.setString("Size 2");
    ButtonTextTwo.setCharacterSize(8);
    ButtonTextTwo.setPosition(buttonOnePosX + buttonWidth + padding + padding * 0.5, buttonVerticalPositions + padding /2);
    
    // --------------------------------------- Button 3

    ButtonThree.setSize(sf::Vector2f(buttonWidth, 24));  // Button dimensions
    ButtonThree.setPosition((buttonWidth * 2) + (padding * 3), buttonVerticalPositions);  // Button position
    ButtonThree.setFillColor(sf::Color(56, 56, 56));  // Button color (cyan)

    ButtonTextThree.setFont(fontEditor);
    ButtonTextThree.setString("Size 2");
    ButtonTextThree.setCharacterSize(8);
    ButtonTextThree.setPosition(buttonWidth * 2 + buttonOnePosX + padding * 2 + padding * 0.5, buttonVerticalPositions + padding /2);

}

void WorldEditor::initTileMiniViewport()
{
    int baseTileWidth = 256;
    int baseTilePositionY = 64;
    int topHeaderHeight = baseTileWidth / 4;

    // --------------------------------------- Base Tile

    miniViewportBaseTile.setSize(sf::Vector2f(baseTileWidth, baseTileWidth));  // Button dimensions
    miniViewportBaseTile.setPosition(0, baseTilePositionY);  // Button position
    miniViewportBaseTile.setFillColor(sf::Color(56, 56, 56));

    gamePreview.setSize(sf::Vector2f(baseTileWidth, baseTileWidth ));  // Button dimensions
    gamePreview.setPosition(0, baseTilePositionY);  // Button position
    gamePreview.setFillColor(sf::Color(48, 48, 48));

    topHeader.setSize(sf::Vector2f(baseTileWidth, topHeaderHeight ));
    topHeader.setPosition(0, baseTilePositionY);
    topHeader.setFillColor(sf::Color(56, 56, 56));

    magicBelt.setSize(sf::Vector2f(baseTileWidth, topHeaderHeight ));
    magicBelt.setPosition(0, baseTileWidth );
    magicBelt.setFillColor(sf::Color(56, 56, 56));
}

void WorldEditor::initDebugConsole()
{
    int baseTileWidth = 256;
    int baseTilePositionY = baseTileWidth + 86;
    int paddingLoadTile = 8;
    baseDebugConsole.setSize(sf::Vector2f(256, 64));  // Button dimensions
    baseDebugConsole.setPosition(0, baseTilePositionY );  // Button position
    baseDebugConsole.setFillColor(sf::Color(8, 8, 8));  // Button color (cyan)

    texDebugConsole.setFont(fontEditor);
    texDebugConsole.setString("Logs: ");
    texDebugConsole.setCharacterSize(8);
    texDebugConsole.setPosition(16, baseTilePositionY + paddingLoadTile);
    texDebugConsole.setFillColor(sf::Color::Green);
}

void WorldEditor::initLoadTilemap()
{
    int baseTileWidth = 256;
    int baseTilePositionY = baseTileWidth + 64;
    int paddingLoadTile = 8;

    baseLoadTilemap.setSize(sf::Vector2f(256, 24));  // Button dimensions
    baseLoadTilemap.setPosition(0, baseTilePositionY );  // Button position
    baseLoadTilemap.setFillColor(sf::Color(32, 32, 32));  // Button color (cyan)

    instructionLoadTilemap.setFont(fontEditor);
    instructionLoadTilemap.setString("Load tilemap");
    instructionLoadTilemap.setCharacterSize(8);
    instructionLoadTilemap.setPosition(16, baseTilePositionY + paddingLoadTile);
    instructionLoadTilemap.setFillColor(sf::Color::White);

    float textWidth = instructionLoadTilemap.getGlobalBounds().width;
    
    buttonLoadTilemap.setSize(sf::Vector2f(64, 16));  // Button dimensions
    buttonLoadTilemap.setPosition(textWidth + 32, baseTilePositionY + paddingLoadTile * 0.5);  // Button position
    buttonLoadTilemap.setFillColor(sf::Color(86, 86, 86));
    
    buttonTextLoadTile.setFont(fontEditor);
    buttonTextLoadTile.setString("Search");
    buttonTextLoadTile.setCharacterSize(8);
    buttonTextLoadTile.setPosition(textWidth + 32 + paddingLoadTile, baseTilePositionY + paddingLoadTile);
    buttonTextLoadTile.setFillColor(sf::Color::White);
}

void WorldEditor::init()
{
    std::cerr << "Init!" << std::endl;
    if (!fontEditor.loadFromFile("res/fonts/PressStart2P-Regular.ttf"))
    {
        std::cout << "Failed to load font!" << std::endl;
    }
    initTileSizeGroup();
    initTileMiniViewport();
    initLoadTilemap();
    initDebugConsole();
   // Tilemap tilemap;
    // Initialize tilemap
    //tilemap.InstantiateATilemapByType(1);
/*
    // Example: Initialize a single tile shape for rendering (32x32 grid tiles)
    gridTile.setSize(sf::Vector2f(32, 32));
    gridTile.setFillColor(sf::Color::Transparent);  // Make it transparent
    gridTile.setOutlineColor(sf::Color::White);  // Add a grid outline
    gridTile.setOutlineThickness(1);
*/
    // Load a font for text display (use your own font path)
}


void  WorldEditor::drawTileSizeGroup(sf::RenderWindow& window) const
{
    window.draw(titleEditor);
    
    window.draw(ButtonOne);
    window.draw(ButtonTextOne);
    
    window.draw(ButtonTwo);
    window.draw(ButtonTextTwo);
    
    window.draw(ButtonThree);
    window.draw(ButtonTextThree);
}

void  WorldEditor::drawTileMiniViewport(sf::RenderWindow& window) const
{
    window.draw(miniViewportBaseTile);
    window.draw(gamePreview);
    window.draw(topHeader);
    window.draw(magicBelt);
}

void WorldEditor::drawTileLoadTilemap(sf::RenderWindow& window) const
{
    window.draw(baseLoadTilemap);
    window.draw(instructionLoadTilemap);
    window.draw(buttonLoadTilemap);
    window.draw(buttonTextLoadTile);
}

void WorldEditor::drawDebugConsole(sf::RenderWindow& window) const
{
    window.draw(baseDebugConsole);
    window.draw(texDebugConsole);
}

void WorldEditor::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color(32, 32, 32));
    drawTileSizeGroup(window);
    drawTileMiniViewport(window);
    drawTileLoadTilemap(window);
    drawDebugConsole(window);
}

// Function to create a new window and tilemap based on the size
void WorldEditor::createTilemap(int tileSizeType)
{
    // Define the size of the tilemap based on the tileSizeType
    
    Tilemap tilemap;
    
     switch (tileSizeType)
    {
        case 1:
            tilemap.InstantiateATilemapByType(1);  // Short tilemap (1800 wide)
            break;
        case 2:
            tilemap.InstantiateATilemapByType(2);  // Medium tilemap (2400 wide)
            break;
        case 3:
            tilemap.InstantiateATilemapByType(3);  // Long tilemap (3600 wide)
            break;
        default:
            std::cout << "Invalid tile size!" << std::endl;
            return;
    } 

    // Create a new window with hardcoded size for now (you can adjust this)
    tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
}

void WorldEditor::Update(sf::RenderWindow &window, sf::Event event)
{
    // save mouse position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    
    // Check if mouse is hovering over ButtonOne
    if (ButtonOne.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        // If the mouse is over the button, now check if the button is pressed
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button One Clicked!" << std::endl;
            // Handle your button click action here
            tileSizeType = 1;
            
            if(!hasCreatedTilemap)
            {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
              
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button One Released!" << std::endl;
            // Handle your button click action here
        }
    } 

    // Check ButtonTwo
    if (ButtonTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {

        // Check if ButtonTwo is clicked
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Two Clicked!" << std::endl;
            tileSizeType = 2;
            if(!hasCreatedTilemap)
            {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
        }

        // Check if ButtonTwo is released
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Two Released!" << std::endl;

        }
    } 

    // Check ButtonThree
    if (ButtonThree.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {

        // Check if ButtonThree is clicked
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Three Clicked!" << std::endl;
            tileSizeType = 3;
            if(!hasCreatedTilemap)
            {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
        }

        // Check if ButtonThree is released
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Three Released!" << std::endl;
         
        }
    } 

    switch (tileSizeType)
    {
    case 1:
        ButtonOne.setFillColor(sf::Color(128 , 128, 128));
        ButtonTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonThree.setFillColor(sf::Color(56, 56, 56));
        break;
    case 2:
        ButtonOne.setFillColor(sf::Color(56, 56, 56));
        ButtonTwo.setFillColor(sf::Color(128 , 128, 128));
        ButtonThree.setFillColor(sf::Color(56, 56, 56));
        break;
    case 3:
        ButtonOne.setFillColor(sf::Color(56, 56, 56));      // Button One inactive
        ButtonTwo.setFillColor(sf::Color(56, 56, 56));      // Button Two inactive
        ButtonThree.setFillColor(sf::Color(128 , 128, 128));
        break;
    default:
        ButtonOne.setFillColor(sf::Color(56, 56, 56));
        ButtonTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonThree.setFillColor(sf::Color(56, 56, 56));

        std::cout << "Invalid tile size type!" << std::endl;
        break;
    }

    
}
