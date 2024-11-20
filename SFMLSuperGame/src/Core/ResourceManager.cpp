#include "ResourceManager.h"

#include "HelperFunctions.h"

void ResourceManager::allocateEnemies()
{
    // Allocate orcs for spawn manager one
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile("res/textures/Orc/spritesheetenemy.png"))
    {
        std::cout << "Failed to load spritesheet: " << std::endl;
    } 
    
    if(!hasSpawnOneInitialized)
    {
        for (int i = 0; i < 5; i++)
        {
            Orc* newOrc = new Orc();
            
            orcSpawnManagerOne[i] = new Orc();
   
         
         //   orcSpawnManagerOne[i]->loadAnimationsOrc();
            orcSpawnManagerOne[i]->setTexture(&enemyTexture);
            orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Transparent);
            

            newOrc->currentSpriteOrc.setTexture(*texture);
            std::cout << "CURRENT position " << i << std::endl;
            
          //  backgroundSpriteOne.setPosition(0, 0);          // Position it at the origin

            newOrc->shape.setSize(sf::Vector2f(32.0f, 32.0f));
            newOrc->isOnGround = false;
            newOrc->isInitialized = false;
            newOrc->hasCollidedWithPlayer = false;
            orcSpawnManagerOne[i] = newOrc;
        }

        for (int i = 0; i < 5; i++)
        {
            if(i == 0)
            {
                // Set initial position and attributes
                   orcSpawnManagerOne[0]->shape.setPosition(310.219f, helperFunctions.recalculateYPositionNegate(3));
      
                std::cout << "initial position 0" << "X: " <<  orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
               
                //   orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 1)
            {
                // Set initial position and attributes
                   orcSpawnManagerOne[1]->shape.setPosition(500.075f, helperFunctions.recalculateYPositionNegate(4));
                std::cout << "initial position 1" << "X: " <<  orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
               
                //  orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 2)
            {
                // Set initial position and attributes
                    orcSpawnManagerOne[2]->shape.setPosition(1376.5f, helperFunctions.recalculateYPositionNegate(7));
                std::cout << "initial position 2" << "X: " <<  orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
               
                //   orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 3)
            {
                // Set initial position and attributes
                    orcSpawnManagerOne[3]->shape.setPosition(2172.95f, helperFunctions.recalculateYPositionNegate(7));
                std::cout << "initial position 3" << "X: " <<  orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
               
                //   orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 4)
            {
                // Set initial position and attributes
                orcSpawnManagerOne[4]->shape.setPosition(2865.23f, helperFunctions.recalculateYPositionNegate(7));
                std::cout << "initial position 4" << "X: " <<  orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
               
                //   orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            }
        }
        hasSpawnOneInitialized = true;
    }

}


void ResourceManager::loadResources()
{
    gameWin = false;
    winScreenInitialized = false;
    
    // Load the player's texture for placeholder (if needed)
    if (!playerTexture.loadFromFile("res/textures/Player/Tilemap/Idle/spritesheetIdle.png")) {
        std::cout << "Failed to load player texture!" << std::endl;
    }

    // Load the player's idle texture
    if (!playerIdleTexture.loadFromFile("res/textures/Player/Tilemap/Idle/spritesheetIdle.png")) {
        std::cout << "Failed to load player idle texture!" << std::endl;
    }

    // Load the player's run texture
    if (!playerRunTexture.loadFromFile("res/textures/Player/Tilemap/Run/spritesheetRun.png")) {
        std::cout << "Failed to load player run texture!" << std::endl;
    }

    // Load the player's jump texture
    if (!playerJumpTexture.loadFromFile("res/textures/Player/Tilemap/Jump/spritesheetJump.png")) {
        std::cout << "Failed to load player jump texture!" << std::endl;
    }
    
    if (!playerAttack.loadFromFile("res/textures/Player/Tilemap/Attack/spritesheetAttack.png")) {
        std::cout << "Failed to load player jump texture!" << std::endl;
    }

    if (!heartTexture.loadFromFile("res/textures/gameplay/heart.png")) {
        std::cout << "Failed to load heart texture!" << std::endl;
    }

    
    if (!backgroundMainMenuTexture.loadFromFile("res/textures/gameplay/menuBackground.png")) {
        std::cout << "Failed to load background texture!" << std::endl;
    } else {
        std::cout << "Background texture loaded successfully" << std::endl;
    }

    if (!enemyTexture.loadFromFile("res/textures/Orc/spritesheetenemy.png")) {
        std::cout << "Failed to load  orc base texture!" << std::endl;
    } else {
        std::cout << "orc base texture loaded successfully" << std::endl;
    }


    // Initialize the player with the loaded texture
    newGamePlayer.setTexture(&playerIdleTexture);

    // Load animations
    newGamePlayer.loadAnimationsPlayer();

    // You can also load other textures here (like for Orc, enemies, etc.)
    loadGameBackgrounds();
}

void ResourceManager::loadGameBackgrounds()
{
    if (!hasTexturesForGameLoaded) { 
        if (!backgroundOne.loadFromFile("res/textures/World/backgrounds/backgroundOne.png")) {
            std::cout << "FAILED to load bg 1 texture!" << std::endl;
        } else {
            backgroundOne.setSmooth(true);
            backgroundSpriteOne.setTexture(backgroundOne);  // Set the texture to backgroundOne
            backgroundSpriteOne.setPosition(0, 0);          // Position it at the origin
            hasTextureToSpriteOneFinished = true;
            std::cout << "bg 1 texture loaded!" << std::endl;

            // Debugging: Print out texture size to verify
            std::cout << "Background texture size: " 
                      << backgroundOne.getSize().x << "x" 
                      << backgroundOne.getSize().y << std::endl;
        }
        hasTexturesForGameLoaded = true;
    }
}



void ResourceManager::setDeltaTime()
{
     deltaTime = clock.restart().asSeconds();
}

float ResourceManager::getDeltaTime() const
{
    return deltaTime;
}

// ResourceManager.cpp
// ResourceManager.cpp

void ResourceManager::updateAndMoveOrcs(float deltaTime)
{

    
    float positionUpdateOrcOneA = 310.219f, positionUpdateOrcOneB = 96.0f;
    float positionUpdateOrcTwoA = 632.0f, positionUpdateOrcTwoB = 440.0f;
    float positionUpdateOrcThreeA = 1531.63f, positionUpdateOrcThreeB = 1376.5f;
    float positionUpdateOrcFourA = 2425.39f, positionUpdateOrcFourB =  2172.95f;
    float positionUpdateOrcFiveA = 2865.23f, positionUpdateOrcFiveB = 2624.5f;

    // Define movement speed (pixels per second)
    const float movementSpeed = 64.0f;
    const float gravity = 981.0f; // Gravity acceleration (pixels per second squared)

    for (int i = 0; i < 5; i++)
    {
        Orc* orc = orcSpawnManagerOne[i];

        float currentPositionX = orc->shape.getPosition().x;
        float currentPositionY = orc->shape.getPosition().y;

        orc->currentSpriteOrc.setPosition(orc->shape.getPosition().x, orc->shape.getPosition().y);
        // Initialize orc velocity if not already initialized
        if (!orc->isInitialized)
        {
            orc->velocity.x = movementSpeed;
            orc->velocity.y = 0.0f;
            orc->isInitialized = true;
        }

        // Apply gravity to vertical velocity
        if (!orc->isOnGround)
        {
            orc->velocity.y += gravity * deltaTime;
        }
        else
        {
            orc->velocity.y = 0.0f;
        }

        // Move orc using velocity
        orc->shape.move(orc->velocity * deltaTime);

        // Assume orc is airborne until collision detected
        orc->isOnGround = false;

        // Define boundaries dynamically
        float positionA, positionB;
        switch (i)
        {
        case 0:
            positionA = positionUpdateOrcOneA;
            positionB = positionUpdateOrcOneB;
            break;
        case 1:
            positionA = positionUpdateOrcTwoA;
            positionB = positionUpdateOrcTwoB;
            break;
        case 2:
            positionA = positionUpdateOrcThreeA;
            positionB = positionUpdateOrcThreeB;
            break;
        case 3:
            positionA = positionUpdateOrcFourA;
            positionB = positionUpdateOrcFourB;
            break;
        case 4:
            positionA = positionUpdateOrcFiveA;
            positionB = positionUpdateOrcFiveB;
            break;
        default:
            positionA = 0;
            positionB = 0;
            break;
        }

        // Reverse direction if boundaries are reached
        if (currentPositionX <= positionB)
        {
            orc->velocity.x = abs(movementSpeed); // Move right
        }
        else if (currentPositionX >= positionA)
        {
            orc->velocity.x = -abs(movementSpeed); // Move left
            
        }

        // Ensure position is within boundaries
        if (currentPositionX < positionB)
        {
            orc->shape.setPosition(positionB, orc->shape.getPosition().y);
        //    orc->currentSpriteOrc.setPosition(orc->shape.getPosition().x, orc->shape.getPosition().y);
        }
        else if (currentPositionX > positionA)
        {
            orc->shape.setPosition(positionA, orc->shape.getPosition().y);
          
        }

        // Change the color of the orc for better visualization
        orc->updateAnimation(deltaTime);
    }
}


void ResourceManager::createEnemiesLevelOne(float initialPositionX, float initialPositionY)
{
    float spacing = orcSpawnManagerOne[0]->shape.getGlobalBounds().width + 20.0f; 

    // Position and initialize attributes for each Orc in the pool
    for (int i = 0; i < 2; i++)
    {
        if (orcSpawnManagerOne[i]) // Check if the orc exists
        {
            if(i == 1)
            {
                // Set initial position and attributes
             //   orcSpawnManagerOne[i]->shape.setPosition(310.219f, helperFunctions.recalculateYPositionNegate(3));
             //   orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 2)
            {
                // Set initial position and attributes
             //   orcSpawnManagerOne[i]->shape.setPosition(506.075f, helperFunctions.recalculateYPositionNegate(13));
              //  orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 3)
            {
                // Set initial position and attributes
            //    orcSpawnManagerOne[i]->shape.setPosition(2048, helperFunctions.recalculateYPositionNegate(13));
             //   orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 4)
            {
                // Set initial position and attributes
            //    orcSpawnManagerOne[i]->shape.setPosition(2422.99f, helperFunctions.recalculateYPositionNegate(13));
             //   orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else 
            {
                // Set initial position and attributes
           //     orcSpawnManagerOne[i]->shape.setPosition(2870.32f, helperFunctions.recalculateYPositionNegate(13));
              //  orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            }

        }
    }
}

int ResourceManager::getPlayerTypeOfAnimationLastSet() const {
    return playerTypeOfAnimationLastSet;
}

void ResourceManager::setPlayerTypeOfAnimationLastSet(int type) {
    playerTypeOfAnimationLastSet = type;
}

ResourceManager::~ResourceManager()
{
    // Clean up spawn manager orcs
    for (int i = 0; i < 5; i++)
    {
        delete orcSpawnManagerOne[i];
    }
    
    // Clean up level one pool orcs
    for (int i = 0; i < NUMBER_OF_ENEMY_LEVEL_ONE; i++)
    {
        delete orcWarriorsPoolShapes[i];
    }
}

void setOrcTypeOfAnimationLastSet(int animationType, Orc* orc) {
    if (!orc) return;
        
    switch(animationType) {
    case 0: // Idle
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Idle][orc->currentFrame];
        orc->currentAction = Orc::Idle;
        break;
                
    case 1: // Run
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Run][orc->currentFrame];
        orc->currentAction = Orc::Run;
        break;
                
    case 2: // Attack
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Attack][orc->currentFrame];
        orc->currentAction = Orc::Attack;
        break;
                
    case 3: // Hurt
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Hurt][orc->currentFrame];
        orc->currentAction = Orc::Hurt;
        break;
                
    case 4: // Die
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Die][orc->currentFrame];
        orc->currentAction = Orc::Die;
        break;
    default:
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Idle][orc->currentFrame];
        orc->currentAction = Orc::Idle;
        break;;
    }
        
    // Handle sprite direction
    if (orc->onInverseDirection) {
        orc->currentSpriteOrc.setScale(-1.0f, 1.0f);
        orc->currentSpriteOrc.setPosition(
            orc->shape.getPosition().x + orc->shape.getSize().x,
            orc->shape.getPosition().y
        );
    } else {
        orc->currentSpriteOrc.setScale(1.0f, 1.0f);
        orc->currentSpriteOrc.setPosition(orc->shape.getPosition());
    }

};