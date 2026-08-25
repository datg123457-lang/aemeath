#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <string>

class Character; // Forward declaration

class SaveSystem {
private:
    std::string saveFilePath;

public:
    SaveSystem(const std::string& filePath = "savegame.txt");

    bool saveGame(const Character& player);
    bool loadGame(Character& player);
    void openSaveLoadMenu(Character& player);
};

#endif // SAVESYSTEM_H