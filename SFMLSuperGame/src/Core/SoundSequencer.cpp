#include "SoundSequencer.h"

SoundSequencer::SoundSequencer() : currentAnimationPLayerPLayed(-1) {
}

bool SoundSequencer::loadSoundBuffers() {
    for (int i = 0; i < MAX_PLAYER_SOUNDS; i++) {
        if (!this->soundBufferPoolPlayer[i].loadFromFile(soundFilesPoolPlayer[i])) {
            hasInitBuffers = false;
            return hasInitBuffers;
        }
    }
    return true;
}

void SoundSequencer::playPlayerIdleSound() {
    if(hasInitBuffers && this->currentAnimationPLayerPLayed != 0) {
        if (this->currentAnimationPLayerPLayed >= 0 && this->currentAnimationPLayerPLayed < MAX_PLAYER_SOUNDS) 
            this->soundPoolPlayer[this->currentAnimationPLayerPLayed].stop();
        
        this->soundPoolPlayer[0].play();
        this->soundPoolPlayer[0].setLoop(true);
        this->soundPoolPlayer[0].setVolume(50.f);
        currentAnimationPLayerPLayed = 0;
    }
}

void SoundSequencer::playPlayerRunSound() {
    if (hasInitBuffers && this->currentAnimationPLayerPLayed != 1) {
        if (this->currentAnimationPLayerPLayed >= 0 && this->currentAnimationPLayerPLayed < MAX_PLAYER_SOUNDS) {
            this->soundPoolPlayer[this->currentAnimationPLayerPLayed].stop();
        }
        this->soundPoolPlayer[1].play();
        this->soundPoolPlayer[1].setLoop(true);
        this->soundPoolPlayer[1].setVolume(40.f);
        this->currentAnimationPLayerPLayed = 1;
    }
}

void SoundSequencer::stopPlayerRunSound() {
    if (hasInitBuffers && this->currentAnimationPLayerPLayed >= 0 && this->currentAnimationPLayerPLayed < MAX_PLAYER_SOUNDS) {
        this->soundPoolPlayer[currentAnimationPLayerPLayed].stop();
        this->currentAnimationPLayerPLayed = -1;
    }
}

void SoundSequencer::playPlayerJumpSound() {
    if (hasInitBuffers && this->currentAnimationPLayerPLayed != 2) {
        if (this->currentAnimationPLayerPLayed >= 0 && this->currentAnimationPLayerPLayed < MAX_PLAYER_SOUNDS) 
            this->soundPoolPlayer[this->currentAnimationPLayerPLayed].stop();
        
        this->soundPoolPlayer[2].play();
        this->soundPoolPlayer[2].setVolume(70.f);
        this->currentAnimationPLayerPLayed = 2;
    }
}

void SoundSequencer::playPlayerOnGroundSound() {
    if (hasInitBuffers && this->currentAnimationPLayerPLayed != 3) {
        if (this->currentAnimationPLayerPLayed >= 0 && this->currentAnimationPLayerPLayed < MAX_PLAYER_SOUNDS) 
            this->soundPoolPlayer[this->currentAnimationPLayerPLayed].stop();
        
        this->soundPoolPlayer[3].play();
        this->soundPoolPlayer[3].setVolume(70.f);
        this->currentAnimationPLayerPLayed = 3;
    }
}

void SoundSequencer::playPlayerOnPlayerHitSound() {
    if (hasInitBuffers && this->currentAnimationPLayerPLayed != 4) {
        if (this->currentAnimationPLayerPLayed >= 0 && this->currentAnimationPLayerPLayed < MAX_PLAYER_SOUNDS) 
            this->soundPoolPlayer[this->currentAnimationPLayerPLayed].stop();
        
        this->soundPoolPlayer[4].play();
        this->soundPoolPlayer[4].setVolume(70.f);
        this->currentAnimationPLayerPLayed = 4;
    }
}

void SoundSequencer::playPlayerDieSound() {
    if (hasInitBuffers && this->currentAnimationPLayerPLayed != 5) {
        if (this->currentAnimationPLayerPLayed >= 0 && this->currentAnimationPLayerPLayed < MAX_PLAYER_SOUNDS) 
            this->soundPoolPlayer[this->currentAnimationPLayerPLayed].stop();
        
        this->soundPoolPlayer[5].play();
        this->soundPoolPlayer[5].setVolume(70.f);
        this->currentAnimationPLayerPLayed = 5;
    }
}

bool SoundSequencer::initBuffers() {
    hasInitBuffers = true;
    
    for (int i = 0; i < MAX_PLAYER_SOUNDS; ++i) {
        if (this->soundBufferPoolPlayer[i].getSampleCount() > 0) {
            this->soundPoolPlayer[i].setBuffer(this->soundBufferPoolPlayer[i]);
        } else {
            hasInitBuffers = false; 
        }
    }
    return hasInitBuffers;
}

bool SoundSequencer::soundSequencerInit() {
    
   if(loadSoundBuffers()) 
       initBuffers();
    
    return false; 
}