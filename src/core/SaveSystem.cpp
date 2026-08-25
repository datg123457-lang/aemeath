#include "core/SaveSystem.h"
#include "entities/Character.h"
#include "utils/ConsoleUtils.h"
#include <fstream>
#include <string>
#include <vector>

SaveSystem::SaveSystem(const std::string& filePath) : saveFilePath(filePath) {}

bool SaveSystem::saveGame(const Character& player) {
    std::ofstream outFile(saveFilePath);
    if (outFile.is_open()) {
        outFile << player.getLevel() << "\n"
                << player.getExperience() << "\n"
                << player.getGold() << "\n"
                << player.getHP() << "\n"
                << player.getMaxHP() << "\n";
        outFile.close();
        return true;
    }
    return false;
}

bool SaveSystem::loadGame(Character& player) {
    std::ifstream inFile(saveFilePath);
    if (inFile.is_open()) {
        int level, experience, gold, hp, maxHP;
        inFile >> level >> experience >> gold >> hp >> maxHP;

        player.setGold(gold);
        player.setHP(hp);
        player.gainExperience(experience);

        inFile.close();
        return true;
    }
    return false;
}

void SaveSystem::openSaveLoadMenu(Character& player) {
    while (true) {
        std::vector<std::string> options = {
            "1. Luu trang thai game (Save Game)",
            "2. Tai du lieu game khoi phuc (Load Game)",
            "Quay lai Menu chinh"
        };

        int choice = ConsoleUtils::showMenuCustom("QUAN LY DU LIEU (SAVE / LOAD SYSTEM)", options, player);

        if (choice == -1 || choice == static_cast<int>(options.size() - 1)) {
            break;
        }

        if (choice == 0) {
            if (saveGame(player)) {
                ConsoleUtils::showMenuCustom("Luu du lieu game thanh cong!", {"Xac nhan"}, player);
            } else {
                ConsoleUtils::showMenuCustom("LOI: Khong the tao file save!", {"Thu lai"}, player);
            }
        } else if (choice == 1) {
            if (loadGame(player)) {
                ConsoleUtils::showMenuCustom("Tai du lieu game thanh cong!", {"Vao Game"}, player);
            } else {
                ConsoleUtils::showMenuCustom("LOI: Khong tim thay file save game!", {"Quay lai"}, player);
            }
        }
    }
}