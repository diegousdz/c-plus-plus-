    #pragma once
    #include "../GameEntities/Player.h"

    class Game
    {
    public:
        
        Game();  // Constructor with parameters

        void init(sf::RenderWindow& window, Player user);
        void updateBackgroundPosition();
        void update(float deltaTime, Player player);
        void draw(sf::RenderWindow& window, Player user);
        
        void NewGame();
        void LoadGame();
        void createEnemiesLevelOne();

    private:
        sf::View camera;
        sf::Sprite background;
        sf::Vector2f worldOffset;
    };
