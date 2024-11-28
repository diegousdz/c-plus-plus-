#include "../Tools/WorldEditor.h"
#include "./../Core/NexusManager.h"

bool inEditorMode = false;

int main() {
    if (inEditorMode) {
        sf::RenderWindow editorWindow(sf::VideoMode(256, 512), "Tilemap Editor");
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        WorldEditor& editor = WorldEditor::getInstance();

        editor.init();
        if (!backgroundTexture.loadFromFile("res/textures/World/backgrounds/backgroundOne.png")) {
            std::cout << "FAILED to load bg 1 texture!" << std::endl;
        } else {
            backgroundSprite.setTexture(backgroundTexture);
            backgroundSprite.setPosition(0, 0);
        }

        while (editorWindow.isOpen() || editor.tileViewPort.isOpen()) {
            sf::Event event;
            while (editorWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    editorWindow.close();
            }

            editorWindow.clear();
            editor.draw(editorWindow);
            editor.Update(editorWindow, event);
            editor.setBackgroundPosition(backgroundSprite, editor.sectionSelected);
            editorWindow.display();

            if (editor.tileViewPort.isOpen()) {
                sf::Event tileEvent;

                while (editor.tileViewPort.pollEvent(tileEvent)) {
                    if (tileEvent.type == sf::Event::Closed)
                        editor.tileViewPort.close();
                }

                editor.tileViewPort.clear(sf::Color(50, 50, 50));
                editor.tileViewPort.draw(backgroundSprite);
                editor.tilemapDraw(editor.tileViewPort);
                editor.tilemapUpdate(editor.tileViewPort, tileEvent);
                editor.tileViewPort.display();
            } else if (editor.hasCreatedTilemap) {
                editor.tileViewPort.create(sf::VideoMode(512, 512), "Tilemap Viewport");
                editor.hasCreatedTilemap = false;
            }
        }
    } else {
        NexusManager& nexusManager = NexusManager::getInstance();
        nexusManager.getResourceManager().setWindowWidth(1280);
        nexusManager.getResourceManager().setWindowHeight(720);
        nexusManager.initializeWindow(
            nexusManager.getResourceManager().gameWindow,
            nexusManager.getResourceManager().windowWidth,
            nexusManager.getResourceManager().windowHeight,
            "Frost & Stone"
        );
        nexusManager.init();

        while (nexusManager.getResourceManager().gameWindow.isOpen()) {
            nexusManager.getResourceManager().setDeltaTime();
            nexusManager.handleInput();
            nexusManager.update(nexusManager.getResourceManager().getDeltaTime());
            nexusManager.draw(nexusManager.getResourceManager().gameWindow);
        }
    }
    return 0;
}