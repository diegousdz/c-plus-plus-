#include "Game.h"
#include "./../Core/ResourceManager.h"
#include "../GameEntities/Orc.h"

Game::Game()
{
    
}

void Game::init(sf::RenderWindow& window, Player user)
{
    camera.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    camera.setCenter(user.shape.getPosition());
}

void Game::updateBackgroundPosition()
{
    worldOffset.x = camera.getCenter().x - (camera.getSize().x / 2);
    worldOffset.y = camera.getCenter().y - (camera.getSize().y / 2);
    background.setPosition(worldOffset.x * 0.5f, worldOffset.y * 0.5f); 
}
void Game::update(float deltaTime, Player player)
{
    const float cameraSmoothing = 0.001f;

    // Get the current camera center and player position
    sf::Vector2f cameraCenter = camera.getCenter();
    sf::Vector2f playerPosition = player.shape.getPosition();

    // Interpolate between the camera center and player position
    cameraCenter.x += (playerPosition.x - cameraCenter.x) * cameraSmoothing;
    cameraCenter.y += (playerPosition.y - cameraCenter.y) * cameraSmoothing;

    camera.setCenter(cameraCenter);
  //  camera.setCenter(player.shape.getPosition());
   // updateBackgroundPosition();
}

void Game::draw(sf::RenderWindow& window, Player user)
{
    sf::RectangleShape debugShape(sf::Vector2f(50.0f, 37.0f));
    debugShape.setFillColor(sf::Color(0, 255, 0, 128)); // Semi-transparent green
    debugShape.setPosition(user.shape.getPosition());
    window.draw(debugShape);
    window.setView(camera);
    window.draw(user.currentSprite);
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
