#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "entities/Character.h"
#include <vector>

class BattleSystem
{
private:
    Character& player;
    std::vector<Character*> enemies;

    int currentTurn;
    bool playerDefending;

private:
    void showBattleStatus() const;
    void showActions() const;

    void playerTurn();
    void enemyTurn();

    void playerAttack();
    void playerDefend();

    Character* getRandomAliveEnemy();
    bool areEnemiesAlive() const;

    void rewardPlayer();

public:
    BattleSystem(
        Character& player,
        const std::vector<Character*>& enemies
    );

    void startBattle();
};

#endif