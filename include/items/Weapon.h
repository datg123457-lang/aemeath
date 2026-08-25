#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item
{
private:
    int damage;
    std::string weaponType;

public:
    Weapon(
        const std::string& name,
        const std::string& description,
        int price,
        int damage,
        const std::string& weaponType
    );

    ~Weapon() override;

    int getDamage() const;
    const std::string& getWeaponType() const;

    void use(Character& target) override;
    void showInfo() const override;
};

#endif