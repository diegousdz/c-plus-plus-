#include "AnimationSequencer.h"
#include <iostream>

// Generic function to load frames from a spritesheet
int AnimationSequencer::loadAnimationFrames(int animationType, const std::string& filePath, int totalFrames, int frameWidth, int frameHeight)
{
    // Load the entire spritesheet
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(filePath))
    {
        std::cout << "Failed to load spritesheet: " << filePath << std::endl;
        return -1;  // Return error if loading fails
    }

    // Resize the vector in the map to store the number of frames
    animationFrames[animationType].resize(totalFrames);


    for (int i = 0; i < totalFrames; ++i)
    {
        // Define the frame boundaries
        frameRect = sf::IntRect (i * frameWidth, 0, frameWidth, frameHeight);  
    
        std::cout << "Loaded frame " << i << " for animation type " << animationType << std::endl;
    
        // Set the texture and texture rectangle for each sprite
        animationFrames[animationType][i].setTexture(*texture);
        // 
        animationFrames[animationType][i].setTextureRect(frameRect);
    }
    

    return totalFrames;  // Return the number of frames loaded
}

// Get the current sprite for the specified animation type and frame index
sf::Sprite& AnimationSequencer::getCurrentSprite(int animationType, int currentFrame)
{
    int totalFrames;  // Get the total number of frames
    totalFrames = static_cast<int>(animationFrames[animationType].size());
    int frameIndex = currentFrame % totalFrames;  // Ensure we loop through the frames correctly

    return animationFrames[animationType][frameIndex];  // Return the correct frame
}

void AnimationSequencer::updateOrientation(int animationType, bool isFlipped)
{
    int frameWidth = 50;   // Adjust as needed
    int frameHeight = 37;  // Adjust as needed
    int totalFrames = static_cast<int>(animationFrames[animationType].size());

    for (int i = 0; i < totalFrames; ++i)
    {
        // Adjust frameRect to flip or unflip the texture
        sf::IntRect frameRect = isFlipped
            ? sf::IntRect((i + 1) * frameWidth, 0, -frameWidth, frameHeight)  // Flipped frame
            : sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight);        // Default frame
        
        animationFrames[animationType][i].setTextureRect(frameRect);
    }

    std::cout << "Updated orientation for animation type " << animationType 
              << " (flipped: " << isFlipped << ")" << std::endl;
}

 sf::IntRect& AnimationSequencer::getCurrentFrameRect(int animationType, int currentFrame)
{
    int totalFrames = static_cast<int>(animationFrames[animationType].size());
    int frameIndex = currentFrame % totalFrames;
    return frameRect;
}