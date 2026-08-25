#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage : public Character
{
public:
    Mage(
        int id,
        const std::string& name
    );

    ~Mage() override;

    std::string getClassName() const override;

    int calculateAttackDamage() const override;
};

#endif