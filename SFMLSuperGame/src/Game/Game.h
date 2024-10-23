#pragma once
#include "../GameEntities/Player.h"

class Game
{
public:
    
    Game(Player user, int nOfEnemies);  // Constructor with parameters
 //   Game();

    void NewGame();
    void LoadGame();

    void simulate();
    void createEnemiesLevelOne();
}
;
