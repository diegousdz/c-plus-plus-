#pragma once
#include <SFML/Audio.hpp>

class SoundSequencer
{ 
    int loadSoundBuffers();
private:
    sf::SoundBuffer soundBuffer[6];
};
