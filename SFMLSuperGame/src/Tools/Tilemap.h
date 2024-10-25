#pragma once

struct timemapInstance
{
    
};

class Tilemap
{
public:
    int mapWidth;
    int mapHeight;

    ~Tilemap();
    void clearTilemap();
    
    void createTilemapShort();
    void createTilemapMedium();
    void createTilemapLong();

    void InstantiateATilemapByType(int type);
    int* genericHorizontalArray[600];
    
};
