#include "WorldEditor.h"
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <windows.h>
#include "Tilemap.h"

WorldEditor::WorldEditor(int screenHeight): tileMapWidth(0), tileSize(0), gameOverLine(0) {
    tileMapHeight = screenHeight;
    setCellSize(8);
    previousCellSize = 0;
}

void WorldEditor::toggleMode() {
    isTextureMode = !isTextureMode;
    if(isTextureMode) {
        ButtonRotateTwo.setFillColor(sf::Color(128, 128, 128));
    }
    if(!isTextureMode) {
        ButtonRotateTwo.setFillColor(sf::Color(56, 56, 56));
    }
}

void WorldEditor::initTileTextures() {
    for (int i = 0; i < NUM_TEXTURES; ++i) {
        if (!tileTextures[i].loadFromFile(texturesPath[i])) {
            std::cerr << "Failed to load texture: " << texturesPath[i].toAnsiString() << std::endl;
        } else {
            std::cout << "Successfully loaded texture: " << texturesPath[i].toAnsiString() << std::endl;
        }
    }
}

void WorldEditor::initLoadTilemap() {
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
    buttonLoad.setPosition(static_cast<float>(textWidth) + 32.0f, static_cast<float>(baseTilePositionY) + static_cast<float>(paddingLoadTile) * 0.5f);
    buttonLoad.setFillColor(sf::Color(86, 86, 86));

    buttonTextLoad.setFont(fontEditor);
    buttonTextLoad.setString("Load");
    buttonTextLoad.setCharacterSize(8);
    buttonTextLoad.setPosition(static_cast<float>(textWidth) + 32.0f + static_cast<float>(paddingLoadTile) * 2.0f, static_cast<float>(baseTilePositionY) + static_cast<float>(paddingLoadTile));
    buttonTextLoad.setFillColor(sf::Color::White);

    buttonSave.setSize(sf::Vector2f(64.0f, 16.0f));
    buttonSave.setPosition(buttonTextLoad.getPosition().x + 64.0f + static_cast<float>(paddingLoadTile), static_cast<float>(baseTilePositionY) + static_cast<float>(paddingLoadTile) * 0.5f);
    buttonSave.setFillColor(sf::Color(86, 86, 86));

    buttonTextSave.setFont(fontEditor);
    buttonTextSave.setString("Save");
    buttonTextSave.setCharacterSize(8);
    buttonTextSave.setPosition(buttonSave.getPosition().x + 8.0f, static_cast<float>(baseTilePositionY) + static_cast<float>(paddingLoadTile));
    buttonTextSave.setFillColor(sf::Color::White);

    sectionLoadTilemapHeight = baseLoadTilemap.getSize().y + paddingLoadTile * 2.0f;
}

void WorldEditor::initTileSizeGroup() {
    int buttonWidth = 64;
    int padding = 16;
    float buttonVerticalPositionY = (sectionLoadTilemapHeight) + padding;

    titleEditor.setFont(fontEditor);
    titleEditor.setString("TILEMAP SIZE");
    titleEditor.setCharacterSize(8);
    titleEditor.setPosition(16, buttonVerticalPositionY - padding);
    titleEditor.setFillColor(sf::Color::White);

    buttonOneFileSize.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    buttonOneFileSize.setPosition(16, buttonVerticalPositionY);
    buttonOneFileSize.setFillColor(sf::Color(56, 56, 56));

    buttonTextOneFileSize.setFont(fontEditor);
    buttonTextOneFileSize.setString("Size 1");
    buttonTextOneFileSize.setCharacterSize(8);
    buttonTextOneFileSize.setPosition(buttonOneFileSize.getPosition().x + 8, buttonOneFileSize.getPosition().y + padding / 2);
    buttonTextOneFileSize.setFillColor(sf::Color::White);

    buttonTwoFileSize.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    buttonTwoFileSize.setPosition(static_cast<float>(buttonOneFileSize.getPosition().x + buttonWidth + padding), static_cast<float>(buttonVerticalPositionY));
    buttonTwoFileSize.setFillColor(sf::Color(56, 56, 56));

    buttonTextTwoFileSize.setFont(fontEditor);
    buttonTextTwoFileSize.setString("Size 2");
    buttonTextTwoFileSize.setCharacterSize(8);
    buttonTextTwoFileSize.setPosition(buttonTwoFileSize.getPosition().x + 8, buttonTwoFileSize.getPosition().y + padding / 2);
    buttonTextTwoFileSize.setFillColor(sf::Color::White);

    buttonThreeFileSize.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    buttonThreeFileSize.setPosition(static_cast<float>(buttonTwoFileSize.getPosition().x) + static_cast<float>(buttonWidth) + static_cast<float>(padding),static_cast<float>(buttonVerticalPositionY));
    buttonThreeFileSize.setFillColor(sf::Color(56, 56, 56));

    buttonTextThreeFileSize.setFont(fontEditor);
    buttonTextThreeFileSize.setString("Size 3");
    buttonTextThreeFileSize.setCharacterSize(8);
    buttonTextThreeFileSize.setPosition(buttonThreeFileSize.getPosition().x + 8, buttonThreeFileSize.getPosition().y + padding / 2);
    buttonTextThreeFileSize.setFillColor(sf::Color::White);

    sectionTileSizeHeight = buttonOneFileSize.getSize().y + padding;
}

void WorldEditor::initGridSizeGroup() {
    int buttonWidth = 64, padding = 16;
    int buttonVerticalPositionY = sectionLoadTilemapHeight + sectionTileSizeHeight + padding * 2;

    titleGrid.setFont(fontEditor);
    titleGrid.setString("GRID SIZE");
    titleGrid.setCharacterSize(8);
    titleGrid.setPosition(16, buttonVerticalPositionY - padding);
    titleGrid.setFillColor(sf::Color::White);

    ButtonOneGrid.setSize(sf::Vector2f(buttonWidth, 24.0f));
    ButtonOneGrid.setPosition(16, buttonVerticalPositionY);
    ButtonOneGrid.setFillColor(sf::Color(56, 56, 56));

    ButtonTextOneGrid.setFont(fontEditor);
    ButtonTextOneGrid.setString("Cell 8");
    ButtonTextOneGrid.setCharacterSize(8);
    ButtonTextOneGrid.setPosition(ButtonOneGrid.getPosition().x + 8, ButtonOneGrid.getPosition().y + padding / 2);
    ButtonTextOneGrid.setFillColor(sf::Color::White);

    ButtonTwoGrid.setSize(sf::Vector2f(buttonWidth, 24.0f));
    ButtonTwoGrid.setPosition(ButtonOneGrid.getPosition().x + buttonWidth + padding, buttonVerticalPositionY);
    ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));

    ButtonTextTwoGrid.setFont(fontEditor);
    ButtonTextTwoGrid.setString("Cell 16");
    ButtonTextTwoGrid.setCharacterSize(8);
    ButtonTextTwoGrid.setPosition(ButtonTwoGrid.getPosition().x + 4, ButtonTwoGrid.getPosition().y + padding / 2);
    ButtonTextTwoGrid.setFillColor(sf::Color::White);

    ButtonThreeGrid.setSize(sf::Vector2f(buttonWidth, 24.0f));
    ButtonThreeGrid.setPosition(ButtonTwoGrid.getPosition().x + buttonWidth + padding, buttonVerticalPositionY);
    ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));

    ButtonTextThreeGrid.setFont(fontEditor);
    ButtonTextThreeGrid.setString("Cell 32");
    ButtonTextThreeGrid.setCharacterSize(8);
    ButtonTextThreeGrid.setPosition(ButtonThreeGrid.getPosition().x + 4, ButtonThreeGrid.getPosition().y + padding / 2);
    ButtonTextThreeGrid.setFillColor(sf::Color::White);
}

void WorldEditor::initTileMiniViewport() {
    int baseTileWidth = 256;
    int baseTilePositionY = sectionLoadTilemapHeight + sectionTileSizeHeight + 64;
    int topHeaderHeight = baseTileWidth / 4;

    miniViewportBaseTile.setSize(sf::Vector2f(baseTileWidth, topHeaderHeight));
    miniViewportBaseTile.setPosition(0.0f, baseTilePositionY);
    miniViewportBaseTile.setFillColor(sf::Color(56, 56, 56));

    gamePreview.setSize(sf::Vector2f(baseTileWidth, topHeaderHeight));
    gamePreview.setPosition(0.0f, baseTilePositionY);
    gamePreview.setFillColor(sf::Color(48, 48, 48));

    topHeader.setSize(sf::Vector2f(baseTileWidth, topHeaderHeight));
    topHeader.setPosition(0.0f, baseTilePositionY);
    topHeader.setFillColor(sf::Color(56, 56, 56));

    magicBelt.setSize(sf::Vector2f(baseTileWidth, topHeaderHeight));
    magicBelt.setPosition(0.0f, baseTilePositionY + baseTileWidth);
    magicBelt.setFillColor(sf::Color(56, 56, 56));
}

void WorldEditor::initDebugConsole() {
    int baseTileWidth = 256;
    float baseTilePositionY = sectionLoadTilemapHeight + sectionTileSizeHeight + 256.0f + 96.0f;
    int paddingLoadTile = 8;

    baseDebugConsole.setSize(sf::Vector2f(baseTileWidth, 64.0f));
    baseDebugConsole.setPosition(0.0f, baseTilePositionY);
    baseDebugConsole.setFillColor(sf::Color(8, 8, 8));

    texDebugConsole.setFont(fontEditor);
    texDebugConsole.setString("Logs:");
    texDebugConsole.setCharacterSize(8);
    texDebugConsole.setPosition(16.0f, baseTilePositionY + paddingLoadTile);
    texDebugConsole.setFillColor(sf::Color::Green);

    consoleInput = "";
    isConsoleActive = true;
}

void WorldEditor::initSectionMap() {
    float baseTilePositionY = static_cast<float>(sectionLoadTilemapHeight) + sectionTileSizeHeight + 64.0f;

    float baseX = 16;
    float buttonWidth = 30;
    float paddingBetweenButtons = 8;
    float baseY = baseTilePositionY + paddingBetweenButtons + titleSection.getGlobalBounds().height + paddingBetweenButtons;

    titleSection.setFont(fontEditor);
    titleSection.setString("SELECT MAP");
    titleSection.setCharacterSize(8);
    titleSection.setFillColor(sf::Color::White);
    titleSection.setPosition(16, baseTilePositionY + paddingBetweenButtons);

    ButtonSectionOne.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    ButtonSectionOne.setPosition(baseX, baseY + paddingBetweenButtons);
    ButtonSectionOne.setFillColor(sf::Color(100, 100, 100));

    ButtonSectionTwo.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    ButtonSectionTwo.setPosition(baseX + buttonWidth + paddingBetweenButtons, baseY + paddingBetweenButtons);
    ButtonSectionTwo.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionThree.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    ButtonSectionThree.setPosition(baseX + 2 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionThree.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionFour.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    ButtonSectionFour.setPosition(baseX + 3 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionFour.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionFive.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    ButtonSectionFive.setPosition(baseX + 4 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionFive.setFillColor(sf::Color(28, 28, 28));

    ButtonSectionSix.setSize(sf::Vector2f(static_cast<float>(buttonWidth), 24.0f));
    ButtonSectionSix.setPosition(baseX + 5 * (buttonWidth + paddingBetweenButtons), baseY + paddingBetweenButtons);
    ButtonSectionSix.setFillColor(sf::Color(28, 28, 28));
}

void WorldEditor::initBrushes() {
    int buttonWidth = 30;
    int buttonHeight = 24;
    float paddingBetweenButtons = 8;
    float baseX = 16;
    float baseY = 222;

    titleBrushed.setFont(fontEditor);
    titleBrushed.setString("TILE TEXTURES");
    titleBrushed.setCharacterSize(8);
    titleBrushed.setPosition(baseX, 210);
    titleBrushed.setFillColor(sf::Color::White);

    float firstRowY = baseY + paddingBetweenButtons;
    float secondRowY = firstRowY + buttonHeight + paddingBetweenButtons;
    float thirdRowY = secondRowY + buttonHeight + paddingBetweenButtons;

    ButtonTextureOne.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureOne.setPosition(baseX, firstRowY);
    ButtonTextureOne.setFillColor(sf::Color(100, 100, 100));

    ButtonTextureTwo.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureTwo.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 1, firstRowY);
    ButtonTextureTwo.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureThree.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureThree.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 2, firstRowY);
    ButtonTextureThree.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFour.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureFour.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 3, firstRowY);
    ButtonTextureFour.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFive.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureFive.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 4, firstRowY);
    ButtonTextureFive.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureSix.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureSix.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 5, firstRowY);
    ButtonTextureSix.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureSeven.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureSeven.setPosition(baseX, secondRowY);
    ButtonTextureSeven.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureEight.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureEight.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 1, secondRowY);
    ButtonTextureEight.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureNine.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureNine.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 2, secondRowY);
    ButtonTextureNine.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureTen.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureTen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 3, secondRowY);
    ButtonTextureTen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureEleven.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureEleven.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 4, secondRowY);
    ButtonTextureEleven.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureTwelve.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureTwelve.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 5, secondRowY);
    ButtonTextureTwelve.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureThirteen.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureThirteen.setPosition(baseX, thirdRowY);
    ButtonTextureThirteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFourteen.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureFourteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 1, thirdRowY);
    ButtonTextureFourteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureFifteen.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureFifteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 2, thirdRowY);
    ButtonTextureFifteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureSixteen.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureSixteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 3, thirdRowY);
    ButtonTextureSixteen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureSeventeen.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureSeventeen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 4, thirdRowY);
    ButtonTextureSeventeen.setFillColor(sf::Color(28, 28, 28));

    ButtonTextureEighteen.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonTextureEighteen.setPosition(baseX + (buttonWidth + paddingBetweenButtons) * 5, thirdRowY);
    ButtonTextureEighteen.setFillColor(sf::Color(28, 28, 28));

    for (int i = 0; i < NUM_TEXTURES; ++i) {
        tileSprites[i].setPosition(buttons[i]->getPosition());
        tileSprites[i].setScale(buttons[i]->getScale()/2.0f);
    }
}

void WorldEditor::initRotationControls() {
    int buttonWidth = 48;
    int buttonHeight = 24;
    int padding = 16;
    int baseX = 16;
    int baseY = 336;

    titleRotation.setFont(fontEditor);
    titleRotation.setString("SPRITE VISIBILITY & ROTATION");
    titleRotation.setCharacterSize(8);
    titleRotation.setFillColor(sf::Color::White);
    titleRotation.setPosition(static_cast<float>(baseX), static_cast<float>(baseY));

    float buttonStartY = baseY + titleRotation.getGlobalBounds().height + padding / 2;

    ButtonRotateOne.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonRotateOne.setPosition(static_cast<float>(baseX), buttonStartY);
    ButtonRotateOne.setFillColor(sf::Color(56, 56, 56));

    titleRotationLeft.setFont(fontEditor);
    titleRotationLeft.setString("See C");
    titleRotationLeft.setCharacterSize(8);
    titleRotationLeft.setFillColor(sf::Color::White);
    titleRotationLeft.setPosition(ButtonRotateOne.getPosition().x + buttonWidth / 2 - titleRotationLeft.getGlobalBounds().width / 2, ButtonRotateOne.getPosition().y + (buttonHeight / 4) );

    ButtonRotateTwo.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonRotateTwo.setPosition(baseX + buttonWidth + padding / static_cast<float>(2), buttonStartY);
    ButtonRotateTwo.setFillColor(sf::Color(56, 56, 56));

    titleRotationRight.setFont(fontEditor);
    titleRotationRight.setString("See T");
    titleRotationRight.setCharacterSize(8);
    titleRotationRight.setFillColor(sf::Color::White);
    titleRotationRight.setPosition(ButtonRotateTwo.getPosition().x + buttonWidth / 2 - titleRotationRight.getGlobalBounds().width / 2, ButtonRotateTwo.getPosition().y + (buttonHeight / 4));

    ButtonRotateThree.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonRotateThree.setPosition(baseX + 2 * (buttonWidth + padding / static_cast<float>(2)), buttonStartY);
    ButtonRotateThree.setFillColor(sf::Color(56, 56, 56));

    titleRotationTop.setFont(fontEditor);
    titleRotationTop.setString("- Y");
    titleRotationTop.setCharacterSize(8);
    titleRotationTop.setFillColor(sf::Color::White);
    titleRotationTop.setPosition(ButtonRotateThree.getPosition().x + buttonWidth / 2 - titleRotationTop.getGlobalBounds().width / 2, ButtonRotateThree.getPosition().y + (buttonHeight / 4));

    ButtonRotateFour.setSize(sf::Vector2f(static_cast<float>(buttonWidth), static_cast<float>(buttonHeight)));
    ButtonRotateFour.setPosition(baseX + 3 * (buttonWidth + padding / static_cast<float>(2)), buttonStartY);
    ButtonRotateFour.setFillColor(sf::Color(56, 56, 56));

    titleRotationBottom.setFont(fontEditor); 
    titleRotationBottom.setString("- X");
    titleRotationBottom.setCharacterSize(8);
    titleRotationBottom.setFillColor(sf::Color::White);
    titleRotationBottom.setPosition(ButtonRotateFour.getPosition().x + buttonWidth / 2 - titleRotationBottom.getGlobalBounds().width / 2, ButtonRotateFour.getPosition().y + (buttonHeight / 4));
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
        if (newGameMap->texturesPath[i] == "none") {
            newGameMap->texturesPath[i] = texturesPath[i]; 
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

void WorldEditor::initVariablesToSave() {
    tilemap.allocateGameMap(8, 512, 512, 1);
    newGameMap = tilemap.getGameMap();

    if (newGameMap) {
        newMapSection = newGameMap->sections;
        std::cout << "GameMap allocated with cell size: " << newGameMap->cellSize << ", screen dimensions: " << newGameMap->screenWidth << "x" << newGameMap->screenHeight << ", map size: " << newGameMap->mapSize << std::endl;

        if (newMapSection) {
            std::cout << "MapSection array allocated with " << newMapSection << " sections." << std::endl;
        } else {
            std::cerr << "Error: MapSection array not allocated." << std::endl;
        }
    }
}

void WorldEditor::init() {
    std::cerr << "Init!" << std::endl;
    if (!fontEditor.loadFromFile("res/fonts/PressStart2P-Regular.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
    } else {
        std::cout << "Font loaded successfully " << std::endl;
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
void WorldEditor::drawTileSizeGroup(sf::RenderWindow& window) const {
    window.draw(titleEditor);
    
    window.draw(buttonOneFileSize);
    window.draw(buttonTextOneFileSize);
    
    window.draw(buttonTwoFileSize);
    window.draw(buttonTextTwoFileSize);
    
    window.draw(buttonThreeFileSize);
    window.draw(buttonTextThreeFileSize);
}
void WorldEditor::drawTileGridGroup(sf::RenderWindow& window) const {

    window.draw(titleGrid);
    
    window.draw(gridTile);
    
    window.draw(ButtonOneGrid);
    window.draw(ButtonTextOneGrid);
    
    window.draw(ButtonTwoGrid);
    window.draw(ButtonTextTwoGrid);
    
    window.draw(ButtonThreeGrid);
    window.draw(ButtonTextThreeGrid);
}

void WorldEditor::drawTileMiniViewport(sf::RenderWindow& window) const {
    window.draw(miniViewportBaseTile);
    window.draw(gamePreview);
    window.draw(topHeader);
    window.draw(magicBelt);
}

void WorldEditor::drawTileLoadTilemap(sf::RenderWindow& window) const {
    window.draw(baseLoadTilemap);
    window.draw(textTilemap);
    window.draw(buttonLoad);
    window.draw(buttonTextLoad);
    window.draw(buttonSave);
    window.draw(buttonTextSave);

}

void WorldEditor::drawDebugConsole(sf::RenderWindow& window) const {
    window.draw(baseDebugConsole);
    window.draw(texDebugConsole);
}

void WorldEditor::drawSectionMap(sf::RenderWindow& window) const {
    if(tileSizeType == 1) {
        window.draw(titleSection);
        window.draw(ButtonSectionOne);
        window.draw(ButtonSectionTwo);
    }
    if(tileSizeType == 2) {
        window.draw(titleSection);
        window.draw(ButtonSectionOne);
        window.draw(ButtonSectionTwo);
        window.draw(ButtonSectionThree);
        window.draw(ButtonSectionFour);
    }
    if(tileSizeType == 3) {
        window.draw(titleSection);
        window.draw(ButtonSectionOne);
        window.draw(ButtonSectionTwo);
        window.draw(ButtonSectionThree);
        window.draw(ButtonSectionFour);
        window.draw(ButtonSectionFive);
        window.draw(ButtonSectionSix);
    }
}

void WorldEditor::drawBrushesTexture(sf::RenderWindow& window) const {
    window.draw(titleBrushed);
    window.draw(ButtonTextureOne);
    window.draw(ButtonTextureTwo);
    window.draw(ButtonTextureThree);
    window.draw(ButtonTextureFour);
    window.draw(ButtonTextureFive);
    window.draw(ButtonTextureSix);
    window.draw(ButtonTextureSeven);
    window.draw(ButtonTextureEight);
    window.draw(ButtonTextureNine);
    window.draw(ButtonTextureTen);
    window.draw(ButtonTextureEleven);
    window.draw(ButtonTextureTwelve);
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

void WorldEditor::drawRotationControls(sf::RenderWindow& window) const {
    window.draw(titleRotation);
    window.draw(ButtonRotateOne);
    window.draw(titleRotationLeft);
    window.draw(ButtonRotateTwo);
    window.draw(titleRotationRight);
    window.draw(ButtonRotateThree);
    window.draw(titleRotationTop);
    window.draw(ButtonRotateFour);
    window.draw(titleRotationBottom);
}

void WorldEditor::draw(sf::RenderWindow &window) {
    window.clear(sf::Color(32, 32, 32));
    drawTileSizeGroup(window);
    drawTileGridGroup(window);
    drawSectionMap(window);
    drawBrushesTexture(window);
    drawRotationControls(window);
    drawTileLoadTilemap(window);
    drawDebugConsole(window);
}

// ------------------------------------------------------------------------------- Update functions

void WorldEditor::checkMousePositionAndClickOnVisibilityAndRotation(const sf::Vector2i &mousePosition, sf::Event event) {
    if(ButtonRotateTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
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

    if (!newGameMap->loadFromFile("res/data", "gameMap")) {
        std::cerr << "Failed to load game map data" << std::endl;
        return;
    }

    tileSizeType = newGameMap->mapSize;
    gridSizeType = newGameMap->cellSize / 8;
    std::cout << "Loaded map size: " << tileSizeType << ", cell size: " << newGameMap->cellSize << std::endl;

    setCellSize(newGameMap->cellSize);
    newGameMap->clearSections();

    int numSections;
    switch(tileSizeType) {
        case 1: numSections = 2; break;
        case 2: numSections = 4; break;
        case 3: numSections = 6; break;
        default: 
            std::cerr << "Invalid map size loaded: " << tileSizeType << std::endl;
            return;
    }

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
                
                int gridSize = 512 / tileSize;
                deallocateTileCellArray(newGameMap->sections[i]);
                allocateTileCellArray(newGameMap->sections[i], gridSize);
                
                for (int y = 0; y < newGameMap->sections[i]->numberOfCellsPerRow; y++) {
                    for (int x = 0; x < newGameMap->sections[i]->numberOfCellsPerRow; x++) {
                        TileCell& cell = newGameMap->sections[i]->tilecellArray[y][x];
                        
                        if (cell.textureID == 0) {
                            cell.textureID = 1;
                        }
                        
                        if (cell.textureID > 0 && cell.textureID <= NUM_TEXTURES) {
                            cell.sprite.setTexture(tileTextures[cell.textureID - 1]);
                            cell.sprite.setPosition(cell.shape.getPosition());
                            
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

    for (int i = 0; i < NUM_TEXTURES; i++) {
        if (newGameMap->texturesPath[i] != "none") {
            if (!tileTextures[i].loadFromFile(newGameMap->texturesPath[i])) {
                std::cerr << "Failed to load texture from path: " << newGameMap->texturesPath[i].toAnsiString() << std::endl;
            }
        }
    }

    sectionSelected = 1;
    changeColorButtonsTileSize();
    changeColorButtonsGridSize();
    changeColorButtonsSection();

    tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
}

void WorldEditor::checkMousePositionAndClicksLoadSave(const sf::Vector2i &mousePosition, sf::Event event) {
    if (buttonLoad.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!loadButtonClicked) {
                std::cout << "Load Button Clicked!" << std::endl;
                loadButtonClicked = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            loadButtonClicked = false;
        }
    }

    if (buttonSave.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!saveButtonClicked) {
                std::cout << "Save Button Clicked!" << std::endl;
                onSaveButtonClick();
                saveButtonClicked = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            saveButtonClicked = false;
        }
    }
}

void WorldEditor::createTilemap(int tileSizeType) {
    cout << "Tile Size: " << getCellSize() << endl;
    tilemap = Tilemap(tileSizeType, 16);
    
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
        
        for(int i = 0; i < numSections; i++) {
            if(newGameMap->sections[i]) {
                int gridSize = 512 / tileSize;
                allocateTileCellArray(newGameMap->sections[i], gridSize);
            }
        }
    }
    
    tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
    previousCellSize = getCellSize();
    cout << "Tile Size 2: " << previousCellSize << endl;
}

// ------------------------------------------------- Tile Size

void WorldEditor::checkMousePositionAndClicksTileSize(const sf::Vector2i &mousePosition, sf::Event event)
{
    if (buttonOneFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "Button One Clicked!" << std::endl;
            tileSizeType = 1;
            
            if(newGameMap) {
                newGameMap->mapSize = tileSizeType;
                newGameMap->clearSections();
                newGameMap->setMapSize(tileSizeType);
                newGameMap->createSections(2);
                std::cout << "Recreated tilemap with 2 sections" << std::endl;
            } else if(!hasCreatedTilemap) {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
            tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
        }
    } 

    if (buttonTwoFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "Button Two Clicked!" << std::endl;
            tileSizeType = 2;
            
            if(newGameMap) {
                newGameMap->clearSections();
                newGameMap->setMapSize(tileSizeType);
                newGameMap->createSections(4);
                std::cout << "Recreated tilemap with 4 sections" << std::endl;
            } else if(!hasCreatedTilemap) {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
            tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
        }
    }

    if (buttonThreeFileSize.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "Button Three Clicked!" << std::endl;
            tileSizeType = 3;
            
            if(newGameMap) {
                newGameMap->clearSections();
                newGameMap->setMapSize(tileSizeType);
                newGameMap->createSections(6);
                std::cout << "Recreated tilemap with 6 sections" << std::endl;
            } else if(!hasCreatedTilemap) {
                createTilemap(tileSizeType);
                hasCreatedTilemap = true;
            }
            tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
        }
    }
}

void WorldEditor::changeColorButtonsTileSize() {
    switch (tileSizeType) {
    case 1:
        buttonOneFileSize.setFillColor(sf::Color(128, 128, 128));
        buttonTwoFileSize.setFillColor(sf::Color(56, 56, 56));
        buttonThreeFileSize.setFillColor(sf::Color(56, 56, 56));
        break;
    case 2:
        buttonOneFileSize.setFillColor(sf::Color(56, 56, 56));
        buttonTwoFileSize.setFillColor(sf::Color(128, 128, 128));
        buttonThreeFileSize.setFillColor(sf::Color(56, 56, 56));
        break;
    case 3:
        buttonOneFileSize.setFillColor(sf::Color(56, 56, 56));      
        buttonTwoFileSize.setFillColor(sf::Color(56, 56, 56));      
        buttonThreeFileSize.setFillColor(sf::Color(128, 128, 128));
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

void WorldEditor::checkMousePositionAndClicksGridSize(const sf::Vector2i &mousePosition, sf::Event event) {
    if (ButtonOneGrid.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if(!canEditCellSize) {
            canEditCellSize = true;
            cout << "value of canEditCellSize 1: " << canEditCellSize << endl;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            gridSizeType = 1;
            newGameMap->mapSize = 1;
            if(canEditCellSize) {
                newGameMap->setCellSize(8);
                canEditCellSize = false;
                cout << "value of canEditCellSize: " << canEditCellSize << endl;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        }
    }
    
    if (ButtonTwoGrid.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if(!canEditCellSize) {
            canEditCellSize = true;
            cout << "value of canEditCellSize 2: " << canEditCellSize << endl;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            gridSizeType = 2;
            newGameMap->mapSize = 2;
            if(canEditCellSize) {
                newGameMap->setCellSize(16);
                canEditCellSize = false;
                cout << "value of canEditCellSize: " << canEditCellSize << endl;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        }
    }

    if (ButtonThreeGrid.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if(!canEditCellSize) {
            canEditCellSize = true;
            cout << "value of canEditCellSize 3: " << canEditCellSize << endl;
        }
          
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            gridSizeType = 3;
            newGameMap->mapSize = 3;
            if(canEditCellSize) {
                newGameMap->setCellSize(32);
                canEditCellSize = false;
                cout << "value of canEditCellSize: " << canEditCellSize << endl;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        }
    }
}

void WorldEditor::changeColorButtonsGridSize() {
    switch (gridSizeType) {
    case 1:
        ButtonOneGrid.setFillColor(sf::Color(128, 128, 128));
        ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));
        ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));
        setCellSize(8);
        break;
    case 2:
        ButtonOneGrid.setFillColor(sf::Color(56, 56, 56));
        ButtonTwoGrid.setFillColor(sf::Color(128, 128, 128));
        ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));
        setCellSize(16);
        break;
    case 3:
        ButtonOneGrid.setFillColor(sf::Color(56, 56, 56));      
        ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));      
        ButtonThreeGrid.setFillColor(sf::Color(128, 128, 128));
        setCellSize(32);
        break;
    default:
        ButtonOneGrid.setFillColor(sf::Color(128, 128, 128));
        ButtonTwoGrid.setFillColor(sf::Color(56, 56, 56));
        ButtonThreeGrid.setFillColor(sf::Color(56, 56, 56));
        setCellSize(8);
        std::cout << "Invalid tile size type!" << std::endl;
        break;
    }
}

void WorldEditor::setBackgroundPosition(sf::Sprite& sprite, int sectionSelected) {
    switch (sectionSelected) {
    case 1:
        sprite.setPosition(0.0f, 0.0f);
        break;
    case 2:
        sprite.setPosition(-512.0f, 0.0f);
        break;
    case 3:
        sprite.setPosition(-1024.0f, 0.0f);
        break;
    case 4:
        sprite.setPosition(-1536.0f, 0.0f);
        break;
    case 5:
        sprite.setPosition(-2048.0f, 0.0f);
        break;
    case 6:
        sprite.setPosition(-2560.0f, 0.0f);
        break;
    default:
        std::cout << "Invalid section selected: " << sectionSelected << std::endl;
        break;
    }
}

void WorldEditor::changeColorButtonsSection() {
    switch (sectionSelected) {
    case 1:
        ButtonSectionOne.setFillColor(sf::Color(128, 128, 128));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 2:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(128, 128, 128));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 3:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(128, 128, 128));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 4:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(128, 128, 128));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 5:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(128, 128, 128));
        ButtonSectionSix.setFillColor(sf::Color(56, 56, 56));
        break;
    case 6:
        ButtonSectionOne.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionTwo.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionThree.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFour.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionFive.setFillColor(sf::Color(56, 56, 56));
        ButtonSectionSix.setFillColor(sf::Color(128, 128, 128));
        break;
    default:
        ButtonSectionOne.setFillColor(sf::Color(128, 128, 128));
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
    for (int i = 0; i < NUM_TEXTURES; ++i) {
        if (buttons[i]->getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                CurrentlySelectedIndex = i + 1;
                std::cout << "CurrentlySelectedIndex: " << CurrentlySelectedIndex << std::endl;
                tileSprites[i].setTexture(tileTextures[i]);
                tileSprites[i].setPosition(buttons[i]->getPosition());
                tileSprites[i].setScale(buttons[i]->getScale());
                tileSprites[i].setColor(sf::Color(255, 255, 255, 200)); 
            }
        }
    }
}

void WorldEditor::changeColorButtonsTextures() {
    if (CurrentlySelectedIndex < 1 || CurrentlySelectedIndex > 18) {
        return;
    }
    int calc = CurrentlySelectedIndex - 1;
    for (int i = 0; i < 18; ++i) {
        if (i == calc) {
            buttons[i]->setFillColor(sf::Color(128, 128, 128));
        } else {
            buttons[i]->setFillColor(sf::Color(56, 56, 56));
        }
    }
}

void WorldEditor::saveCurrentSectionState() {
    if (!newGameMap || !newGameMap->sections || sectionSelected <= 0) {
        return;
    }

    currentSection = newGameMap->sections[sectionSelected - 1];
    if (!currentSection) {
        return;
    }

    std::string sectionFileName = "section_" + std::to_string(sectionSelected) + "_data";
    try {
        if (currentSection->saveToFile("res/data", sectionFileName)) {
            std::cout << "Section " << sectionSelected << " saved successfully." << std::endl;
        } else {
            std::cerr << "Failed to save section " << sectionSelected << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error saving section " << sectionSelected << ": " << e.what() << std::endl;
    }
}

void WorldEditor::checkMousePositionAndClickOnSection(const sf::Vector2i &mousePosition, sf::Event event) {
    if (tileSizeType == 1) {
        if (ButtonSectionOne.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section One Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 1;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section One Released!" << std::endl;
            }
        }

        if (ButtonSectionTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Two Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 2;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Two Released!" << std::endl;
            }
        }
    }

    if (tileSizeType == 2) {
        if (ButtonSectionOne.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section One Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 1;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section One Released!" << std::endl;
            }
        }

        if (ButtonSectionTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Two Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 2;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Two Released!" << std::endl;
            }
        }

        if (ButtonSectionThree.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Three Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 3;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Three Released!" << std::endl;
            }
        }

        if (ButtonSectionFour.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Four Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 4;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Four Released!" << std::endl;
            }
        }
    }

    if (tileSizeType == 3) {
        if (ButtonSectionOne.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section One Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 1;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section One Released!" << std::endl;
            }
        }

        if (ButtonSectionTwo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Two Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 2;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Two Released!" << std::endl;
            }
        }

        if (ButtonSectionThree.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Three Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 3;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Three Released!" << std::endl;
            }
        }

        if (ButtonSectionFour.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Four Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 4;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Four Released!" << std::endl;
            }
        }

        if (ButtonSectionFive.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Five Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 5;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Five Released!" << std::endl;
            }
        }

        if (ButtonSectionSix.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Six Clicked!" << std::endl;
                saveCurrentSectionState();
                sectionSelected = 6;
                changeColorButtonsSection();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Button Section Six Released!" << std::endl;
            }
        }
    }
}

//--------------------------------------------------------------------------------- Debug

void WorldEditor::checkMousePositionAndClickOnDebugConsole(sf::Vector2i mousePosition, sf::Event event) {
    if (isConsoleActive) {
        if (debounceClock.getElapsedTime().asSeconds() > debounceDelay) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!consoleInput.empty()) {
                        consoleInput.pop_back();
                    }
                } else if (event.text.unicode == '\r') {
                    if (CurrentlySelectedIndex > 0 && newGameMap != nullptr) {
                        newGameMap->texturesPath[CurrentlySelectedIndex - 1] = consoleInput; 
                        std::cout << "Texture path set for button " << CurrentlySelectedIndex << ": " << consoleInput << std::endl;
                    }
                    consoleInput.clear(); 
                } else if (event.text.unicode < 128) {
                    consoleInput += static_cast<char>(event.text.unicode);
                }

                texDebugConsole.setString("Logs: " + consoleInput);
                debounceClock.restart();
            }
        }
    }
}

// ------------------------------------------------------------------------------- Update function

void WorldEditor::Update(sf::RenderWindow &window, const sf::Event& event) {
    mousePosition = sf::Mouse::getPosition(window);
    
    checkMousePositionAndClicksLoadSave(mousePosition, event);
    checkMousePositionAndClicksTileSize(mousePosition, event);
    changeColorButtonsTileSize();
    checkMousePositionAndClicksGridSize(mousePosition, event);
    changeColorButtonsGridSize();
    checkMousePositionAndClickOnSection(mousePosition, event);
    checkMousePositionAndClickOnTileTextures(mousePosition, event);
    changeColorButtonsTextures();
    checkMousePositionAndClickOnVisibilityAndRotation(mousePosition, event);
    saveAndApplyTextureToTile();
}

void WorldEditor::allocateTileCellArray(MapSection* section, int gridSize) {
    if (!section)
        return;

    section->numberOfCellsPerRow = gridSize;
    
    section->tilecellArray = new TileCell*[gridSize];
    for(int y = 0; y < gridSize; y++) {
        section->tilecellArray[y] = new TileCell[gridSize];
        
        for(int x = 0; x < gridSize; x++) {
            section->tilecellArray[y][x].shape.setSize(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
            section->tilecellArray[y][x].shape.setPosition(static_cast<float>(x) * static_cast<float>(tileSize), static_cast<float>(y) * static_cast<float>(tileSize));
            section->tilecellArray[y][x].shape.setFillColor(sf::Color::Transparent);
            section->tilecellArray[y][x].shape.setOutlineColor(sf::Color::Red);
            section->tilecellArray[y][x].shape.setOutlineThickness(0.5f);
            section->tilecellArray[y][x].cellType = 'V'; // Default to void
            section->tilecellArray[y][x].textureID = -1;
        }
    }
    std::cout << "TileCell array allocated for section with grid size: " << gridSize << std::endl;
}

void WorldEditor::deallocateTileSection(MapSection* section) {
    if (!section)
        return;
    
    if (section->tilecellArray) {
        for (int y = 0; y < section->numberOfCellsPerRow; y++) {
            delete[] section->tilecellArray[y];
        }
        delete[] section->tilecellArray;
        section->tilecellArray = nullptr;
    }

    std::cout << "Section tiles deallocated successfully." << std::endl;
}

void WorldEditor::saveBrushToTile(MapSection* section, int cellX, int cellY) {
    if (!section || cellX < 0 || cellY < 0 || cellX >= section->numberOfCellsPerRow || cellY >= section->numberOfCellsPerRow)
        return;
    
    section->tilecellArray[cellY][cellX].textureID = CurrentlySelectedIndex;
    std::cout << "Brush index " << section->tilecellArray[cellY][cellX].textureID << " saved to tile at (" << cellX << ", " << cellY << ")" << std::endl;
}

void WorldEditor::applyTextureToTile(MapSection* section, int cellX, int cellY, int textureIndex) {
    if (!section || cellX < 0 || cellY < 0 || cellX >= section->numberOfCellsPerRow || cellY >= section->numberOfCellsPerRow || textureIndex < 0 || textureIndex >= NUM_TEXTURES) 
        return;
    

    TileCell& cell = section->tilecellArray[cellY][cellX];
    cell.sprite.setTexture(tileTextures[textureIndex]);
    cell.sprite.setPosition(cell.shape.getPosition());
    cell.shape.setFillColor(sf::Color::Transparent);
    cell.textureID = textureIndex;

    sf::Vector2u textureSize = tileTextures[textureIndex].getSize();
    float scaleX = static_cast<float>(tileSize) / textureSize.x;
    float scaleY = static_cast<float>(tileSize) / textureSize.y;
    cell.sprite.setScale(scaleX, scaleY);
}

void WorldEditor::deallocateTileCellArray(MapSection* section) {
    if (!section || !section->tilecellArray)
        return;

    for(int y = 0; y < section->numberOfCellsPerRow; y++) 
        delete[] section->tilecellArray[y];
    
    delete[] section->tilecellArray;
    section->tilecellArray = nullptr;
    
    std::cout << "TileCell array deallocated for section" << std::endl;
}

void WorldEditor::saveAndApplyTextureToTile() {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        
        sf::Vector2i viewportMousePos = sf::Mouse::getPosition(tileViewPort);
        
        if (viewportMousePos.x < 0 || viewportMousePos.y < 0 || viewportMousePos.x >= 512 || viewportMousePos.y >= 512) 
            return; 
        
        int cellX = viewportMousePos.x / tileSize;
        int cellY = viewportMousePos.y / tileSize;

        if (!newGameMap || sectionSelected <= 0 || sectionSelected > newGameMap->mapSections) 
            return;
        

        MapSection* currentSection = newGameMap->sections[sectionSelected - 1];
        
        if (!currentSection) 
            return;
        

        if (cellX >= 0 && cellY >= 0 && cellX < currentSection->numberOfCellsPerRow && cellY < currentSection->numberOfCellsPerRow) {
            saveBrushToTile(currentSection, cellX, cellY);
            applyTextureToTile(currentSection, cellX, cellY, CurrentlySelectedIndex - 1);
            std::cout << "Texture " << CurrentlySelectedIndex << " applied at position (" << cellX << ", " << cellY << ")" << std::endl;
        }
    }
}

void WorldEditor::displayTileSection(sf::RenderWindow& window, MapSection* section)
{
    if (!section || !section->tilecellArray)
        return;

    for (int y = 0; y < section->numberOfCellsPerRow; y++) {
        for (int x = 0; x < section->numberOfCellsPerRow; x++) {
            TileCell& cell = section->tilecellArray[y][x];

            if (isTextureMode) {
                if (cell.textureID >= 0 && cell.textureID < NUM_TEXTURES) {
                    int adjustedTextureId = cell.textureID;
                    cell.sprite.setTexture(tileTextures[adjustedTextureId]);
                    window.draw(cell.sprite);
                }
            } else {
                window.draw(cell.shape);

                if (cell.textureID >= 0 && cell.textureID < NUM_TEXTURES) {
                    int adjustedTextureId = cell.textureID;
                    cell.sprite.setTexture(tileTextures[adjustedTextureId]);
                    window.draw(cell.sprite);
                }

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
    return tileSize;
}

void WorldEditor::setCellSize(int size) {
    tileSize = size;
}
void WorldEditor::checkMousePositionAndClicksWithShift(const sf::Vector2i& mousePosition, sf::Event event) {
    if (!newGameMap || !newGameMap->sections)
        return;

    MapSection* currentSection = newGameMap->sections[sectionSelected - 1];
    
    if (!currentSection)
        return;

    sf::Vector2i viewportMousePos = sf::Mouse::getPosition(tileViewPort);
    
    if (viewportMousePos.x < 0 || viewportMousePos.y < 0 || viewportMousePos.x >= 512 || viewportMousePos.y >= 512) 
        return;
        

    int cellX = viewportMousePos.x / tileSize;
    int cellY = viewportMousePos.y / tileSize;
    static int lastCellX = -1;
    static int lastCellY = -1;

    if ((cellX != lastCellX || cellY != lastCellY) && cellX >= 0 && cellY >= 0 && cellX < currentSection->numberOfCellsPerRow && cellY < currentSection->numberOfCellsPerRow) {
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

    for (int y = 0; y < section->numberOfCellsPerRow; y++) {
        for (int x = 0; x < section->numberOfCellsPerRow; x++) {
            TileCell& cell = section->tilecellArray[y][x];
            
            if (cell.cellType == 'V' && cell.shape.getFillColor() != sf::Color(100, 100, 100, 100)) {
                cell.shape.setFillColor(sf::Color(100, 100, 100, 100)); // Gray for 'V'
                std::cout << "Setting cell (" << x << ", " << y << ") to void with gray color\n";
            } else if (cell.cellType == 'C' && cell.shape.getFillColor() != sf::Color(0, 0, 255, 100)) {
                cell.shape.setFillColor(sf::Color(0, 0, 255, 100)); // Blue for 'C'
                std::cout << "Setting cell (" << x << ", " << y << ") to collider with blue color\n";
            }

            window.draw(cell.shape);

            if (cell.cellType == 'C' || cell.cellType == 'V') {
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

void WorldEditor::tilemapDraw(sf::RenderWindow& window) {
    if(!newGameMap || !newGameMap->sections || sectionSelected <= 0)
        return;
    
    MapSection* currentSection = newGameMap->sections[sectionSelected - 1];
    if(!currentSection) return;

    if (getCellSize() != previousCellSize) {
        int gridSize = 512 / getCellSize();
        deallocateTileCellArray(currentSection);
        allocateTileCellArray(currentSection, gridSize);
        previousCellSize = getCellSize();
    }

    displayTileSection(window, currentSection);
}

void WorldEditor::tilemapUpdate(sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i viewportMousePos = sf::Mouse::getPosition(tileViewPort);
    checkMousePositionAndClicksWithShift(viewportMousePos, event);
}

void WorldEditor::allocateArrayCharEncoder(TileCell& tileCell) {
    tileCell.cellType = 'V';
    tileCell.shape.setFillColor(sf::Color::Transparent);
    tileCell.shape.setOutlineColor(sf::Color::Red);
    tileCell.shape.setOutlineThickness(0.5f);
    tileCell.textureID = -1;
}