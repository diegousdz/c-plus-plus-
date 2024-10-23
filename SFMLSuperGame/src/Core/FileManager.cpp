#include "FileManager.h"
#include <string>

/* teacher way
void FileManager::createNewOuputFile(std::string basePath, string nameFile, string data)
{
    string finalPath = basePath + "/" + nameFile + ".dat";
    ofstream newFile(finalPath);
    if(newFile.is_open())
        newFile << data << endl;
    newFile.close();
}

void FileManager::createNewInputFile(string basePath, string nameFile)
{
    ifstream newFile;
    string finalPath = basePath + "/" + nameFile + ".dat";
    string line;
    newFile.open(finalPath);
    while(std::getline(newFile, line))
    {
        cout << line << endl;
    }
    newFile.close();
}
*/


Player FileManager::loadPlayerProgress(const std::string& basePath, const std::string& fileName)
{
    std::string filePath = basePath + "/" + fileName + ".dat";
    std::ifstream inFile(filePath);
    Player loadedPlayer;

    if (inFile.is_open()) {
        // Read player details
        std::getline(inFile, loadedPlayer.name);
        inFile >> loadedPlayer.life;
        inFile >> loadedPlayer.health;
        inFile >> loadedPlayer.energy;

        // Read inventory details
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

bool FileManager::savePlayerProgress(const std::string& basePath, const std::string& fileName, const Player& player)
{
    std::string filePath = basePath + "/" + fileName + ".dat";
    std::ofstream outFile(filePath);

    if (outFile.is_open()) {
        // Write player details
        outFile << player.name << "\n";
        outFile << player.life << "\n";
        outFile << player.health << "\n";
        outFile << player.energy << "\n";
        
        // Write inventory details
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
