#include "entities/Mage.h"

Mage::Mage(
    int id,
    const std::string& name
)
    : Character(
        id,
        name,
        100,  // maxHP
        15,   // attack
        8,    // defense
        30,   // intelligence
        12    // agility
    )
{
}

Mage::~Mage() = default;

std::string Mage::getClassName() const
{
    return "Mage";
}

int Mage::calculateAttackDamage() const
{
    return attack + intelligence;
}