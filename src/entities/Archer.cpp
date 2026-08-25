#include "entities/Archer.h"

Archer::Archer(
    int id,
    const std::string& name
)
    : Character(
        id,
        name,
        120,  // maxHP
        22,   // attack
        12,   // defense
        10,   // intelligence
        25    // agility
    )
{
}

Archer::~Archer() = default;

std::string Archer::getClassName() const
{
    return "Archer";
}

int Archer::calculateAttackDamage() const
{
    return attack + (agility / 2);
}