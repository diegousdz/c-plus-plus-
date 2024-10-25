#include <iostream>
#include <iso646.h>

#include "../Tools/WorldEditor.h"
#include "./../Core/NexusEngine.h"

bool inEditorMode = true;

int main()
{
    if(inEditorMode)
    {
        sf::RenderWindow editorWindow(sf::VideoMode(256, 512), "Tilemap Editor");
        WorldEditor& editor = WorldEditor::getInstance();
   
         editor.init();
        while (editorWindow.isOpen() || editor.tileViewPort.isOpen())
        {
            // Handle main window events
            sf::Event event;
            while (editorWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    editorWindow.close();
            }
                // Draw something in the editor window (like the tilemap for example)
                editorWindow.clear();
               
                editor.draw(editorWindow);
                editor.Update(editorWindow,  event);
            
                editorWindow.display();

            if(editor.hasCreatedTilemap)
            {
                if (editor.tileViewPort.isOpen())
                {
                    editor.tileViewPort.close();  // Close the existing tilemap window
                }

                editor.tileViewPort.create(sf::VideoMode(600, 600), "Tilemap Viewport");
                
                if (editor.tileViewPort.isOpen())
                {
                    while (editor.tileViewPort.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            editor.tileViewPort.close();
                        // Handle tilemap-specific events here
                    }
                    editor.tileViewPort.clear(sf::Color(50, 50, 50));
                
                    editor.tileViewPort.display();
                }
                editor.hasCreatedTilemap = false;
            }
           
        }
    
    } else
    {
        // create an instance of the engine
        NexusEngine& engine = NexusEngine::getInstance();
        engine.initializeWindow(engine.getResourceManager().gameWindow, 600, 600, "Stone & Frost");
        engine.init();
    
        while (engine.getResourceManager().gameWindow.isOpen())
        {
            engine.getResourceManager().setDeltaTime();
            engine.handleInput();
            engine.update(engine.getResourceManager().getDeltaTime());
            engine.draw(engine.getResourceManager().gameWindow);
        }
    }
    return 0;
}
