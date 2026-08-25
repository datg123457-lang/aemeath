#include "entities/Warrior.h"

Warrior::Warrior(
    int id,
    const std::string& name
)
    : Character(
        id,
        name,
        150,  // maxHP
        25,   // attack
        20,   // defense
        5,    // intelligence
        10    // agility
    )
{
}

Warrior::~Warrior() = default;

std::string Warrior::getClassName() const
{
    return "Warrior";
}

int Warrior::calculateAttackDamage() const
{
    return attack;
}