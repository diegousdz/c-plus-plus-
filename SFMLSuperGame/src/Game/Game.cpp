#include "Game.h"
#include "./../Core/ResourceManager.h"
#include "../GameEntities/Orc.h"

Game::Game(Player user, int nOfEnemies)
{
    ResourceManager resourceManager;
    resourceManager.loadResources();  // Load resources (including player textures)
    
    // Now use the preloaded player from ResourceManager
    user = resourceManager.newGamePlayer; 
    
}

void Game::createEnemiesLevelOne()
{
   /* for (int i = 0; i < 5; i++)
    {
        Orc newOrc = resocreateOrc();
        orcWarriorsPoolShapes[i] = newOrc;
        float xPosition = 50.0f + (i * 70); 
        float yPosition = windowHeight - newOrc.enemySize;            

        orcWarriorsPoolShapes[i].shape.setPosition(xPosition, yPosition);
        
        // TODD:  gameWindow.draw(orcWarriorsPoolShapes[i].shape);
    } */
}
