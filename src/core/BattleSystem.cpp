#include "core/BattleSystem.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
void BattleSystem::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// ==========================================
// Constructor
// ==========================================

BattleSystem::BattleSystem(
    Character& player,
    const vector<Character*>& enemies
)
    : player(player),
      enemies(enemies),
      currentTurn(1),
      playerDefending(false)
{
}

// ==========================================
// Hiển thị trạng thái trận đấu
// ==========================================

void BattleSystem::showBattleStatus() const
{
    cout << "\n=====================================\n";
    cout << "           BATTLE STATUS\n";
    cout << "=====================================\n";

    cout << "\nPLAYER\n";
    cout << "Name   : " << player.getName() << endl;
    cout << "Class  : " << player.getClassName() << endl;
    cout << "Level  : " << player.getLevel() << endl;
    cout << "HP     : "
         << player.getHP()
         << "/"
         << player.getMaxHP()
         << endl;

    cout << "\nENEMIES\n";

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        Character* enemy = enemies[i];

        if (enemy == nullptr)
            continue;

        cout << i + 1 << ". "
             << enemy->getName()
             << " | HP: "
             << enemy->getHP()
             << "/"
             << enemy->getMaxHP();

        if (!enemy->isAlive())
        {
            cout << " [DEAD]";
        }

        cout << endl;
    }

    cout << "=====================================\n";
}

// ==========================================
// Hiển thị hành động
// ==========================================

void BattleSystem::showActions() const
{
    cout << "\n---------- ACTION ----------\n";
    cout << "1. Attack\n";
    cout << "2. Defend\n";
    cout << "3. Skip Turn\n";
    cout << "----------------------------\n";
}

// ==========================================
// Kiểm tra Enemy còn sống
// ==========================================

bool BattleSystem::areEnemiesAlive() const
{
    for (Character* enemy : enemies)
    {
        if (enemy != nullptr && enemy->isAlive())
        {
            return true;
        }
    }

    return false;
}

// ==========================================
// Lấy Enemy còn sống ngẫu nhiên
// ==========================================

Character* BattleSystem::getRandomAliveEnemy()
{
    vector<Character*> aliveEnemies;

    for (Character* enemy : enemies)
    {
        if (enemy != nullptr && enemy->isAlive())
        {
            aliveEnemies.push_back(enemy);
        }
    }

    if (aliveEnemies.empty())
    {
        return nullptr;
    }

    static mt19937 rng(
        static_cast<unsigned int>(time(nullptr))
    );

    uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(aliveEnemies.size()) - 1
    );

    return aliveEnemies[distribution(rng)];
}

// ==========================================
// Player Attack
// ==========================================

void BattleSystem::playerAttack()
{
    Character* target = getRandomAliveEnemy();

    if (target == nullptr)
    {
        cout << "Khong con enemy de tan cong!\n";
        return;
    }

    cout << "\n"
         << player.getName()
         << " attacks "
         << target->getName()
         << "!\n";

    int damage = player.calculateAttackDamage();

    cout << "Raw Damage: "
         << damage
         << endl;

    target->takeDamage(damage);

    cout << target->getName()
         << " HP: "
         << target->getHP()
         << "/"
         << target->getMaxHP()
         << endl;

    if (!target->isAlive())
    {
        cout << "\n>>> "
             << target->getName()
             << " was defeated!\n";
    }
}

// ==========================================
// Player Defend
// ==========================================

void BattleSystem::playerDefend()
{
    playerDefending = true;

    cout << "\n"
         << player.getName()
         << " is defending!\n";

    cout << "Defense will be increased temporarily.\n";
}

// ==========================================
// Player Turn
// ==========================================

void BattleSystem::playerTurn()
{
    playerDefending = false;

    cout << "\n=====================================\n";
    cout << "           PLAYER TURN\n";
    cout << "=====================================\n";

    bool validAction = false;

    while (!validAction)
    {
        showActions();

        int choice;

        cout << "Choose action: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            playerAttack();
            validAction = true;
            break;

        case 2:
            playerDefend();
            validAction = true;
            break;

        case 3:
            cout << "\n"
                 << player.getName()
                 << " skipped the turn.\n";

            validAction = true;
            break;

        default:
            cout << "Invalid action!\n";
            break;
        }
    }
}

// ==========================================
// Enemy Turn
// ==========================================

void BattleSystem::enemyTurn()
{
    cout << "\n=====================================\n";
    cout << "           ENEMY TURN\n";
    cout << "=====================================\n";

    for (Character* enemy : enemies)
    {
        if (enemy == nullptr)
            continue;

        if (!enemy->isAlive())
            continue;

        if (!player.isAlive())
            break;

        cout << "\n"
             << enemy->getName()
             << " attacks "
             << player.getName()
             << "!\n";

        int damage = enemy->calculateAttackDamage();

        // Nếu Player đang phòng thủ
        if (playerDefending)
        {
            damage /= 2;

            cout << "Player is defending!\n";
            cout << "Damage reduced by half.\n";
        }

        player.takeDamage(damage);

        cout << player.getName()
             << " HP: "
             << player.getHP()
             << "/"
             << player.getMaxHP()
             << endl;
    }
}

// ==========================================
// Reward
// ==========================================

void BattleSystem::rewardPlayer()
{
    int rewardExp = 50 * static_cast<int>(enemies.size());

    cout << "\n=====================================\n";
    cout << "          BATTLE REWARD\n";
    cout << "=====================================\n";

    cout << "EXP gained: "
         << rewardExp
         << endl;

    player.gainExperience(rewardExp);

    cout << "Current Level: "
         << player.getLevel()
         << endl;
}

// ==========================================
// Start Battle
// ==========================================

void BattleSystem::startBattle()
{
    currentTurn = 1;

    cout << "\n";
    cout << "=====================================\n";
    cout << "          BATTLE START!\n";
    cout << "=====================================\n";

    cout << player.getName()
         << " enters the battle!\n";

    while (player.isAlive() && areEnemiesAlive())
{
    clearScreen();

    cout << "#####################################\n";
    cout << "              TURN "
         << currentTurn
         << "\n";
    cout << "#####################################\n";

    showBattleStatus();

    // Player turn
    playerTurn();

        // Kiểm tra enemy chết hết chưa
        if (!areEnemiesAlive())
        {
            break;
        }

        // Enemy turn
        enemyTurn();

        // Kiểm tra Player
        if (!player.isAlive())
        {
            break;
        }

        ++currentTurn;
    }

    // ======================================
    // Battle Result
    // ======================================

    cout << "\n";
    cout << "=====================================\n";
    cout << "          BATTLE END\n";
    cout << "=====================================\n";

    if (player.isAlive())
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "          CHÚC MỪNG!\n";
    cout << "      BẠN ĐÃ CHIẾN THẮNG!\n";
    cout << "=====================================\n";

    rewardPlayer();
}
    else
    {
        cout << "\n";
        cout << ">>> DEFEAT! <<<\n";

        cout << player.getName()
             << " has fallen.\n";
    }

    cout << "=====================================\n";
}