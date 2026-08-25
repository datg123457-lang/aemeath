#ifndef ENEMY_H
#define ENEMY_H

#include "entities/Character.h"
#include <vector>
#include <string>

// ==========================================
// Loại Enemy
// ==========================================

enum class EnemyType
{
    NORMAL,
    ELITE,
    BOSS
};

// ==========================================
// Dữ liệu Enemy
// ==========================================

struct EnemyData
{
    int id;
    std::string name;

    EnemyType type;

    int areaId;
    std::string areaName;

    int level;

    int maxHP;
    int attack;
    int defense;
    int intelligence;
    int agility;

    int experienceReward;
    int goldReward;
};

// ==========================================
// Enemy
// ==========================================

class Enemy : public Character
{
private:
    EnemyType type;
    int areaId;
    int experienceReward;
    int goldReward;

public:

    Enemy(
        int id,
        const std::string& name,
        EnemyType type,
        int areaId,
        int maxHP,
        int attack,
        int defense,
        int intelligence,
        int agility,
        int experienceReward,
        int goldReward
    );

    ~Enemy() override;

    EnemyType getEnemyType() const;

    int getAreaId() const;

    int getExperienceReward() const;

    int getGoldReward() const;

    std::string getClassName() const override;

    // ======================================
    // 15 Enemy
    // ======================================

    static Enemy createShadowWolf();
    static Enemy createForestWarden();
    static Enemy createElderTreant();

    static Enemy createRuinsGuardian();
    static Enemy createAncientGolem();
    static Enemy createRuinsOverlord();

    static Enemy createFrostWolf();
    static Enemy createIceRevenant();
    static Enemy createFrostDragon();

    static Enemy createShadowKnight();
    static Enemy createDarkPaladin();
    static Enemy createShadowKing();

    static Enemy createLesserDemon();
    static Enemy createDemonGeneral();
    static Enemy createDemonLord();

    // ======================================
    // Lấy toàn bộ 15 Enemy
    // ======================================

    static std::vector<EnemyData> getEnemyDatabase();

    static std::vector<EnemyData> getEnemiesByArea(
        int areaId
    );

    static std::vector<EnemyData> getEnemiesByType(
        EnemyType type
    );
};

#endif