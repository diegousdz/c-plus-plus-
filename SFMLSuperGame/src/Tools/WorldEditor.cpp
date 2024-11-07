#include "WorldEditor.h"

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <windows.h>

#include "Tilemap.h"

// ------------------------------------------------------------------------------- Class constructor
WorldEditor::WorldEditor(int screenHeight): tileMapWidth(0), tileSize(0), gameOverLine(0)
{
    tileMapHeight = screenHeight;
    setCellSize(8);
    previousCellSize = 0;
}
// ------------------------------------------------------------------------------- Init functions

void WorldEditor::toggleMode() {
    isTextureMode = !isTextureMode;

    if(isTextureMode) {
    ButtonRotateTwo.setFillColor(sf::Color(128 , 128, 128));
    }
    if(!isTextureMode) {
    ButtonRotateTwo.setFillColor(sf::Color(56, 56, 56));
    }
}

// In WorldEditor.cpp
void WorldEditor::initTileTextures() {
    // Paths to texture files, adjust according to your project's structure

    // Load each texture into the tileTextures array
    for (int i = 0; i < NUM_TEXTURES; ++i) {
        if (!tileTextures[i].loadFromFile(textures[i])) {
            std::cerr << "Failed to load texture: " << textures[i].toAnsiString() << std::endl;
        } else {
            std::cout << "Successfully loaded texture: " << textures[i].toAnsiString() << std::endl;
            // asign the texture to a sprite that will be created as new and then added in the position and scale of the Button that match the index
        }
    }
}
void WorldEditor::initLoadTilemap()
{
    int baseTilePositionY = 0;
    int paddingLoadTile = 8;
    
    baseLoadTilemap.setSize(sf::Vector2f(256, 24));
    baseLoadTilemap.setPosition(0, static_cast<float>(baseTilePositionY));
    baseLoadTilemap.setFillColor(sf::Color(32, 32, 32));

    textTilemap.setFont(fontEditor);
    textTilemap.setString("TILEMAP");
    textTilemap.setCharacterSize(8);
    textTilemap.setPosition(16, static_cast<float>(baseTilePositionY) + paddingLoadTile);
    textTilemap.setFillColor(sf::Color::White);

    float textWidth = textTilemap.getGlobalBounds().width;

    buttonLoad.setSize(sf::Vector2f(64, 16));
    buttonLoad.setPosition(textWidth + 32, baseTilePositionY + paddingLoadTile * 0.5);
    buttonLoad.setFillColor(sf::Color(86, 86, 86));

    buttonTextLoad.setFont(fontEditor);
    buttonTextLoad.setString("Load");
    buttonTextLoad.setCharacterSize(8);
    buttonTextLoad.setPosition(textWidth + 32 + (paddingLoadTile * 2), static_cast<float>(baseTilePositionY) + paddingLoadTile);
    buttonTextLoad.setFillColor(sf::Color::White);

    buttonSave.setSize(sf::Vector2f(64, 16));
    buttonSave.setPosition(buttonTextLoad.getPosition().x + 64 + static_cast<float>(paddingLoadTile), baseTilePositionY + paddingLoadTile * 0.5);
    buttonSave.setFillColor(sf::Color(86, 86, 86));

    buttonTextSave.setFont(fontEditor);
    buttonTextSave.setString("Save");
    buttonTextSave.setCharacterSize(8);
    buttonTextSave.setPosition(buttonSave.getPosition().x + 8, baseTilePositionY + paddingLoadTile);
    buttonTextSave.setFillColor(sf::Color::White);

    sectionLoadTilemapHeight = baseLoadTilemap.getSize().y + paddingLoadTile * 2;
}

void WorldEditor::initTileSizeGroup()
{
    int buttonWidth = 64;
    int padding = 16;
    int buttonVerticalPositionY = sectionLoadTilemapHeight + padding;

    titleEditor.setFont(fontEditor);
    titleEditor.setString("TILEMAP SIZE");
    titleEditor.setCharacterSize(8);
    titleEditor.setPosition(16, buttonVerticalPositionY - padding);
    titleEditor.setFillColor(sf::Color::White);

    buttonOneFileSize.setSize(sf::Vector2f(buttonWidth, 24));
    buttonOneFileSize.setPosition(16, buttonVerticalPositionY);
    buttonOneFileSize.setFillColor(sf::Color(56, 56, 56));

    buttonTextOneFileSize.setFont(fontEditor);
    buttonTextOneFileSize.setString("Size 1");
    buttonTextOneFileSize.setCharacterSize(8);
    buttonTextOneFileSize.setPosition(buttonOneFileSize.getPosition().x + 8, buttonOneFileSize.getPosition().y + padding / 2);
    buttonTextOneFileSize.setFillColor(sf::Color::White);

    buttonTwoFileSize.setSize(sf::Vector2f(buttonWidth, 24));
    buttonTwoFileSize.setPosition(buttonOneFileSize.getPosition().x + buttonWidth + padding, buttonVerticalPositionY);
    buttonTwoFileSize.setFillColor(sf::Color(56, 56, 56));

    buttonTextTwoFileSize.setFont(fontEditor);
    buttonTextTwoFileSize.setString("Size 2");
    buttonTextTwoFileSize.setCharacterSize(8);
    buttonTextTwoFileSize.setPosition(buttonTwoFileSize.getPosition().x + 8, buttonTwoFileSize.getPosition().y + padding / 2);
    buttonTextTwoFileSize.setFillColor(sf::Color::White);

    buttonThreeFileSize.setSize(sf::Vector2f(buttonWidth, 24));
    buttonThreeFileSize.setPosition(buttonTwoFileSize.getPosition().x + buttonWidth + padding, buttonVerticalPositionY);
    buttonThreeFileSize.setFillColor(sf::Color(56, 56, 56));

    buttonTextThreeFileSize.setFont(fontEditor);
    buttonTextThreeFileSize.setString("Size 3");
    buttonTextThreeFileSize.setCharacterSize(8);
    buttonTextThreeFileSize.setPosition(buttonThreeFileSize.getPosition().x + 8, buttonThreeFileSize.getPosition().y + padding / 2);
    buttonTextThreeFileSize.setFillColor(sf::Color::White);

    sectionTileSizeHeight = buttonOneFileSize.getSize().y + padding;
}

void WorldEditor::initGridSizeGroup()
{
    int buttonWidth = 64;
    int padding = 16;
    int buttonVerticalPositionY = sectionLoadTilemapHeight + sectionTileSizeHeight + padding * 2;

    // Set the position for the title text properly
    titleGrid.setFont(fontEditor);
    titleGrid.setString("GRID SIZE");
    titleGrid.setCharacterSize(8);
    titleGrid.setPosition(16, buttonVerticalPositionY - padding); // Adjusted position for the title
    titleGrid.setFillColor(sf::Color::White);

    ButtonOneGrid.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonOneGrid.setPosition(16, buttonVerticalPositionY);
    ButtonOneGrid.setFillColor(sf::Color(56, 56, 56));

    ButtonTextOneGrid.setFont(fontEditor);
    ButtonTextOneGrid.setString("Cell 8");
    ButtonTextOneGrid.setCharacterSize(8);
    ButtonTextOneGrid.setPosition(ButtonOneGrid.getPosition().x + 8, ButtonOneGrid.getPosition().y + padding / 2);
    ButtonTextOneGrid.setFillColor(sf::Color::White);

    ButtonTwoGrid.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonTwoGrid.setPosition(ButtonOneGrid.getPosition().x + buttonWidth + padding, buttonVerticalPositionY);
    ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));

    ButtonTextTwoGrid.setFont(fontEditor);
    ButtonTextTwoGrid.setString("Cell 16");
    ButtonTextTwoGrid.setCharacterSize(8);
    ButtonTextTwoGrid.setPosition(ButtonTwoGrid.getPosition().x + 4, ButtonTwoGrid.getPosition().y + padding / 2);
    ButtonTextTwoGrid.setFillColor(sf::Color::White);

    ButtonThreeGrid.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonThreeGrid.setPosition(ButtonTwoGrid.getPosition().x + buttonWidth + padding, buttonVerticalPositionY);
    ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));

    ButtonTextThreeGrid.setFont(fontEditor);
    ButtonTextThreeGrid.setString("Cell 32");
    ButtonTextThreeGrid.setCharacterSize(8);
    ButtonTextThreeGrid.setPosition(ButtonThreeGrid.getPosition().x + 4, ButtonThreeGrid.getPosition().y + padding / 2);
    ButtonTextThreeGrid.setFillColor(sf::Color::White);
}

void WorldEditor::initTileMiniViewport()
{
    int baseTileWidth = 256;
    int baseTilePositionY = sectionLoadTilemapHeight + sectionTileSizeHeight + 64;
    int topHeaderHeight = baseTileWidth / 4;

    miniViewportBaseTile.setSize(sf::Vector2f(baseTileWidth, baseTileWidth));
    miniViewportBaseTile.setPosition(0, baseTilePositionY);
    miniViewportBaseTile.setFillColor(sf::Color(56, 56, 56));

    gamePreview.setSize(sf::Vector2f(baseTileWidth, baseTileWidth));
    gamePreview.setPosition(0, baseTilePositionY);
    gamePreview.setFillColor(sf::Color(48, 48, 48));

    topHeader.setSize(sf::Vector2f(static_cast<float>(baseTileWidth), static_cast<float>(topHeaderHeight)));
    topHeader.setPosition(0, static_cast<float>(baseTilePositionY));
    topHeader.setFillColor(sf::Color(56, 56, 56));

    magicBelt.setSize(sf::Vector2f(static_cast<float>(baseTileWidth), static_cast<float>(topHeaderHeight)));
    magicBelt.setPosition(0, static_cast<float>(baseTilePositionY) + static_cast<float>(baseTileWidth));
    magicBelt.setFillColor(sf::Color(56, 56, 56));
}

void WorldEditor::initDebugConsole() {
    int baseTileWidth = 256;
    int baseTilePositionY = sectionLoadTilemapHeight + sectionTileSizeHeight + 256 + 96;
    int paddingLoadTile = 8;

    baseDebugConsole.setSize(sf::Vector2f(baseTileWidth, 64));
    baseDebugConsole.setPosition(0, baseTilePositionY);
    baseDebugConsole.setFillColor(sf::Color(8, 8, 8));

    texDebugConsole.setFont(fontEditor);
    texDebugConsole.setString("Logs:");
    texDebugConsole.setCharacterSize(8);
    texDebugConsole.setPosition(16, baseTilePositionY + paddingLoadTile);
    texDebugConsole.setFillColor(sf::Color::Green);

    consoleInput = ""; // Initialize with an empty string
    isConsoleActive = true; // Set console to be active for input initially
}

void WorldEditor::initSectionMap()
{
    // Use MiniViewport dimensions
    int baseTilePositionY = static_cast<float>(sectionLoadTilemapHeight) + sectionTileSizeHeight + 64;
    float baseX = 16;
    float buttonWidth = 30;  // Assuming a width; update as needed
    float paddingBetweenButtons = 8; // Adjust padding between buttons
    float baseY = baseTilePositionY + paddingBetweenButtons + titleSection.getGlobalBounds().height + paddingBetweenButtons;

    // Title for the section
    titleSection.setFont(fontEditor);
    titleSection.setString("SELECT MAP");
    titleSection.setCharacterSize(8);
    titleSection.setFillColor(sf::Color::White);
    titleSection.setPosition(16, baseTilePositionY + paddingBetweenButtons);
    // Use MiniViewport dimensions
 
    // Set positions for each button, adding up widths and padding

    ButtonSectionOne.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonSectionOne.setPosition(baseX, baseY + paddingBetweenButtons);
    ButtonSectionOne.setFillColor(sf::Color(100, 100, 100));

    ButtonSectionTwo.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonSectionTwo.setPosition(baseX + buttonWidth + paddingBetweenButtons, baseY + paddingBetweenButtons);
    ButtonSectionTwo.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionThree.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonSectionThree.setPosition(baseX + 2 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionThree.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionFour.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonSectionFour.setPosition(baseX + 3 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionFour.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionFive.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonSectionFive.setPosition(baseX + 4 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionFive.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionSix.setSize(sf::Vector2f(buttonWidth, 24));
    ButtonSectionSix.setPosition(baseX + 5 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionSix.setFillColor(sf::Color(28, 28, 28));

}

void WorldEditor::initBrushes()
{
    int buttonWidth = 30;
    int buttonHeight = 24;
    float paddingBetweenButtons = 8;
    float baseX = 16;
    float baseY = 222;  // Adding 8 pixels to baseY for extra space between title and buttons

    // Title setup
    titleBrushed.setFont(fontEditor);
    titleBrushed.setString("TILE TEXTURES");
    titleBrushed.setCharacterSize(8);
    titleBrushed.setPosition(baseX, 210);
    titleBrushed.setFillColor(sf::Color::White);

    // Calculate vertical positioning for each row
    float firstRowY = baseY + paddingBetweenButtons;
    float secondRowY = firstRowY + buttonHeight + paddingBetweenButtons;
    float thirdRowY = secondRowY + buttonHeight + paddingBetweenButtons;

    // First row of texture buttons
    ButtonTextureOne.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureOne.setPosition(baseX, firstRowY);
    ButtonTextureOne.setFillColor(sf::Color(100, 100, 100));

    ButtonTextureTwo.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureTwo.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 1, firstRowY);
    ButtonTextureTwo.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureThree.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureThree.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 2, firstRowY);
    ButtonTextureThree.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFour.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureFour.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 3, firstRowY);
    ButtonTextureFour.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFive.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureFive.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 4, firstRowY);
    ButtonTextureFive.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureSix.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureSix.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 5, firstRowY);
    ButtonTextureSix.setFillColor(sf::Color(28, 28, 28));

    // Second row of texture buttons
    ButtonTextureSeven.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureSeven.setPosition(baseX, secondRowY);
    ButtonTextureSeven.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureEight.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureEight.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 1, secondRowY);
    ButtonTextureEight.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureNine.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureNine.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 2, secondRowY);
    ButtonTextureNine.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureTen.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureTen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 3, secondRowY);
    ButtonTextureTen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureEleven.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureEleven.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 4, secondRowY);
    ButtonTextureEleven.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureTwelve.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureTwelve.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 5, secondRowY);
    ButtonTextureTwelve.setFillColor(sf::Color(28, 28, 28));

    // Third row of texture buttons
    ButtonTextureThirteen.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureThirteen.setPosition(baseX, thirdRowY);
    ButtonTextureThirteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFourteen.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureFourteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 1, thirdRowY);
    ButtonTextureFourteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFifteen.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureFifteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 2, thirdRowY);
    ButtonTextureFifteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureSixteen.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureSixteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 3, thirdRowY);
    ButtonTextureSixteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureSeventeen.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureSeventeen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 4, thirdRowY);
    ButtonTextureSeventeen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureEighteen.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonTextureEighteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 5, thirdRowY);
    ButtonTextureEighteen.setFillColor(sf::Color(28, 28, 28));

    for (int i = 0; i < NUM_TEXTURES; ++i) {
        // Ensure tileSprites is positioned and sized to match each button but rendered on top
        tileSprites[i].setPosition(buttons[i]->getPosition());
        tileSprites[i].setScale(buttons[i]->getScale()/2.0f);

        // Set any necessary Z-order for tileSprites, depending on the rendering system
        // Alternatively, apply a color overlay or any visual style here to distinguish it.
    }
}

void WorldEditor::initRotationControls()
{
    int buttonWidth = 48;
    int buttonHeight = 24;
    int padding = 16;
    int baseX = 16;
    int baseY = 336;

    // Title for the rotation section
    titleRotation.setFont(fontEditor);
    titleRotation.setString("SPRITE VISIBILITY & ROTATION");
    titleRotation.setCharacterSize(8);
    titleRotation.setFillColor(sf::Color::White);
    titleRotation.setPosition(baseX, baseY);

    // Calculate the Y position for the buttons, below the title
    float buttonStartY = baseY + titleRotation.getGlobalBounds().height + padding / 2;

    // Configure buttons and their labels with angle text
    // Button: -90 (Left)
    ButtonRotateOne.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonRotateOne.setPosition(baseX, buttonStartY);
    ButtonRotateOne.setFillColor(sf::Color(56, 56, 56));

    titleRotationLeft.setFont(fontEditor);
    titleRotationLeft.setString("See C");
    titleRotationLeft.setCharacterSize(8);
    titleRotationLeft.setFillColor(sf::Color::White);
    titleRotationLeft.setPosition(
        ButtonRotateOne.getPosition().x + buttonWidth / 2 - titleRotationLeft.getGlobalBounds().width / 2,
        ButtonRotateOne.getPosition().y + (buttonHeight / 4)
    );

    // Button: 90 (Right)
    ButtonRotateTwo.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonRotateTwo.setPosition(baseX + buttonWidth + padding / 2, buttonStartY);
    ButtonRotateTwo.setFillColor(sf::Color(56, 56, 56));

    titleRotationRight.setFont(fontEditor);
    titleRotationRight.setString("See T");
    titleRotationRight.setCharacterSize(8);
    titleRotationRight.setFillColor(sf::Color::White);
    titleRotationRight.setPosition(
        ButtonRotateTwo.getPosition().x + buttonWidth / 2 - titleRotationRight.getGlobalBounds().width / 2,
        ButtonRotateTwo.getPosition().y + (buttonHeight / 4)
    );

    // Button: 0 (Top)
    ButtonRotateThree.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonRotateThree.setPosition(baseX + 2 * (buttonWidth + padding / 2), buttonStartY);
    ButtonRotateThree.setFillColor(sf::Color(56, 56, 56));

    titleRotationTop.setFont(fontEditor);
    titleRotationTop.setString("- Y");
    titleRotationTop.setCharacterSize(8);
    titleRotationTop.setFillColor(sf::Color::White);
    titleRotationTop.setPosition(
        ButtonRotateThree.getPosition().x + buttonWidth / 2 - titleRotationTop.getGlobalBounds().width / 2,
        ButtonRotateThree.getPosition().y + (buttonHeight / 4)
    );

    // Button: 180 (Bottom)
    ButtonRotateFour.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    ButtonRotateFour.setPosition(baseX + 3 * (buttonWidth + padding / 2), buttonStartY);
    ButtonRotateFour.setFillColor(sf::Color(56, 56, 56));

    titleRotationBottom.setFont(fontEditor); 
    titleRotationBottom.setString("- X");
    titleRotationBottom.setCharacterSize(8);
    titleRotationBottom.setFillColor(sf::Color::White);
    titleRotationBottom.setPosition(
        ButtonRotateFour.getPosition().x + buttonWidth / 2 - titleRotationBottom.getGlobalBounds().width / 2,
        ButtonRotateFour.getPosition().y + (buttonHeight / 4)
    );
}

void WorldEditor::onSaveButtonClick() {
    if (!newGameMap) {
        std::cerr << "Error: No GameMap to save." << std::endl;
        return;
    }

    if (!newGameMap->sections) {
        std::cerr << "Error: No sections array exists." << std::endl;
        return;
    }

    for (int i = 0; i < NUM_TEXTURES; i++) {
        // Save the default texture paths if they're not already set
        if (newGameMap->texturesPath[i] == "none") {
            newGameMap->texturesPath[i] = textures[i];  // Adjust path as needed
        }
    }

    newGameMap->saveToFile("res/data", "gameMap");

    std::cout << "Saving " << newGameMap->mapSections << " sections..." << std::endl;

    for (int i = 0; i < newGameMap->mapSections; i++) {
        if (!newGameMap->sections[i]) {
            std::cerr << "Section " << i << " is nullptr, skipping save." << std::endl;
            continue;
        }

        std::string sectionFileName = "mapSection_" + std::to_string(i);
        try {
            if (newGameMap->sections[i]->saveToFile("res/data", sectionFileName)) {
                std::cout << "Section " << i << " saved successfully" << std::endl;
            } else {
                std::cerr << "Failed to save section " << i << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error saving section " << i << ": " << e.what() << std::endl;
        }
    }
}

void WorldEditor::initVariablesToSave()
{
    // Initialize GameMap with default values
    tilemap.allocateGameMap(8, 512, 512, 1);
    newGameMap = tilemap.getGameMap();

    if (newGameMap) {
        newMapSection = newGameMap->sections;

        // Debug information to verify allocation
        std::cout << "GameMap allocated with cell size: " << newGameMap->cellSize
                  << ", screen dimensions: " << newGameMap->screenWidth << "x" << newGameMap->screenHeight
                  << ", map size: " << newGameMap->mapSize << std::endl;

        if (newMapSection) {
            std::cout << "MapSection array allocated with " << newMapSection << " sections." << std::endl;
            
        } else {
            std::cerr << "Error: MapSection array not allocated." << std::endl;
        }
    }
}

// ------------------------------------------------------------------------------- Init function 
void WorldEditor::init()
{
    std::cerr << "Init!" << std::endl;
    if (!fontEditor.loadFromFile("res/fonts/PressStart2P-Regular.ttf"))
    {
        std::cout << "Failed to load font!" << std::endl;
    } else
    {
        std::cout << "Font loaded  successfully " << std::endl;
    }
    initTileTextures();
    initVariablesToSave();
    initLoadTilemap();
    initTileSizeGroup();
    initGridSizeGroup();
    initSectionMap();
    initBrushes();
    initRotationControls();
    initDebugConsole();
}
// ------------------------------------------------------------------------------- Draw functions
void WorldEditor::drawTileSizeGroup(sf::RenderWindow& window) const
{
    window.draw(titleEditor);
    
    window.draw(buttonOneFileSize);
    window.draw(buttonTextOneFileSize);
    
    window.draw(buttonTwoFileSize);
    window.draw(buttonTextTwoFileSize);
    
    window.draw(buttonThreeFileSize);
    window.draw(buttonTextThreeFileSize);
}
void WorldEditor::drawTileGridGroup(sf::RenderWindow& window) const
{

    window.draw(titleGrid);
    
    window.draw(gridTile);
    
    window.draw(ButtonOneGrid);
    window.draw(ButtonTextOneGrid);
    
    window.draw(ButtonTwoGrid);
    window.draw(ButtonTextTwoGrid);
    
    window.draw(ButtonThreeGrid);
    window.draw(ButtonTextThreeGrid);
}
void WorldEditor::drawTileMiniViewport(sf::RenderWindow& window) const
{
    window.draw(miniViewportBaseTile);
    window.draw(gamePreview);
    window.draw(topHeader);
    window.draw(magicBelt);
}
void WorldEditor::drawTileLoadTilemap(sf::RenderWindow& window) const
{
    window.draw(baseLoadTilemap);
    window.draw(textTilemap);
    window.draw(buttonLoad);
    window.draw(buttonTextLoad);
    window.draw(buttonSave);
    window.draw(buttonTextSave);

}
void WorldEditor::drawDebugConsole(sf::RenderWindow& window) const
{
    window.draw(baseDebugConsole);
    window.draw(texDebugConsole);
}
void WorldEditor::drawSectionMap(sf::RenderWindow& window) const
{
    if(tileSizeType == 1)
    {
        window.draw(titleSection);
        window.draw(ButtonSectionOne);
        window.draw(ButtonSectionTwo);
    }
    if(tileSizeType == 2)
    {
        window.draw(titleSection);
        window.draw(ButtonSectionOne);
        window.draw(ButtonSectionTwo);
        window.draw(ButtonSectionThree);
        window.draw(ButtonSectionFour);
    }
    if(tileSizeType == 3)
    {
        window.draw(titleSection);
        window.draw(ButtonSectionOne);
        window.draw(ButtonSectionTwo);
        window.draw(ButtonSectionThree);
        window.draw(ButtonSectionFour);
        window.draw(ButtonSectionFive);
        window.draw(ButtonSectionSix);
    }
}

void WorldEditor::drawBrushesTexture(sf::RenderWindow& window)
{
    window.draw(titleBrushed);
    
    // First row of texture buttons
    window.draw(ButtonTextureOne);
    window.draw(ButtonTextureTwo);
    window.draw(ButtonTextureThree);
    window.draw(ButtonTextureFour);
    window.draw(ButtonTextureFive);
    window.draw(ButtonTextureSix);
    
    // Second row of texture buttons
    window.draw(ButtonTextureSeven);
    window.draw(ButtonTextureEight);
    window.draw(ButtonTextureNine);
    window.draw(ButtonTextureTen);
    window.draw(ButtonTextureEleven);
    window.draw(ButtonTextureTwelve);
    
    // Third row of texture buttons
    window.draw(ButtonTextureThirteen);
    window.draw(ButtonTextureFourteen);
    window.draw(ButtonTextureFifteen);
    window.draw(ButtonTextureSixteen);
    window.draw(ButtonTextureSeventeen);
    window.draw(ButtonTextureEighteen);

    for (int i = 0; i < NUM_TEXTURES; ++i) {
      window.draw(tileSprites[i]);
    }
}

void WorldEditor::drawRotationControls(sf::RenderWindow& window) const
{
    // Draw title for the rotation section
    window.draw(titleRotation);

    // Draw Left button and label
    window.draw(ButtonRotateOne);
    window.draw(titleRotationLeft);

    // Draw Right button and label
    window.draw(ButtonRotateTwo);
    window.draw(titleRotationRight);

    // Draw Top button and label
    window.draw(ButtonRotateThree);
    window.draw(titleRotationTop);

    // Draw Bottom button and label
    window.draw(ButtonRotateFour);
    window.draw(titleRotationBottom);
}


// ------------------------------------------------------------------------------- Draw function 
void WorldEditor::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color(32, 32, 32));
    drawTileSizeGroup(window);
    drawTileGridGroup(window);
   // drawTileMiniViewport(window);
    drawSectionMap(window);
    drawBrushesTexture(window);
    drawRotationControls(window);
    drawTileLoadTilemap(window);

    drawDebugConsole(window);
}
// ------------------------------------------------------------------------------- Update functions

void WorldEditor::checkMousePOsitionAndClickOnVisibilityAndRotation(const sf::Vector2i &mousePosition, sf::Event event)
{
    if(ButtonRotateTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            toggleMode();
        }
    }
}

void WorldEditor::onLoadButtonClick() {
    if (!newGameMap) {
        std::cerr << "Error: No GameMap exists to load into." << std::endl;
        return;
    }

    // Load the main game map data
    if (!newGameMap->loadFromFile("res/data", "gameMap")) {
        std::cerr << "Failed to load game map data" << std::endl;
        return;
    }

    // Update UI based on loaded map size
    tileSizeType = newGameMap->mapSize;
    gridSizeType = newGameMap->cellSize / 8; // Convert cell size back to type (8->1, 16->2, 32->3)
    std::cout << "Loaded map size: " << tileSizeType << ", cell size: " << newGameMap->cellSize << std::endl;

    // Update cell size
    setCellSize(newGameMap->cellSize);

    // Clear existing sections before loading
    newGameMap->clearSections();

    // Create correct number of sections based on map size
    int numSections;
    switch(tileSizeType) {
        case 1: numSections = 2; break;
        case 2: numSections = 4; break;
        case 3: numSections = 6; break;
        default: 
            std::cerr << "Invalid map size loaded: " << tileSizeType << std::endl;
            return;
    }

    // Create and load sections
    newGameMap->createSections(numSections);
    
    for (int i = 0; i < numSections; i++) {
        std::string sectionFileName = "mapSection_" + std::to_string(i);
        
        if (!newGameMap->sections[i]) {
            std::cerr << "Section " << i << " is null after creation" << std::endl;
            continue;
        }

        try {
            if (newGameMap->sections[i]->loadFromFile("res/data", sectionFileName)) {
                std::cout << "Successfully loaded section " << i << std::endl;
                
                // Recreate the grid for this section
                int gridSize = 512 / tileSize;
                deallocateTileCellArray(newGameMap->sections[i]);
                allocateTileCellArray(newGameMap->sections[i], gridSize);
                
                // Load data into the grid
                // This assumes your MapSection save format includes the tile data
                // Adjust according to your actual save format
                for (int y = 0; y < newGameMap->sections[i]->numberOfCellsPerRow; y++) {
                    for (int x = 0; x < newGameMap->sections[i]->numberOfCellsPerRow; x++) {
                        TileCell& cell = newGameMap->sections[i]->tilecellArray[y][x];
                        
                        // If textureID is 0 from the file, increment it by 1
                        if (cell.textureID == 0) {
                            cell.textureID = 1;
                        }
                        
                        // Apply texture if there is one
                        if (cell.textureID > 0 && cell.textureID <= NUM_TEXTURES) {
                            cell.sprite.setTexture(tileTextures[cell.textureID - 1]);
                            cell.sprite.setPosition(cell.shape.getPosition());
                            
                            // Calculate scale based on tile size
                            sf::Vector2u textureSize = tileTextures[cell.textureID - 1].getSize();
                            float scaleX = static_cast<float>(tileSize) / textureSize.x;
                            float scaleY = static_cast<float>(tileSize) / textureSize.y;
                            cell.sprite.setScale(scaleX, scaleY);
                        }
                    }
                }
            } else {
                std::cerr << "Failed to load section " << i << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error loading section " << i << ": " << e.what() << std::endl;
        }
    }

    // Load texture paths
    for (int i = 0; i < NUM_TEXTURES; i++) {
        if (newGameMap->texturesPath[i] != "none") {
            if (!tileTextures[i].loadFromFile(newGameMap->texturesPath[i])) {
                std::cerr << "Failed to load texture from path: " << newGameMap->texturesPath[i].toAnsiString() << std::endl;
            }
        }
    }

    // Update UI state
    sectionSelected = 1;  // Reset to first section
    changeColorButtonsTileSize();  // Update tile size button colors
    changeColorButtonsGridSize();  // Update grid size button colors
    changeColorButtonsSection();   // Update section button colors

    // Recreate viewport if needed
    tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
}

void WorldEditor::checkMousePositionAndClicksLoadSave(const sf::Vector2i &mousePosition, sf::Event event) {
    // Check if mouse is hovering over the Load button
    if (buttonLoad.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!loadButtonClicked) {
                std::cout << "Load Button Clicked!" << std::endl;

           //     onLoadButtonClick();
                loadButtonClicked = true; // Set the flag so it doesn't log multiple times
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            loadButtonClicked = false; // Reset the flag when button is released
        }
    }

    // Check if mouse is hovering over the Save button
    if (buttonSave.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!saveButtonClicked) {
                std::cout << "Save Button Clicked!" << std::endl;
                onSaveButtonClick();
                saveButtonClicked = true; // Set the flag so it doesn't log multiple times
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            saveButtonClicked = false; // Reset the flag when button is released
        }
    }
}

// Function to create a new window and tilemap based on the size type
void WorldEditor::createTilemap(int tileSizeType)
{
    cout << "Tile Size: " << getCellSize() << endl;
    
    // Define the size of the tilemap based on the tileSizeType
    tilemap = Tilemap(tileSizeType, 16);
    
    // Properly allocate GameMap with correct number of sections
    int numSections;
    switch(tileSizeType) {
    case 1: numSections = 2; break;
    case 2: numSections = 4; break;
    case 3: numSections = 6; break;
    default: numSections = 2; break;
    }
    
    tilemap.allocateGameMap(8, 512, 512, tileSizeType);
    newGameMap = tilemap.getGameMap();
    if(newGameMap) {
        newGameMap->createSections(numSections);
        newMapSection = newGameMap->sections;
        
        // Initialize each section's grid
        for(int i = 0; i < numSections; i++) {
            if(newGameMap->sections[i]) {
                int gridSize = 512 / tileSize;
                allocateTileCellArray(newGameMap->sections[i], gridSize);
            }
        }
    }
    
   // tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
    previousCellSize = getCellSize();
    cout << "Tile Size 2: " << previousCellSize << endl;
}
// ------------------------------------------------- Tile Size 
void WorldEditor::checkMousePositionAndClicksTileSize(const sf::Vector2i &mousePosition, sf::Event event)
{
    // Check if mouse is hovering over ButtonOne
    if (buttonOneFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button One Clicked!" << std::endl;
            tileSizeType = 1;
            
            if(newGameMap) {
                newGameMap->mapSize = tileSizeType;
                newGameMap->clearSections(); // Clear existing sections
                newGameMap->setMapSize(tileSizeType);
                newGameMap->createSections(2); // Create 2 sections for size 1
                std::cout << "Recreated tilemap with 2 sections" << std::endl;
            } else if(!hasCreatedTilemap) {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
            
            // Always create/recreate the viewport window
            tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
        }
    } 

    // Check ButtonTwo
    if (buttonTwoFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Two Clicked!" << std::endl;
            tileSizeType = 2;
            
            if(newGameMap) {
                newGameMap->clearSections();
                newGameMap->setMapSize(tileSizeType);
                newGameMap->createSections(4); // Create 4 sections for size 2
                std::cout << "Recreated tilemap with 4 sections" << std::endl;
            } else if(!hasCreatedTilemap) {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
            
            // Always create/recreate the viewport window
            tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
        }
    } 

    // Check ButtonThree
    if (buttonThreeFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Three Clicked!" << std::endl;
            tileSizeType = 3;
            
            if(newGameMap) {
                newGameMap->clearSections();
                newGameMap->setMapSize(tileSizeType);
                newGameMap->createSections(6); // Create 6 sections for size 3
                std::cout << "Recreated tilemap with 6 sections" << std::endl;
            } else if(!hasCreatedTilemap) {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
            
            // Always create/recreate the viewport window
            tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
        }
    } 
}

void WorldEditor::changeColorButtonsTileSize()
{
    switch (tileSizeType)
    {
    case 1:
        buttonOneFileSize.setFillColor(sf::Color(128 , 128, 128));
        buttonTwoFileSize.setFillColor(sf::Color(56, 56, 56));
        buttonThreeFileSize.setFillColor(sf::Color(56, 56, 56));
        break;
    case 2:
        buttonOneFileSize.setFillColor(sf::Color(56, 56, 56));
        buttonTwoFileSize.setFillColor(sf::Color(128 , 128, 128));
        buttonThreeFileSize.setFillColor(sf::Color(56, 56, 56));
        break;
    case 3:
        buttonOneFileSize.setFillColor(sf::Color(56, 56, 56));      
        buttonTwoFileSize.setFillColor(sf::Color(56, 56, 56));      
        buttonThreeFileSize.setFillColor(sf::Color(128 , 128, 128));
        break;
    default:
        buttonOneFileSize.setFillColor(sf::Color(56, 56, 56));
        buttonTwoFileSize.setFillColor(sf::Color(56, 56, 56));
        buttonThreeFileSize.setFillColor(sf::Color(56, 56, 56));

        std::cout << "Invalid tile size type!" << std::endl;
        break;
    }
}
// ------------------------------------------------- Grid Size 
void WorldEditor::checkMousePositionAndClicksGridSize(const sf::Vector2i &mousePosition,  sf::Event event)
{
    
    // Check if mouse is hovering over ButtonOne
    if (ButtonOneGrid.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        if( !canEditCellSize)
        {
            canEditCellSize = true;
            cout << "value of canEditCellSize 1: " << canEditCellSize << endl;
        }
        // If the mouse is over the button, now check if the button is pressed
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
       //     std::cout << "Button One Clicked!" << std::endl;
    
            gridSizeType = 1;
            newGameMap->mapSize = 1;
            if(canEditCellSize) {
                newGameMap->setCellSize(8);
                canEditCellSize = false;
                cout << "value of canEditCellSize: " << canEditCellSize << endl;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
        //    std::cout << "Button One Released!" << std::endl;
            // Handle your button click action here
        }
    } 

    // Check ButtonTwo
    if (ButtonTwoGrid.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        if(!canEditCellSize)
        {
            canEditCellSize = true;
            cout << "value of canEditCellSize 2: " << canEditCellSize << endl;
        }

        // Check if ButtonTwo is clicked
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
        //    std::cout << "Button Two Clicked!" << std::endl;
            gridSizeType = 2;
            newGameMap->mapSize = 2;
            if(canEditCellSize) {
                newGameMap->setCellSize(16);
                canEditCellSize = false;
                cout << "value of canEditCellSize: " << canEditCellSize << endl;
            }
        }

        // Check if ButtonTwo is released
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
         //   std::cout << "Button Two Released!" << std::endl;

        }
    } 

    // Check ButtonThree
    if (ButtonThreeGrid.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
       
        if(!canEditCellSize)
        {
            canEditCellSize = true;
            cout << "value of canEditCellSize 3: " << canEditCellSize << endl;
        }
          
        // Check if ButtonThree is clicked
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
          //  std::cout << "Button Three Clicked!" << std::endl;
            gridSizeType = 3;
            newGameMap->mapSize = 3;
            if(canEditCellSize) {
                newGameMap->setCellSize(32);
                canEditCellSize = false;
                cout << "value of canEditCellSize: " << canEditCellSize << endl;
            }
        }

        // Check if ButtonThree is released
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
           // std::cout << "Button Three Released!" << std::endl;
         
        }
    } 
}
void WorldEditor::changeColorButtonsGridSize()
{
    switch (gridSizeType)
    {
    case 1:
        ButtonOneGrid.setFillColor(sf::Color(128 , 128, 128));
        ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));
        ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));
        setCellSize(8);
        break;
    case 2:
        ButtonOneGrid.setFillColor(sf::Color(56, 56, 56));
        ButtonTwoGrid.setFillColor(sf::Color(128 , 128, 128));
        ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));
        setCellSize(16);
        break;
    case 3:
        ButtonOneGrid.setFillColor(sf::Color(56, 56, 56));      
        ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));      
        ButtonThreeGrid.setFillColor(sf::Color(128 , 128, 128));
        setCellSize(32);
        break;
    default:
        ButtonOneGrid.setFillColor(sf::Color(128 , 128, 128));
        ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));
        ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));
        setCellSize(8);
        std::cout << "Invalid tile size type!" << std::endl;
        break;
    }
}
void WorldEditor::changeColorButtonsSection()
{
    switch (sectionSelected)
    {
    case 1:
        ButtonSectionOne.setFillColor(sf::Color(128 , 128, 128));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 2:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(128 , 128, 128));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 3:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(128 , 128, 128));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 4:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(128 , 128, 128));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 5:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(128 , 128, 128));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 6:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(128 , 128, 128));
        break;
    default:
        ButtonSectionOne.setFillColor(sf::Color(128 , 128, 128));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        std::cout << "Invalid tile size type!" << std::endl;
        break;
    }
}



void WorldEditor::checkMousePositionAndClickOnTileTextures(const sf::Vector2i &mousePosition, sf::Event event) {
    // Array of all buttons for easy iteration
  //  CurrentlySelectedIndex = 0;
   
    for (int i = 0; i < NUM_TEXTURES; ++i) {
        if (buttons[i]->getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                // save the current index 
                CurrentlySelectedIndex = i + 1;

                std::cout << "CurrentlySelectedIndex: " << CurrentlySelectedIndex << std::endl;
      
                // Assign the texture to the corresponding sprite
                tileSprites[i] .setTexture(tileTextures[i]);
                tileSprites[i].setPosition(buttons[i]->getPosition());
                tileSprites[i].setScale(buttons[i]->getScale());

                // Adjust color or transparency for better visibility if needed
                tileSprites[i].setColor(sf::Color(255, 255, 255, 200)); 
            }
        }
    }
}

void WorldEditor::changeColorButtonsTextures()
{
    // Ensure CurrentlySelectedIndex is within bounds (1 to 18)
    
    if (CurrentlySelectedIndex < 1 || CurrentlySelectedIndex > 18) {
     //   cout << "Invalid CurrentlySelectedIndex: " << CurrentlySelectedIndex << std::endl;
        return;
    }
    int calc = CurrentlySelectedIndex - 1;
    // Loop through the buttons array
    for (int i = 0; i < 18; ++i) {
        if (i == calc) {
            // Set selected button color
            buttons[i]->setFillColor(sf::Color(128, 128, 128));
        } else {
            // Set default color for non-selected buttons
            buttons[i]->setFillColor(sf::Color(56, 56, 56));
        }
    }
}



void WorldEditor::saveCurrentSectionState()
{
    if (!newGameMap || !newGameMap->sections || sectionSelected <= 0) return;

    MapSection* currentSection = newGameMap->sections[sectionSelected - 1];
    if (!currentSection) return;

    std::string sectionFileName = "section_" + std::to_string(sectionSelected) + "_data";
    try {
        if (currentSection->saveToFile("res/data", sectionFileName)) {
            std::cout << "Section " << sectionSelected << " saved successfully." << std::endl;
        } else {
            std::cerr << "Failed to save section " << sectionSelected << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error saving section " << sectionSelected << ": " << e.what() << std::endl;
    }
}

void WorldEditor::checkMousePositionAndClickOnSection(const sf::Vector2i &mousePosition, sf::Event event)
{
    if(tileSizeType == 1)
    {
        // Check if mouse is hovering over ButtonSectionOne
        if (ButtonSectionOne.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionOne is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section One Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 1;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionOne is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section One Released!" << std::endl;
            }
        }

        // Check if mouse is hovering over ButtonSectionTwo
        if (ButtonSectionTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionTwo is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Two Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 2;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionTwo is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Two Released!" << std::endl;
            }
        }
    }

    if(tileSizeType == 2)
    {
        // Check if mouse is hovering over ButtonSectionOne
        if (ButtonSectionOne.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionOne is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section One Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 1;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionOne is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section One Released!" << std::endl;
            }
        }

        // Check if mouse is hovering over ButtonSectionTwo
        if (ButtonSectionTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionTwo is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Two Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 2;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionTwo is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Two Released!" << std::endl;
            }
        }
        
        // Check if mouse is hovering over ButtonSectionThree
        if (ButtonSectionThree.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionThree is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Three Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 3;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionThree is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Three Released!" << std::endl;
            }
        }

        // Repeat for additional buttons (ButtonSectionFour, ButtonSectionFive, ButtonSectionSix)
        if (ButtonSectionFour.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Four Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 4;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Four Released!" << std::endl;
            }
        }

    }
    
    if(tileSizeType == 3)
    {
        // Check if mouse is hovering over ButtonSectionOne
        if (ButtonSectionOne.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionOne is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section One Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 1;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionOne is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section One Released!" << std::endl;
            }
        }

        // Check if mouse is hovering over ButtonSectionTwo
        if (ButtonSectionTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionTwo is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Two Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 2;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionTwo is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Two Released!" << std::endl;
            }
        }
        
        // Check if mouse is hovering over ButtonSectionThree
        if (ButtonSectionThree.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            // Check if ButtonSectionThree is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Three Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 3;
                changeColorButtonsSection(); // Update colors based on selection
            }
            // Check if ButtonSectionThree is released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Three Released!" << std::endl;
            }
        }

        // Repeat for additional buttons (ButtonSectionFour, ButtonSectionFive, ButtonSectionSix)
        if (ButtonSectionFour.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Four Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 4;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Four Released!" << std::endl;
            }
        }

        if (ButtonSectionFive.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Five Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 5;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Five Released!" << std::endl;
            }
        }

        if (ButtonSectionSix.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Six Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 6;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Button Section Six Released!" << std::endl;
            }
        }
    }
    
}
//--------------------------------------------------------------------------------- Debug


void WorldEditor::checkMousePositionAndClickOnDebugConsole(sf::Vector2i mousePosition, sf::Event event) {
    if (isConsoleActive) {
        // Check if enough time has passed since the last input
        if (debounceClock.getElapsedTime().asSeconds() > debounceDelay) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    // Handle backspace (remove last character)
                    if (!consoleInput.empty()) {
                        consoleInput.pop_back();
                    }
                } else if (event.text.unicode == '\r') {
                    // Handle Enter key (submit the input)
                    if (CurrentlySelectedIndex > 0 && newGameMap != nullptr) {
                        newGameMap->texturesPath[CurrentlySelectedIndex - 1] = consoleInput; // Set path for the selected texture
                        std::cout << "Texture path set for button " << CurrentlySelectedIndex << ": " << consoleInput << std::endl;
                    }
                    consoleInput.clear(); // Clear the input after submitting
                } else if (event.text.unicode < 128) {
                    // Only add ASCII characters to the input
                    consoleInput += static_cast<char>(event.text.unicode);
                }

                // Update the displayed text in the debug console
                texDebugConsole.setString("Logs: " + consoleInput);

                // Reset the debounce timer
                debounceClock.restart();
            }
        }
    }
}



// ------------------------------------------------------------------------------- Update function 
void WorldEditor::Update(sf::RenderWindow &window, const sf::Event& event)
{
    mousePosition = sf::Mouse::getPosition(window);
    
    checkMousePositionAndClicksLoadSave(mousePosition, event);
    // Tile Size
    checkMousePositionAndClicksTileSize(mousePosition, event);
    changeColorButtonsTileSize();

    // Grid Size
    checkMousePositionAndClicksGridSize(mousePosition, event);
    changeColorButtonsGridSize();

    // Section
    checkMousePositionAndClickOnSection(mousePosition, event);


    // Tile Textures
    checkMousePositionAndClickOnTileTextures(mousePosition, event);
    changeColorButtonsTextures();
  //  checkMousePositionAndClickOnDebugConsole(mousePosition, event);
    checkMousePOsitionAndClickOnVisibilityAndRotation(mousePosition, event);
   // checkMousePositionAndFVClicksWithShift(mousePosition, event);
    // Encapsulated call to save and apply texture to tile
    saveAndApplyTextureToTile();
}

void WorldEditor::allocateTileCellArray(MapSection* section, int gridSize)
{
    if (!section) return;

    // Calculate number of cells based on grid size
    section->numberOfCellsPerRow = gridSize;
    
    // Allocate the 2D array of TileCells
    section->tilecellArray = new TileCell*[gridSize];
    for(int y = 0; y < gridSize; y++)
    {
        section->tilecellArray[y] = new TileCell[gridSize];
        
        for(int x = 0; x < gridSize; x++)
        {
            // Initialize each TileCell
            section->tilecellArray[y][x].shape.setSize(sf::Vector2f(tileSize, tileSize));
            section->tilecellArray[y][x].shape.setPosition(x * tileSize, y * tileSize);
            section->tilecellArray[y][x].shape.setFillColor(sf::Color::Transparent);
            section->tilecellArray[y][x].shape.setOutlineColor(sf::Color::Red);
            section->tilecellArray[y][x].shape.setOutlineThickness(0.5f);
            section->tilecellArray[y][x].cellType = 'V'; // Default to void
            section->tilecellArray[y][x].textureID = -1;
        }
    }
    
    std::cout << "TileCell array allocated for section with grid size: " << gridSize << std::endl;
}

void WorldEditor::deallocateTileSection(MapSection* section) 
{
    if (!section) return;

    // Clean up the tilecell array
    if (section->tilecellArray) 
    {
        for (int y = 0; y < section->numberOfCellsPerRow; y++) 
        {
            delete[] section->tilecellArray[y];
        }
        delete[] section->tilecellArray;
        section->tilecellArray = nullptr;
    }

    std::cout << "Section tiles deallocated successfully." << std::endl;
}

// In WorldEditor.cpp

void WorldEditor::saveBrushToTile(MapSection* section, int cellX, int cellY) {
    if (!section || cellX < 0 || cellY < 0 || cellX >= section->numberOfCellsPerRow || cellY >= section->numberOfCellsPerRow) return;
    
    // Save the CurrentlySelectedIndex to the tile's local storage
    section->tilecellArray[cellY][cellX].textureID = CurrentlySelectedIndex; // Save as 0-based index for file storage
    std::cout << "Brush index " << section->tilecellArray[cellY][cellX].textureID << " saved to tile at (" << cellX << ", " << cellY << ")" << std::endl;
}



void WorldEditor::applyTextureToTile(MapSection* section, int cellX, int cellY, int textureIndex) {
    if (!section || cellX < 0 || cellY < 0 || 
        cellX >= section->numberOfCellsPerRow || 
        cellY >= section->numberOfCellsPerRow ||
        textureIndex < 0 || textureIndex >= NUM_TEXTURES) {
        return;
        }

    TileCell& cell = section->tilecellArray[cellY][cellX];
    cell.sprite.setTexture(tileTextures[textureIndex]);
    cell.sprite.setPosition(cell.shape.getPosition());
    cell.shape.setFillColor(sf::Color::Transparent);
    cell.textureID = textureIndex; // Store as 0-based index

    // Calculate and apply proper scaling for the sprite
    sf::Vector2u textureSize = tileTextures[textureIndex].getSize();
    float scaleX = static_cast<float>(tileSize) / textureSize.x;
    float scaleY = static_cast<float>(tileSize) / textureSize.y;
    cell.sprite.setScale(scaleX, scaleY);
}



void WorldEditor::deallocateTileCellArray(MapSection* section)
{
    if (!section || !section->tilecellArray) return;

    for(int y = 0; y < section->numberOfCellsPerRow; y++)
    {
        delete[] section->tilecellArray[y];
    }
    delete[] section->tilecellArray;
    section->tilecellArray = nullptr;
    
    std::cout << "TileCell array deallocated for section" << std::endl;
}
/*
void WorldEditor::deallocateSpritesArray(int rows)
{
    if (spriteArrayTilemap)
    {
        // Free each row
        for (int y = 0; y < rows; y++)
        {
            delete[] spriteArrayTilemap[y];
            delete[] colliderArray[y];
        }

        // Free the outer array
        delete[] spriteArrayTilemap;
        delete[] colliderArray;
        
        spriteArrayTilemap = nullptr;
        colliderArray = nullptr;

        std::cout << "Previous sprites and colliders deallocated." << std::endl;
    }

    if (textureIDArray)
    {
        for (int y = 0; y < rows; y++)
        {
            delete[] textureIDArray[y];
        }
        delete[] textureIDArray;
        textureIDArray = nullptr;
        std::cout << "textureIDArray deallocated." << std::endl;
    }

    if (ArrayCharEncoder)
    {
        deallocateArrayCharEncoder(rows);
        ArrayCharEncoder = nullptr; // Set to nullptr after deallocation
    }
}*/void WorldEditor::saveAndApplyTextureToTile() {
    // Check for Shift + P press
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        
        // Get mouse position relative to the tilemap viewport window
        sf::Vector2i viewportMousePos = sf::Mouse::getPosition(tileViewPort);
        
        // Validate that mouse is within the viewport bounds
        if (viewportMousePos.x < 0 || viewportMousePos.y < 0 || 
            viewportMousePos.x >= 512 || viewportMousePos.y >= 512) {
            return; // Mouse is outside the viewport
        }

        // Calculate cell coordinates using viewport mouse position
        int cellX = viewportMousePos.x / tileSize;
        int cellY = viewportMousePos.y / tileSize;

        // Get the current section
        if (!newGameMap || sectionSelected <= 0 || sectionSelected > newGameMap->mapSections) {
            return;
        }

        MapSection* currentSection = newGameMap->sections[sectionSelected - 1];
        if (!currentSection) {
            return;
        }

        // Validate coordinates
        if (cellX >= 0 && cellY >= 0 && 
            cellX < currentSection->numberOfCellsPerRow && 
            cellY < currentSection->numberOfCellsPerRow) {
            
            // Save the brush to the tile
            saveBrushToTile(currentSection, cellX, cellY);
            
            // Apply the texture (subtract 1 from CurrentlySelectedIndex since it's 1-based)
            applyTextureToTile(currentSection, cellX, cellY, CurrentlySelectedIndex - 1);
            
            std::cout << "Texture " << CurrentlySelectedIndex << " applied at position (" 
                      << cellX << ", " << cellY << ")" << std::endl;
        }
    }
}

void WorldEditor::displayTileSection(sf::RenderWindow& window, MapSection* section)
{
    if (!section || !section->tilecellArray) return;

    for (int y = 0; y < section->numberOfCellsPerRow; y++) 
    {
        for (int x = 0; x < section->numberOfCellsPerRow; x++) 
        {
            TileCell& cell = section->tilecellArray[y][x];

            // In texture mode, only draw sprites without grid or labels
            if (isTextureMode) {
                if (cell.textureID >= 0 && cell.textureID < NUM_TEXTURES) {
                    // Convert 0-based index to 1-based for texture access
                    int adjustedTextureId = cell.textureID;
                    cell.sprite.setTexture(tileTextures[adjustedTextureId]);
                    window.draw(cell.sprite);
                }
            }
            // In editor mode, draw everything (grid, sprites, and labels)
            else {
                // Draw the grid cell
                window.draw(cell.shape);

                // Draw sprite if there's a texture
                if (cell.textureID >= 0 && cell.textureID < NUM_TEXTURES) {
                    // Convert 0-based index to 1-based for texture access
                    int adjustedTextureId = cell.textureID;
                    cell.sprite.setTexture(tileTextures[adjustedTextureId]);
                    window.draw(cell.sprite);
                }

                // Draw the cell type label
                sf::Text labelText;
                labelText.setFont(fontEditor);
                labelText.setString(std::string(1, cell.cellType));
                labelText.setCharacterSize(8);
                labelText.setFillColor(sf::Color::White);
                labelText.setPosition(cell.shape.getPosition().x + 2, cell.shape.getPosition().y + 2);
                window.draw(labelText);
            }
        }
    }
}

int WorldEditor::getCellSize() {
  //  std::cout << "Current tile size: " << tileSize << std::endl;
    return tileSize;
}

void WorldEditor::setCellSize(int size) {
    tileSize = size;
}
void WorldEditor::checkMousePositionAndClicksWithShift(const sf::Vector2i& mousePosition, sf::Event event) {
    if (!newGameMap || !newGameMap->sections) return;

    MapSection* currentSection = newGameMap->sections[sectionSelected - 1];
    if (!currentSection) return;

    // Get mouse position relative to the tilemap viewport window
    sf::Vector2i viewportMousePos = sf::Mouse::getPosition(tileViewPort);
    
    // Validate that mouse is within the viewport bounds
    if (viewportMousePos.x < 0 || viewportMousePos.y < 0 || 
        viewportMousePos.x >= 512 || viewportMousePos.y >= 512) {
        return; // Mouse is outside the viewport
        }

    int cellX = viewportMousePos.x / tileSize;
    int cellY = viewportMousePos.y / tileSize;

    static int lastCellX = -1;
    static int lastCellY = -1;

    if ((cellX != lastCellX || cellY != lastCellY) && 
        cellX >= 0 && cellY >= 0 && 
        cellX < currentSection->numberOfCellsPerRow && 
        cellY < currentSection->numberOfCellsPerRow) {
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                currentSection->tilecellArray[cellY][cellX].cellType = 'V';
                std::cout << "Set cell (" << cellX << ", " << cellY << ") to V" << std::endl;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                currentSection->tilecellArray[cellY][cellX].cellType = 'C';
                std::cout << "Set cell (" << cellX << ", " << cellY << ") to C" << std::endl;
            }
            lastCellX = cellX;
            lastCellY = cellY;
        }
        }

    if (event.type == sf::Event::MouseButtonReleased) {
        lastCellX = -1;
        lastCellY = -1;
    }
}

void WorldEditor::displayColliderEncoderArray(sf::RenderWindow& window, MapSection* section)
{
    if (!section || !section->tilecellArray) return;

    for (int y = 0; y < section->numberOfCellsPerRow; y++)
    {
        for (int x = 0; x < section->numberOfCellsPerRow; x++)
        {
            TileCell& cell = section->tilecellArray[y][x];
            
          //  cout << "Current state of cell at (" << x << ", " << y << "): Type = " << cell.cellType << cell.textureID << std::endl;

            if (cell.cellType == 'V' && cell.shape.getFillColor() != sf::Color(100, 100, 100, 100)) 
            {
                cell.shape.setFillColor(sf::Color(100, 100, 100, 100)); // Gray for 'V'
                std::cout << "Setting cell (" << x << ", " << y << ") to void with gray color\n";
            }
            else if (cell.cellType == 'C' && cell.shape.getFillColor() != sf::Color(0, 0, 255, 100)) 
            {
                cell.shape.setFillColor(sf::Color(0, 0, 255, 100)); // Blue for 'C'
                std::cout << "Setting cell (" << x << ", " << y << ") to collider with blue color\n";
            }

            // Draw the cell shape
            window.draw(cell.shape);

            // Draw label if cell is C or V
            if (cell.cellType == 'C' || cell.cellType == 'V')
            {
                sf::Text labelText;
                labelText.setFont(fontEditor);
                labelText.setString(std::string(1, cell.cellType));
                labelText.setCharacterSize(8);
                labelText.setFillColor(sf::Color::White);
                
                sf::Vector2f cellPos = cell.shape.getPosition();
                labelText.setPosition(cell.shape.getPosition().x + 2, cell.shape.getPosition().y + 2);
                window.draw(labelText);
            }
        }
    }
}

void WorldEditor::tilemapDraw(sf::RenderWindow& window)
{
    if(!newGameMap || !newGameMap->sections || sectionSelected <= 0) return;
    
    MapSection* currentSection = newGameMap->sections[sectionSelected - 1];
    if(!currentSection) return;

    // If cell size changed, reallocate the grid
    if (getCellSize() != previousCellSize)
    {
        int gridSize = 512 / getCellSize();
        deallocateTileCellArray(currentSection);
        allocateTileCellArray(currentSection, gridSize);
        previousCellSize = getCellSize();
    }

    //displayColliderEncoderArray(window, currentSection);
    displayTileSection(window, currentSection);
}

void WorldEditor::tilemapUpdate(sf::RenderWindow& window, const sf::Event& event)
{
    sf::Vector2i viewportMousePos = sf::Mouse::getPosition(tileViewPort);
    checkMousePositionAndClicksWithShift(viewportMousePos, event);
}


/*
void WorldEditor::checkMousePositionAndClicksWithShift(const sf::Vector2i& mousePosition, sf::Event event)
{
    // Ensure ArrayCharEncoder is allocated
    if (ArrayCharEncoder == nullptr)
        return;

    int cellX = mousePosition.x / tileSize;
    int cellY = mousePosition.y / tileSize;

    if (cellX < numberOfCellsPerRow && cellY < rowsOfSprites)
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
        {
            cout << "shift pressed" << endl;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
            {
                cout << "V Pressed" << endl;
                ArrayCharEncoder[cellY][cellX] = 'V';
                colliderArray[cellY][cellX].setFillColor(sf::Color(100, 100, 100, 100));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                cout << "C Pressed" << endl;
                ArrayCharEncoder[cellY][cellX] = 'C';
                colliderArray[cellY][cellX].setFillColor(sf::Color(255, 0, 0, 100));
            }
        }

    }
}*/

void WorldEditor::allocateArrayCharEncoder(TileCell& tileCell)
{
    // Initialize the TileCell with default values
    tileCell.cellType = 'V';
    tileCell.shape.setFillColor(sf::Color::Transparent);
    tileCell.shape.setOutlineColor(sf::Color::Red);
    tileCell.shape.setOutlineThickness(0.5f);
    tileCell.textureID = -1;
}


// enemigo collisiones player
// para la clase que viene, colision player con el mundo, collision  player con el enemigo,
// loose and win condition ( pierde es que se queeda sin vida) Gana es que collisiona con el enitty crown)

/* Diego:
   
   Página de Itchio con Fuente, How To Play, Descripción. (Videos e Imágenes cuando el arte esté integrado)
   Colision Player -> Mundo.
   Enemigos.
   Lose y Win Condition.
   Pick de posión de Vidas o Balas.
   Texturas Main Menu, Gameplay, Background y Objetos del mapa.
   Animacion de Player al moverse.
   Audio.*/
   
 // puerta es win dondition 
 
 // lloose condition, muera o que se le acabe la vida. 
 
 // git ignore 
 
 // add .idea
 
 //add git ignore 
 // git ignore de github.
 
 