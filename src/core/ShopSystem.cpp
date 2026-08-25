#include "core/ShopSystem.h"
#include "entities/Character.h"
#include "utils/ConsoleUtils.h"
#include <algorithm>
#include <string>
#include <vector>

ShopSystem::ShopSystem() {
    catalog = {
        {"Mau Nho (Small Potion)", 50, 30, "Hoi 30 HP ngay lap tuc"},
        {"Mau Lon (Large Potion)", 120, 80, "Hoi 80 HP ngay lap tuc"},
        {"Thuoc Tang Luc", 200, 0, "Tang suc manh tam thoi"}
    };
}

void ShopSystem::openShop(Character& player) {
    while (true) {
        std::vector<std::string> options;
        
        // Tạo danh sách vật phẩm hiển thị trong Menu
        for (const auto& item : catalog) {
            options.push_back(item.name + " - Gia: " + std::to_string(item.price) + " Gold (" + item.description + ")");
        }
        options.push_back("Quay lai Menu chinh");

        // Gọi UI hiển thị menu từ ConsoleUtils
        int choice = ConsoleUtils::showMenuCustom("CUA HANG VAT PHAM (SHOP SYSTEM)", options, player);

        // Thoát nếu chọn tùy chọn cuối cùng hoặc nhấn ESC
        if (choice == -1 || choice == static_cast<int>(options.size() - 1)) {
            break;
        }

        // Xử lý mua vật phẩm
        if (choice >= 0 && choice < static_cast<int>(catalog.size())) {
            const auto& selectedItem = catalog[choice];

            if (player.getGold() >= selectedItem.price) {
                // Trừ tiền người chơi
                player.setGold(player.getGold() - selectedItem.price);

                // Hồi máu nếu vật phẩm có chỉ số hồi phục
                if (selectedItem.healAmount > 0) {
                    int newHP = std::min(player.getMaxHP(), player.getHP() + selectedItem.healAmount);
                    player.setHP(newHP);
                }

                std::string successMsg = "MUA THANH CONG: " + selectedItem.name;
                ConsoleUtils::showMenuCustom(successMsg, {"Tiep tuc mua sam"}, player);
            } else {
                ConsoleUtils::showMenuCustom("LOI: BAN KHONG DU GOLD DE MUA!", {"Thu lai"}, player);
            }
        }
    }
}