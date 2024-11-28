#pragma once
#include "./../GameEntities/Player.h"

class FileManager {
public:
    static bool savePlayerProgress(const std::string& basePath, const std::string& fileName, const Player& player);
    static Player loadPlayerProgress(const std::string& basePath, const std::string& fileName);
};
