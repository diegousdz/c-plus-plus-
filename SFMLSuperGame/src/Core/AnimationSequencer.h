#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class AnimationSequencer
{
public:
    
    std::map<int, std::vector<sf::Sprite>> animationFramesPlayer;  // Map of animation type to frames
    std::map<int, std::vector<sf::Sprite>> animationFramesOrcs;  // Map of animation type to frames
    
    int loadAnimationFrames(int animationType, const std::string& filePath, int totalFrames, int frameWidth, int frameHeightt);
    int loadAnimationFramesOrc(int animationType, const std::string& filePath, int totalFrames, int frameWidth,
                               int frameHeight);

    // Function to return the current sprite for any animation type
    sf::Sprite& getCurrentSpritePlayer(int animationType, int currentFrame);
    void updateOrientation(int animationType, bool isFlipped);
    sf::IntRect& getCurrentFrameRect(int animationType, int currentFrame);


    bool isFlipedPlayer = false;
    sf::IntRect frameRect;
};
