#include "Tilemap.h"

void Tilemap::clearTilemap()
{
    for (int row = 0; row < 600; row++)
    {
        if (genericHorizontalArray[row] != nullptr)
        {
            delete[] genericHorizontalArray[row];  // Free memory for each row
            genericHorizontalArray[row] = nullptr;  // Set pointer to nullptr after deletion
        }
    }
}

void Tilemap::createTilemapShort()
{
    for (int row = 0; row < 600; row++)
    {
        // Create a separate array for each row
        genericHorizontalArray[row] = new int[1800];  // Dynamically allocated

        // Initialize the array with 0
        for (int i = 0; i < 1800; i++)
        {
            genericHorizontalArray[row][i] = 0;
        }
    }
}

void Tilemap::createTilemapMedium()
{
    for (int row = 0; row < 600; row++)
    {
        genericHorizontalArray[row] = new int[2400];  // Dynamically allocated

        for (int i = 0; i < 2400; i++)
        {
            genericHorizontalArray[row][i] = 0;
        }
    }
}

void Tilemap::createTilemapLong()
{
    for (int row = 0; row < 600; row++)
    {
        genericHorizontalArray[row] = new int[3600];  // Dynamically allocated

        for (int i = 0; i < 3600; i++)
        {
            genericHorizontalArray[row][i] = 0;
        }
    }
}

void Tilemap::InstantiateATilemapByType(int type)
{
    if (type == 1)
    {
        createTilemapShort();
    } else if ( type == 2)
    {
        createTilemapMedium();
    } else
    {
        createTilemapLong();
    }
}

Tilemap::~Tilemap()
{
    clearTilemap();
}



