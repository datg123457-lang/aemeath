#ifndef ENEMY_H
#define ENEMY_H

#include "entities/Character.h"

enum class EnemyType {
    NORMAL,
    ELITE,
    BOSS
};

class Enemy : public Character {
private:
    EnemyType type;

public:
    // Khai báo constructor khớp chuẩn các tham số
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

    virtual ~Enemy();

    EnemyType getEnemyType() const;
    std::string getClassName() const override;
};

#endif // ENEMY_H