#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include <string>

class Character : public Entity
{
protected:
    std::string name;

    int level;
    int experience;
    int gold;

    int maxHP;
    int hp;

    int attack;
    int defense;
    int intelligence;
    int agility;

public:
    Character(
        int id,
        const std::string& name,
        int maxHP,
        int attack,
        int defense,
        int intelligence,
        int agility
    );

    virtual ~Character();

    const std::string& getName() const;

    int getLevel() const;
    int getExperience() const;
    int getGold() const;

    int getHP() const;
    int getMaxHP() const;

    int getAttack() const;
    int getDefense() const;
    int getIntelligence() const;
    int getAgility() const;

    void setHP(int hp);
    void setGold(int gold);

    virtual int calculateAttackDamage() const;
    virtual void takeDamage(int damage);
    virtual bool isAlive() const;

    virtual void gainExperience(int amount);
    virtual void levelUp();

    virtual void attackTarget(Character& target);

    virtual std::string getClassName() const = 0;
};

#endif