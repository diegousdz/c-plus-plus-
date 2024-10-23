#include "AnimationSequencer.h"

int AnimationSequencer::fillArrayIdleWithSword()
{
    sf::Texture SFMLTexture;
    if (SFMLTexture.loadFromFile("res/textures/Player/idleWithSword/adventurer-idle-2-00.png")) {
        return 0;
    } else {
        spriteArrayIdleWithSword[0].setTexture(SFMLTexture);
        return 4;
    }
}

