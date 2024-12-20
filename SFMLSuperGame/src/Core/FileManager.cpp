﻿#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <string>

Player FileManager::loadPlayerProgress(const std::string& basePath, const std::string& fileName) {

    std::string filePath = basePath + "/" + fileName + ".dat";
    std::ifstream inFile(filePath);
    
    Player loadedPlayer;

    if (inFile.is_open()) {

        std::getline(inFile, loadedPlayer.name);
        inFile >> loadedPlayer.life;
        inFile >> loadedPlayer.health;
        inFile >> loadedPlayer.energy;
        
        float posX, posY;
        inFile >> posX >> posY;
        loadedPlayer.setPlayerPosition(sf::Vector2f(posX, posY));

        inFile >> loadedPlayer.playerInventory.potionRedIndex
               >> loadedPlayer.playerInventory.potionGreenIndex
               >> loadedPlayer.playerInventory.potionBlueIndex
               >> loadedPlayer.playerInventory.weaponIndex
               >> loadedPlayer.playerInventory.crowdIndex;

        inFile.close();
        std::cout << "Game progress loaded from " << filePath << std::endl;
    } else {
        std::cerr << "Failed to open file for loading: " << filePath << std::endl;
    }

    return loadedPlayer;
}


bool FileManager::savePlayerProgress(const std::string& basePath, const std::string& fileName, const Player& player) {
    
    std::string filePath = basePath + "/" + fileName + ".dat";
    std::ofstream outFile(filePath);

    if (outFile.is_open()) {

        outFile << player.name << "\n";
        outFile << player.life << "\n";
        outFile << player.health << "\n";
        outFile << player.energy << "\n";
        
        outFile << player.shape.getPosition().x << " " << player.shape.getPosition().y << "\n";
        
        outFile << player.playerInventory.potionRedIndex << " "
                << player.playerInventory.potionGreenIndex << " "
                << player.playerInventory.potionBlueIndex << " "
                << player.playerInventory.weaponIndex << " "
                << player.playerInventory.crowdIndex << "\n";

        outFile.close();
        std::cout << "Game progress saved to " << filePath << std::endl;
        return true;
    } else {
        std::cerr << "Failed to open file for saving: " << filePath << std::endl;
        return false;
    }
}


