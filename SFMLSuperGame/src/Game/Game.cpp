#include "Game.h"
#include "./../Core/ResourceManager.h"
#include "../GameEntities/Orc.h"
#include "../Tools/Tilemap.h"

Game::Game()
{
    
}

void Game::init(sf::RenderWindow& window, ResourceManager& resourceManager, Player& player)
{

    player.setPlayerPosition(resourceManager.initalSpawnPositionLevelOne);
    if(!isGameMapLoaded)
    {
      //  Tilemap tilemap;
        // tilemap.LoadMapData
    }

    if(resourceManager.currentUserLevel == 1)
    {
       
    }
    sf::View view = window.getDefaultView();
    camera.setSize(static_cast<float>(window.getSize().x) , static_cast<float>(window.getSize().y));
    camera.setCenter(player.shape.getPosition().x + static_cast<float>(window.getSize().x) /2, 0.0f);
    camera.zoom(0.6);

 //   std::cout << "Finished initializing: " << std::endl;
}

void Game::inputHandle()
{
     
}

void Game::update(float deltaTime, Player& player)
{
 //   player.setPlayerPosition(sf::Vector2f(100.0f, 512.0f));
  //  std::cout << "Camera Center: " << camera.getCenter().x << ", " << camera.getCenter().y << std::endl;
 //   std::cout << "Player Position: " << player.shape.getPosition().x << ", " << player.shape.getPosition().y << std::endl;
    camera.setCenter(player.shape.getPosition());
   // calculate position
    // Update player movement first
   // player.onInverseDirection;
    //isFlipedPlayer = false;
    player.handleMovement(deltaTime);
    
    // Let GEM handle all collisions
 //   entityManager.gemUpdate(player);
    
    // Update camera after final player position is determined
  //  updateCamera(deltaTime, player);
    /*
    const float cameraSmoothing = 0.001f;

    // Get the current camera center and player position
    sf::Vector2f cameraCenter = camera.getCenter();
    sf::Vector2f playerPosition = player.shape.getPosition();

    // Interpolate between the camera center and player position
    cameraCenter.x += (playerPosition.x - cameraCenter.x) * cameraSmoothing;
    cameraCenter.y += (playerPosition.y - cameraCenter.y) * cameraSmoothing;
    

   // camera.setCenter(cameraCenter);
    camera.setCenter(player.shape.getPosition());
    updateBackgroundPosition();*/
}

void Game::draw(sf::RenderWindow& window, ResourceManager& resourceManager)
{
    if(!resourceManager.isMainMenuActive)
        window.setView(camera);
   // window.setView(camera);
    window.draw(resourceManager.backgroundSpriteOne);
    window.draw(resourceManager.newGamePlayer.currentSprite);
 //   window.draw(resourceManager.backgroundSpriteOne);
}


void Game::composeRender(sf::RenderWindow& window, ResourceManager& resourceManager)
{
    window.draw(resourceManager.backgroundSpriteOne);
}
