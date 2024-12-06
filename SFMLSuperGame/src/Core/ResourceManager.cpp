#include "ResourceManager.h"
#include "HelperFunctions.h"

void ResourceManager::allocateEnemies() {
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile("res/textures/Orc/spritesheetenemy.png")) {
        std::cout << "Failed to load spritesheet: " << std::endl;
    }

    if (!hasSpawnOneInitialized) {
        for (int i = 0; i < 5; i++) {
            Orc* newOrc = new Orc();
            orcSpawnManagerOne[i] = new Orc();
            orcSpawnManagerOne[i]->setTexture(&enemyTexture);
            orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Transparent);
            newOrc->currentSpriteOrc.setTexture(*texture);
            std::cout << "CURRENT position " << i << std::endl;

            newOrc->shape.setSize(sf::Vector2f(32.0f, 32.0f));
            newOrc->isOnGround = false;
            newOrc->isInitialized = false;
            newOrc->hasCollidedWithPlayer = false;
            orcSpawnManagerOne[i] = newOrc;
        }

        for (int i = 0; i < 5; i++) {
            if (i == 0) {
                orcSpawnManagerOne[0]->shape.setPosition(310.219f, helperFunctions.recalculateYPosition(2));
                std::cout << "initial position 0"
                          << "X: " << orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
            } else if (i == 1) {
                orcSpawnManagerOne[1]->shape.setPosition(500.075f, helperFunctions.recalculateYPosition(2));
                std::cout << "initial position 1"
                          << "X: " << orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
            } else if (i == 2) {
                orcSpawnManagerOne[2]->shape.setPosition(1376.5f, helperFunctions.recalculateYPosition(2));
                std::cout << "initial position 2"
                          << "X: " << orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
            } else if (i == 3) {
                orcSpawnManagerOne[3]->shape.setPosition(2172.95f, helperFunctions.recalculateYPosition(1));
                std::cout << "initial position 3"
                          << "X: " << orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
            } else if (i == 4) {
                orcSpawnManagerOne[4]->shape.setPosition(2865.23f, helperFunctions.recalculateYPosition(2));
                std::cout << "initial position 4"
                          << "X: " << orcSpawnManagerOne[i]->shape.getPosition().x << "Y" << orcSpawnManagerOne[i]->shape.getPosition().y << std::endl;
            }
        }
        hasSpawnOneInitialized = true;
    }
}

void ResourceManager::loadResources() {
    gameWin = false;
    winScreenInitialized = false;

    if (!playerTexture.loadFromFile("res/textures/Player/Tilemap/Idle/spritesheetIdle.png")) {
        std::cout << "Failed to load player texture!" << std::endl;
    }

    if (!playerIdleTexture.loadFromFile("res/textures/Player/Tilemap/Idle/spritesheetIdle.png")) {
        std::cout << "Failed to load player idle texture!" << std::endl;
    }

    if (!playerRunTexture.loadFromFile("res/textures/Player/Tilemap/Run/spritesheetRun.png")) {
        std::cout << "Failed to load player run texture!" << std::endl;
    }

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
        std::cout << "Failed to load orc base texture!" << std::endl;
    } else {
        std::cout << "orc base texture loaded successfully" << std::endl;
    }

    newGamePlayer.setTexture(&playerIdleTexture);
    newGamePlayer.loadAnimationsPlayer();
    loadGameBackgrounds();

    if (!soundSequencer.soundSequencerInit()) {
        std::cerr << "SoundSequencer failed to initialize." << std::endl;
    } else {
        std::cout << "SoundSequencer initialized successfully." << std::endl;
    }
}

void ResourceManager::loadGameBackgrounds() {
    if (!hasTexturesForGameLoaded) {
        if (!backgroundOne.loadFromFile("res/textures/World/backgrounds/backgroundOne.png")) {
            std::cout << "FAILED to load bg 1 texture!" << std::endl;
        } else {
            backgroundOne.setSmooth(true);
            backgroundSpriteOne.setTexture(backgroundOne);
            backgroundSpriteOne.setPosition(0, 0);
            hasTextureToSpriteOneFinished = true;
            std::cout << "bg 1 texture loaded!" << std::endl;

            std::cout << "Background texture size: " << backgroundOne.getSize().x << "x" << backgroundOne.getSize().y << std::endl;
        }
        hasTexturesForGameLoaded = true;
    }
}

void ResourceManager::setDeltaTime() {
    deltaTime = clock.restart().asSeconds();
}

float ResourceManager::getDeltaTime() const {
    return deltaTime;
}

void ResourceManager::updateAndMoveOrcs(float deltaTime) const {
    float positionUpdateOrcOneA = 310.219f, positionUpdateOrcOneB = 96.0f;
    float positionUpdateOrcTwoA = 632.0f, positionUpdateOrcTwoB = 440.0f;
    float positionUpdateOrcThreeA = 1531.63f, positionUpdateOrcThreeB = 1376.5f;
    float positionUpdateOrcFourA = 2425.39f, positionUpdateOrcFourB = 2172.95f;
    float positionUpdateOrcFiveA = 2865.23f, positionUpdateOrcFiveB = 2624.5f;

    const float movementSpeed = 64.0f;
    const float gravity = 981.0f;

    for (int i = 0; i < 5; i++) {
        Orc* orc = orcSpawnManagerOne[i];
        float currentPositionX = orc->shape.getPosition().x;
        orc->currentSpriteOrc.setPosition(orc->shape.getPosition().x, orc->shape.getPosition().y);

        if (!orc->isInitialized) {
            orc->velocity.x = movementSpeed;
            orc->velocity.y = 0.0f;
            orc->isInitialized = true;
        }

        if (!orc->isOnGround) {
           // orc->velocity.y += gravity * deltaTime;
        } else {
            orc->velocity.y = 0.0f;
        }

        orc->shape.move(orc->velocity * deltaTime);
        orc->isOnGround = false;

        float positionA, positionB;
        switch (i) {
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

        if (currentPositionX <= positionB) {
            orc->velocity.x = abs(movementSpeed);
        } else if (currentPositionX >= positionA) {
            orc->velocity.x = -abs(movementSpeed);
        }

        if (currentPositionX < positionB) {
            orc->shape.setPosition(positionB, orc->shape.getPosition().y);
        } else if (currentPositionX > positionA) {
            orc->shape.setPosition(positionA, orc->shape.getPosition().y);
        }

        orc->updateAnimation(deltaTime);
    }
}

int ResourceManager::getPlayerTypeOfAnimationLastSet() const {
    return playerTypeOfAnimationLastSet;
}

void ResourceManager::setPlayerTypeOfAnimationLastSet(int type) {
    playerTypeOfAnimationLastSet = type;
}

ResourceManager::~ResourceManager() {
    for (int i = 0; i < 5; i++) {
        delete orcSpawnManagerOne[i];
    }

    for (int i = 0; i < NUMBER_OF_ENEMY_LEVEL_ONE; i++) {
        delete orcWarriorsPoolShapes[i];
    }
}

void ResourceManager::setSpawnPointOne(int index, Orc* orc)
{
    if (index >= 0 && index < 5) 
        orcSpawnManagerOne[index] = orc;
}

Orc* ResourceManager::getSpawnPointOne(int index) const
{
    if (index >= 0 && index < 5) 
        return orcSpawnManagerOne[index];
    
    return nullptr; 
}

sf::Sprite& ResourceManager::getBackgroundSpriteOne()
{
        return backgroundSpriteOne;
}

void setOrcTypeOfAnimationLastSet(int animationType, Orc* orc) {
    if (!orc) return;

    switch (animationType) {
    case 0:
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Idle][orc->currentFrame];
        orc->currentAction = Orc::Idle;
        break;
    case 1:
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Run][orc->currentFrame];
        orc->currentAction = Orc::Run;
        break;
    case 2:
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Attack][orc->currentFrame];
        orc->currentAction = Orc::Attack;
        break;
    case 3:
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Hurt][orc->currentFrame];
        orc->currentAction = Orc::Hurt;
        break;
    case 4:
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Die][orc->currentFrame];
        orc->currentAction = Orc::Die;
        break;
    default:
        orc->currentSpriteOrc = orc->animSequencerOrc.animationFramesOrcs[Orc::Idle][orc->currentFrame];
        orc->currentAction = Orc::Idle;
        break;
    }

    if (orc->onInverseDirection) {
        orc->currentSpriteOrc.setScale(-1.0f, 1.0f);
        orc->currentSpriteOrc.setPosition(orc->shape.getPosition().x + orc->shape.getSize().x, orc->shape.getPosition().y);
    } else {
        orc->currentSpriteOrc.setScale(1.0f, 1.0f);
        orc->currentSpriteOrc.setPosition(orc->shape.getPosition());
    }
}