#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <string>

class Character; // Forward declaration

class SaveSystem {
private:
    std::string saveFilePath;

public:
    // Trỏ mặc định vào thư mục data/saves/ để khớp với cấu trúc thư mục BTL
    SaveSystem(const std::string& filePath = "data/saves/savegame.txt");

    bool saveGame(const Character& player);
    bool loadGame(Character& player);
    void openSaveLoadMenu(Character& player);
};

#endif // SAVESYSTEM_H