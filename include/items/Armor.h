#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor : public Item
{
private:
    int defenseBonus;
    std::string armorType;

public:
    Armor(
        const std::string& name,
        const std::string& description,
        int price,
        int defenseBonus,
        const std::string& armorType
    );

    ~Armor() override;

    int getDefenseBonus() const;
    const std::string& getArmorType() const;

    void use(Character& target) override;
    void showInfo() const override;
};

#endif