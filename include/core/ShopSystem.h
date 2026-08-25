#ifndef SHOPSYSTEM_H
#define SHOPSYSTEM_H

#include <string>
#include <vector>

class Character; // Forward declaration

struct ShopItem {
    std::string name;
    int price;
    int healAmount;
    std::string description;
};

class ShopSystem {
private:
    std::vector<ShopItem> catalog;

public:
    ShopSystem();
    void openShop(Character& player);
};

#endif // SHOPSYSTEM_H