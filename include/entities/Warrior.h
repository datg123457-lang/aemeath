#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Warrior : public Character
{
public:
    Warrior(
        int id,
        const std::string& name
    );

    ~Warrior() override;

    std::string getClassName() const override;

    int calculateAttackDamage() const override;
};

#endif