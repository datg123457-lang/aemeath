#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item
{
private:
    int restoreAmount;
    std::string potionType; // "HP" hoac "MP"

public:
    Potion(
        const std::string& name,
        const std::string& description,
        int price,
        int restoreAmount,
        const std::string& potionType
    );

    ~Potion() override;

    int getRestoreAmount() const;
    const std::string& getPotionType() const;

    void use(Character& target) override;
    void showInfo() const override;
};

#endif