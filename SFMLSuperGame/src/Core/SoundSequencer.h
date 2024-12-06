#pragma once
#include <SFML/Audio.hpp>

class SoundSequencer {
public:
    SoundSequencer();
    
    bool loadSoundBuffers();
    bool initBuffers();
    bool soundSequencerInit();

    void playPlayerIdleSound();
    void playPlayerRunSound();
    void stopPlayerRunSound();
    void playPlayerJumpSound();
    void playPlayerOnGroundSound();
    void playPlayerOnPlayerHitSound();
    void playPlayerDieSound();

private:
    static constexpr int MAX_PLAYER_SOUNDS = 6;
    int currentAnimationPLayerPLayed = 0;
    
    sf::SoundBuffer soundBufferPoolPlayer[MAX_PLAYER_SOUNDS];
    sf::Sound soundPoolPlayer[MAX_PLAYER_SOUNDS];

    bool hasInitBuffers = false;
    
    std::vector<std::string> soundFilesPoolPlayer = { 
        "res/sounds/player/Idle.wav",
        "res/sounds/player/Run.wav",
        "res/sounds/player/Jump.wav",
        "res/sounds/player/OnGround.wav",
        "res/sounds/player/OnPlayerHit.wav",
        "res/sounds/player/Die.wav"
    };
};