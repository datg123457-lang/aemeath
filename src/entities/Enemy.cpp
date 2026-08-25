#include "entities/Enemy.h"

Enemy::Enemy(
    int id,
    const std::string& name,
    EnemyType type,
    int maxHP,
    int attack,
    int defense,
    int intelligence,
    int agility
)
    : Character(
        id,
        name,
        maxHP,
        attack,
        defense,
        intelligence,
        agility
      ),
      type(type)
{
}

Enemy::~Enemy() = default;

EnemyType Enemy::getEnemyType() const
{
    return type;
}

std::string Enemy::getClassName() const
{
    return "Enemy";
}