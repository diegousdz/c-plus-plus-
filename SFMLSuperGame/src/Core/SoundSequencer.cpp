#include "SoundSequencer.h"

int SoundSequencer::loadSoundBuffers() {
   
    if (!this->soundBuffer[0].loadFromFile("res/player/Idle.wav")) {
       return -1;
    }

    if (!this->soundBuffer[1].loadFromFile("res/player/Run.wav")) {
       return -1;
    }

    if (!this->soundBuffer[2].loadFromFile("res/player/Jump.wav")) {
       return -1;
    }

   if (!this->soundBuffer[3].loadFromFile("res/player/Fall.wav")) {
       return -1;
    }

   if (!this->soundBuffer[4].loadFromFile("res/player/Attack.wav")) {
       return -1;
    }

   if (!this->soundBuffer[5].loadFromFile("res/player/Die.wav")) {
       return -1;
   }

   return 0;
}
