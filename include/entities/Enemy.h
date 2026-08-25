#ifndef ENEMY_H
#define ENEMY_H

#include "entities/Character.h"

enum class EnemyType
{
    NORMAL,
    ELITE,
    BOSS
};

class Enemy : public Character
{
private:
    EnemyType type;

public:
    Enemy(
        int id,
        const std::string& name,
        EnemyType type,
        int maxHP,
        int attack,
        int defense,
        int intelligence,
        int agility
    );

    ~Enemy() override;

    EnemyType getEnemyType() const;

    std::string getClassName() const override;
};

#endif