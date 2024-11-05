#include "WorldEditor.h"

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Tilemap.h"

// ------------------------------------------------------------------------------- Class constructor
WorldEditor::WorldEditor(int screenHeight): tileMapWidth(0), tileSize(0), gameOverLine(0)
{
    tileMapHeight = screenHeight;
    setCellSize(8);
    previousCellSize = 0;
}
// ------------------------------------------------------------------------------- Init functions
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

void WorldEditor::initDebugConsole()
{
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
    titleRotation.setString("SPRITE ROTATION");
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
    titleRotationLeft.setString("-90");
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
    titleRotationRight.setString("90");
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
    titleRotationTop.setString("0");
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
    titleRotationBottom.setString("180");
    titleRotationBottom.setCharacterSize(8);
    titleRotationBottom.setFillColor(sf::Color::White);
    titleRotationBottom.setPosition(
        ButtonRotateFour.getPosition().x + buttonWidth / 2 - titleRotationBottom.getGlobalBounds().width / 2,
        ButtonRotateFour.getPosition().y + (buttonHeight / 4)
    );
}

void WorldEditor::onSaveButtonClick() {
    if (newGameMap) { // Check if gameMap exists
        newGameMap->saveToFile("res/data", "gameMap");
    } else {
        std::cout << "No GameMap to save." << std::endl;
    }
}


void WorldEditor::initVariablesToSave()
{
    tilemap.allocateGameMap(8, 512, 512, 1);
    newGameMap = tilemap.getGameMap();
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

void WorldEditor::checkMousePositionAndClicksLoadSave(const sf::Vector2i &mousePosition, sf::Event event) {
    // Check if mouse is hovering over the Load button
    if (buttonLoad.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!loadButtonClicked) {
                std::cout << "Load Button Clicked!" << std::endl;
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
    // Define the size of the tilemap based on the tileSizeType
    
    Tilemap(tileSizeType, 16);
    // Create a new window with hardcoded size for now (you can adjust this)
    tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
}
// ------------------------------------------------- Tile Size 
void WorldEditor::checkMousePositionAndClicksTileSize(const sf::Vector2i &mousePosition,  sf::Event event)
{
    
    // Check if mouse is hovering over ButtonOne
    if (buttonOneFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
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
                
                newGameMap->setMapSize(tileSizeType);
                newGameMap->setMapSections(2);
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
    if (buttonTwoFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {

        // Check if ButtonTwo is clicked
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Two Clicked!" << std::endl;
            tileSizeType = 2;
            if(!hasCreatedTilemap)
            {
                createTilemap(tileSizeType);
                newGameMap->setMapSize(tileSizeType);
                newGameMap->setMapSections(4);
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
    if (buttonThreeFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {

        // Check if ButtonThree is clicked
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Three Clicked!" << std::endl;
            tileSizeType = 3;
            if(!hasCreatedTilemap)
            {
                createTilemap(tileSizeType);
                newGameMap->setMapSize(tileSizeType);
                newGameMap->setMapSections(6);
                hasCreatedTilemap = true;
            }
        }

        // Check if ButtonThree is released
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button Three Released!" << std::endl;
         
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
    changeColorButtonsGridSize();
}

void WorldEditor::allocateSpritesArrayForMapSection(int screenWidth, int screenHeight, int cellSize)
{
        if (cellSize <= 0)
        {
            std::cerr << "Error: cellSize must be greater than zero!" << std::endl;
            return; // Exit the function if cellSize is invalid
        }

        if (hasAllocatedSpritesAndShapes) {
            deallocateSpritesArray(rowsOfSprites); // Call deallocation function to free memory
            hasAllocatedSpritesAndShapes = false;  // Reset allocation status
        } 
            // create an array for each line of pixels (pixel array) but take in consideration how many lines t
            numberOfCellsPerRow = screenWidth / tileSize;
            rowsOfSprites = screenHeight / tileSize;
        
        
            spriteArrayTilemap = new sf::Sprite*[rowsOfSprites];
            colliderArray = new sf::RectangleShape*[rowsOfSprites];
            allocateArrayCharEncoder(rowsOfSprites, numberOfCellsPerRow);
            textureIDArray = new int*[rowsOfSprites];
    
            // iterate the total number of screen height devided between the number of cell size
            for(int y = 0; y < rowsOfSprites; y++)
            {
                spriteArrayTilemap[y] = new sf::Sprite[numberOfCellsPerRow];
                colliderArray[y] = new sf::RectangleShape[numberOfCellsPerRow];
                textureIDArray[y] = new int[numberOfCellsPerRow];
                
                for(int x = 0; x < numberOfCellsPerRow; x++)
                {
                    spriteArrayTilemap[y][x].setPosition(x * tileSize, y * tileSize);
                    spriteArrayTilemap[y][x] = sf::Sprite();

                    colliderArray[y][x].setPosition(x * tileSize, y * tileSize);
                    colliderArray[y][x].setSize(sf::Vector2f(tileSize, tileSize));
                    colliderArray[y][x].setFillColor(sf::Color::Transparent);  // No fill
                    colliderArray[y][x].setOutlineColor(sf::Color::Red);       // Red outline
                    colliderArray[y][x].setOutlineThickness(0.5f);

                    textureIDArray[y][x] = -1;
                }
            }
            hasAllocatedSpritesAndShapes = true;
            std::cout << "Sprites and colliders allocated." << std::endl;
        
}

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
}

void WorldEditor::displaySpritesArray(sf::RenderWindow& window)
{
    std::cout << "Drawing sprites and colliders 0" << std::endl;
    // get the window
    // inside the window grab the array of pointer that points to an array of sprites and set position
    for (int y = 0; y < rowsOfSprites; y++)
    {
        for (int x = 0; x < numberOfCellsPerRow; x++)
        {
            window.draw(colliderArray[y][x]);
            if (ArrayCharEncoder[y][x] == 'C' || ArrayCharEncoder[y][x] == 'V')
            {
                sf::Text labelText;
                labelText.setFont(fontEditor);
                labelText.setString(std::string(1, ArrayCharEncoder[y][x]));
                labelText.setCharacterSize(8);
                labelText.setFillColor(sf::Color::White);
                labelText.setPosition(colliderArray[y][x].getPosition());
                window.draw(labelText);
            }
            window.draw(spriteArrayTilemap[y][x]);
            window.draw(colliderArray[y][x]);
            
        }
        std::cout << "Drawing sprites and colliders 1" << std::endl;
    }
}

int WorldEditor::getCellSize() {
  //  std::cout << "Current tile size: " << tileSize << std::endl;
    return tileSize;
}

void WorldEditor::setCellSize(int size) {
    tileSize = size;
}

void WorldEditor::displayColliderEncoderArray(sf::RenderWindow& window)
{
    for (int y = 0; y < rowsOfSprites; y++)
    {
        for (int x = 0; x < numberOfCellsPerRow; x++)
        {
            // Set default transparent color
            colliderArray[y][x].setFillColor(sf::Color::Transparent);

            // Update color based on ArrayCharEncoder
            if (ArrayCharEncoder[y][x] == 'V') 
            {
                colliderArray[y][x].setFillColor(sf::Color(100, 100, 100, 100)); // Gray for 'V'
            }
            else if (ArrayCharEncoder[y][x] == 'C') 
            {
                colliderArray[y][x].setFillColor(sf::Color(0, 0, 255, 100)); // Blue for 'C'
            }

            // Draw the collider and label if necessary
            window.draw(colliderArray[y][x]);

            if (ArrayCharEncoder[y][x] == 'C' || ArrayCharEncoder[y][x] == 'V')
            {
              //  std::cout << "Drawing label for " << ArrayCharEncoder[y][x] << " at (" << x << ", " << y << ")" << std::endl;

                sf::Text labelText;
                labelText.setFont(fontEditor);
                labelText.setString(std::string(1, ArrayCharEncoder[y][x]));
                labelText.setCharacterSize(8);
                labelText.setFillColor(sf::Color::White);
                
                sf::Vector2f colliderPos = colliderArray[y][x].getPosition();
                labelText.setPosition(colliderPos.x + 2, colliderPos.y + 2);
                
                window.draw(labelText);
            }
        }
    }
}

void WorldEditor::tilemapDraw(sf::RenderWindow& window)
{
    if (getCellSize() != previousCellSize)
    {
        // Deallocate previous arrays before reallocating
        deallocateSpritesArray(512 / previousCellSize);

        // Allocate new arrays with the updated cell size
        allocateSpritesArrayForMapSection(512, 512, getCellSize());

        // Update the previous cell size to the current one
        previousCellSize = getCellSize();
    }

    // Display the sprites with the new size
    displayColliderEncoderArray(window);
}
void WorldEditor::tilemapUpdate(sf::RenderWindow& window, const sf::Event& event)
{
    mousePosition = sf::Mouse::getPosition(window);
    checkMousePositionAndClicksWithShift(mousePosition, event);
}

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
}

void WorldEditor::allocateArrayCharEncoder(int rows, int cols)
{
    // Allocate only if not already allocated
    if (ArrayCharEncoder == nullptr)
    {
        ArrayCharEncoder = new char*[rows];
        for (int y = 0; y < rows; y++)
        {
            ArrayCharEncoder[y] = new char[cols];
            for (int x = 0; x < cols; x++)
            {
                ArrayCharEncoder[y][x] = 'V'; // Initialize as empty
            }
        }
    }
}

void WorldEditor::deallocateArrayCharEncoder(int rows)
{
    for (int y = 0; y < rows; y++)
    {
        delete[] ArrayCharEncoder[y];
    }
    delete[] ArrayCharEncoder;
    ArrayCharEncoder = nullptr;
}

// enemigo collisiones player
// Editor ( to be continue)
// para la clase que viene, colision player con el mundo, player enemigo,
// loose and win condition
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
 
 