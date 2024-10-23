#pragma once
#include <iostream>
#include <fstream>
#include "./../GameEntities/Player.h"

class FileManager
{
public:
    // Save and load player progress
    static bool savePlayerProgress(const std::string& basePath, const std::string& fileName, const Player& player);
    static Player loadPlayerProgress(const std::string& basePath, const std::string& fileName);
};
