#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class AnimationSequencer {
public:
    
    std::map<int, std::vector<sf::Sprite>> animationFramesPlayer; 
    std::map<int, std::vector<sf::Sprite>> animationFramesOrcs;  
    
    int loadAnimationFrames(int animationType, const std::string& filePath, int totalFrames, int frameWidth, int frameHeight);
    int loadAnimationFramesOrc(int animationType, const std::string& filePath, int totalFrames, int frameWidth, int frameHeight);
    
    sf::Sprite& getCurrentSpritePlayer(int animationType, int currentFrame);

    bool isFlipedPlayer = false;
    sf::IntRect frameRect;
};