#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct PlayerConfiguration
{
    
    int playerCurrentLife = 1;
    
    int playerSavedLife = 0;

    // Main Character Name
    std::string playerName = "Player1";

    // World Dimension Representation
    float playerPositionX = 0;
    float playerPositionY = 0;

    // Player Dimension Representation 
    int playerWidth = 0;
    int playerHeight = 0;

    // Top Panel Stats
    float playerHealth = 100;
    float playerTiredness = 0;
    float playerSpeed = 0;
    
    //struct representing life cycle of player
    //Note: Structs allways have a ; at the end of the scope
    enum PlayerState { alive, recovering, hurt, dying, died };
    enum PlayerActions { idle, walking, jumping, attacking };
};

class StoneAndFrostWorld
{
    
private:
    int screenWidth = 0;
    int screenHeight = 0;

    int bottomGamePanel = 256;
    int gameArea = screenHeight - bottomGamePanel;
    
     std::string deviceID = "host";
  

    std::string currentTimeStamp = ""; 
    std::string savedTimeStamp = "";

   // bool isNetworkedEnabled = false;
  //  int checkPointIndex = 0;

protected:
    
public:

    StoneAndFrostWorld(int width, int height);

    int cameraPositionX = 0;
    int cameraPositionY = 0;

    int cameraZoom = 64;
    int cameraTargetPosition = 0;
    bool isCameraAttachedToPlayer = false;
    
    bool isGameStarted;
};
