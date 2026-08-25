#ifndef ARCHER_H
#define ARCHER_H

#include "Character.h"

class Archer : public Character
{
public:
    Archer(
        int id,
        const std::string& name
    );

    ~Archer() override;

    std::string getClassName() const override;

    int calculateAttackDamage() const override;
};

#endif