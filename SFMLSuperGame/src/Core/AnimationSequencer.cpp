#include "AnimationSequencer.h"
#include <iostream>

int AnimationSequencer::loadAnimationFrames(int animationType, const std::string& filePath, int totalFrames, int frameWidth, int frameHeight) {
    
    sf::Texture* texture = new sf::Texture();
    
    if (!texture->loadFromFile(filePath)) {
        std::cout << "Failed to load spritesheet: " << filePath << std::endl;
        return -1; 
    }
    
    animationFramesPlayer[animationType].resize(totalFrames);

    for (int i = 0; i < totalFrames; ++i) {
        frameRect = sf::IntRect (i * frameWidth, 0, frameWidth, frameHeight);  
        animationFramesPlayer[animationType][i].setTexture(*texture);
        animationFramesPlayer[animationType][i].setTextureRect(frameRect);
        std::cout << "Loaded frame " << i << " for animation type " << animationType << std::endl;
    }
    
    return totalFrames;  
}

int AnimationSequencer::loadAnimationFramesOrc(int animationType, const std::string& filePath, int totalFrames, int frameWidth, int frameHeight) {

    sf::Texture* texture = new sf::Texture();
    
    if (!texture->loadFromFile(filePath)) {
        std::cout << "Failed to load spritesheet: " << filePath << std::endl;
        return -1;
    }
    
    animationFramesOrcs[animationType].resize(totalFrames);

    for (int i = 0; i < totalFrames; ++i) {
        frameRect = sf::IntRect (i * frameWidth, 0, frameWidth, frameHeight);  
        animationFramesOrcs[animationType][i].setTexture(*texture);
        std::cout << "Loaded frame " << i << " for animation type " << animationType << std::endl;
    }

    return totalFrames;  
}

sf::Sprite& AnimationSequencer::getCurrentSpritePlayer(int animationType, int currentFrame) {
    
    int totalFrames = static_cast<int>(animationFramesPlayer[animationType].size());
    int frameIndex;
    
    if (animationType == 3) {
        frameIndex = std::min(currentFrame, totalFrames - 1);
    } else {
        frameIndex  = currentFrame % totalFrames;
    }
    return animationFramesPlayer[animationType][frameIndex]; 
}