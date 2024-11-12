﻿#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class AnimationSequencer
{
public:
    
    std::map<int, std::vector<sf::Sprite>> animationFrames;  // Map of animation type to frames

    // Generic function to load a spritesheet and extract frames for any animation
    int loadAnimationFrames(int animationType, const std::string& filePath, int totalFrames, int frameWidth, int frameHeightt);

    // Function to return the current sprite for any animation type
    sf::Sprite& getCurrentSprite(int animationType, int currentFrame);
    void updateOrientation(int animationType, bool isFlipped);
    sf::IntRect& getCurrentFrameRect(int animationType, int currentFrame);


    bool isFlipedPlayer = false;
    sf::IntRect frameRect;
};
