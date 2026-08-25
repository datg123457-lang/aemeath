#include "entities/Character.h"
#include <algorithm>

// =========================
// Constructor / Destructor
// =========================

Character::Character(
    int id,
    const std::string& name,
    int maxHP,
    int attack,
    int defense,
    int intelligence,
    int agility
)
    : Entity(id),
      name(name),
      level(1),
      experience(0),
      gold(0),
      maxHP(maxHP),
      hp(maxHP),
      attack(attack),
      defense(defense),
      intelligence(intelligence),
      agility(agility)
{
}
Character::~Character() = default;

// =========================
// Getter
// =========================

const std::string& Character::getName() const
{
    return name;
}

int Character::getLevel() const
{
    return level;
}

int Character::getExperience() const
{
    return experience;
}

int Character::getGold() const
{
    return gold;
}

int Character::getHP() const
{
    return hp;
}

int Character::getMaxHP() const
{
    return maxHP;
}

int Character::getAttack() const
{
    return attack;
}

int Character::getDefense() const
{
    return defense;
}

int Character::getIntelligence() const
{
    return intelligence;
}

int Character::getAgility() const
{
    return agility;
}

// =========================
// Setter
// =========================

void Character::setHP(int hp)
{
    this->hp = std::clamp(hp, 0, maxHP);
}

void Character::setGold(int gold)
{
    this->gold = std::max(0, gold);
}

// =========================
// Combat
// =========================

int Character::calculateAttackDamage() const
{
    return attack;
}

void Character::takeDamage(int damage)
{
    if (damage <= 0)
    {
        return;
    }

    int actualDamage = std::max(0, damage - defense);

    hp -= actualDamage;

    if (hp < 0)
    {
        hp = 0;
    }
}

bool Character::isAlive() const
{
    return hp > 0;
}

void Character::attackTarget(Character& target)
{
    if (!isAlive())
    {
        return;
    }

    int damage = calculateAttackDamage();
    target.takeDamage(damage);
}

// =========================
// Experience / Level
// =========================

void Character::gainExperience(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    experience += amount;

    int requiredExperience = level * 100;

    while (experience >= requiredExperience)
    {
        experience -= requiredExperience;

        levelUp();

        requiredExperience = level * 100;
    }
}

void Character::levelUp()
{
    ++level;

    maxHP += 20;
    hp = maxHP;

    attack += 5;
    defense += 3;
    intelligence += 3;
    agility += 3;
}

// =========================
// Class Type
// =========================

std::string Character::getClassName() const
{
    return "Character";
}