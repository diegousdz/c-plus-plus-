#include "ResourceManager.h"

void ResourceManager::loadResources()
{ 
}

void ResourceManager::setDeltaTime()
{
     deltaTime = clock.restart().asSeconds();
}

float ResourceManager::getDeltaTime() const
{
    return deltaTime;
}

Orc createOrc()
{
    Orc orcWarrior;
    
    orcWarrior.shape.setPosition(100, 0);
    
    orcWarrior.shape.setFillColor(sf::Color::Red);  // Orcs are red by default

    return orcWarrior;  // Return the created Orc
}

void ResourceManager::createEnemiesLevelOne()
{

        for (int i = 0; i < 5; i++)
        {
            Orc newOrc = createOrc();
            orcWarriorsPoolShapes[i] = newOrc;
            float xPosition = 50.0f + (i * 70); 
            float yPosition = windowHeight - newOrc.enemySize;            

            orcWarriorsPoolShapes[i].shape.setPosition(xPosition, yPosition);
        
            // TODD:  gameWindow.draw(orcWarriorsPoolShapes[i].shape);
        }
    
}
