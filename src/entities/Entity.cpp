#include "entities/Enemy.h"

#include <algorithm>

// ==========================================
// Constructor
// ==========================================

Enemy::Enemy(
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
      type(type),
      areaId(areaId),
      experienceReward(experienceReward),
      goldReward(goldReward)
{
}

// ==========================================
// Destructor
// ==========================================

Enemy::~Enemy() = default;

// ==========================================
// Getter
// ==========================================

EnemyType Enemy::getEnemyType() const
{
    return type;
}

int Enemy::getAreaId() const
{
    return areaId;
}

int Enemy::getExperienceReward() const
{
    return experienceReward;
}

int Enemy::getGoldReward() const
{
    return goldReward;
}

std::string Enemy::getClassName() const
{
    return "Enemy";
}

// ============================================================
// 1. DARK FOREST
// ============================================================

// Shadow Wolf
Enemy Enemy::createShadowWolf()
{
    return Enemy(
        101,
        "Shadow Wolf",
        EnemyType::NORMAL,
        1,
        80,
        15,
        5,
        3,
        15,
        30,
        20
    );
}

// Forest Warden
Enemy Enemy::createForestWarden()
{
    return Enemy(
        102,
        "Forest Warden",
        EnemyType::ELITE,
        1,
        180,
        28,
        12,
        8,
        12,
        100,
        60
    );
}

// Elder Treant
Enemy Enemy::createElderTreant()
{
    return Enemy(
        103,
        "Elder Treant",
        EnemyType::BOSS,
        1,
        400,
        45,
        20,
        15,
        8,
        250,
        150
    );
}

// ============================================================
// 2. ANCIENT RUINS
// ============================================================

// Ruins Guardian
Enemy Enemy::createRuinsGuardian()
{
    return Enemy(
        201,
        "Ruins Guardian",
        EnemyType::NORMAL,
        2,
        150,
        25,
        15,
        5,
        8,
        50,
        35
    );
}

// Ancient Golem
Enemy Enemy::createAncientGolem()
{
    return Enemy(
        202,
        "Ancient Golem",
        EnemyType::ELITE,
        2,
        300,
        42,
        30,
        10,
        4,
        150,
        90
    );
}

// Ruins Overlord
Enemy Enemy::createRuinsOverlord()
{
    return Enemy(
        203,
        "Ruins Overlord",
        EnemyType::BOSS,
        2,
        600,
        60,
        35,
        25,
        10,
        400,
        250
    );
}

// ============================================================
// 3. FROZEN PEAK
// ============================================================

// Frost Wolf
Enemy Enemy::createFrostWolf()
{
    return Enemy(
        301,
        "Frost Wolf",
        EnemyType::NORMAL,
        3,
        230,
        38,
        18,
        8,
        20,
        70,
        50
    );
}

// Ice Revenant
Enemy Enemy::createIceRevenant()
{
    return Enemy(
        302,
        "Ice Revenant",
        EnemyType::ELITE,
        3,
        420,
        55,
        28,
        20,
        15,
        200,
        120
    );
}

// Frost Dragon
Enemy Enemy::createFrostDragon()
{
    return Enemy(
        303,
        "Frost Dragon",
        EnemyType::BOSS,
        3,
        850,
        80,
        45,
        40,
        18,
        550,
        350
    );
}

// ============================================================
// 4. SHADOW CASTLE
// ============================================================

// Shadow Knight
Enemy Enemy::createShadowKnight()
{
    return Enemy(
        401,
        "Shadow Knight",
        EnemyType::NORMAL,
        4,
        350,
        55,
        30,
        15,
        18,
        100,
        70
    );
}

// Dark Paladin
Enemy Enemy::createDarkPaladin()
{
    return Enemy(
        402,
        "Dark Paladin",
        EnemyType::ELITE,
        4,
        600,
        75,
        45,
        30,
        20,
        300,
        180
    );
}

// Shadow King
Enemy Enemy::createShadowKing()
{
    return Enemy(
        403,
        "Shadow King",
        EnemyType::BOSS,
        4,
        1200,
        110,
        60,
        55,
        25,
        800,
        500
    );
}

// ============================================================
// 5. DEMON REALM
// ============================================================

// Lesser Demon
Enemy Enemy::createLesserDemon()
{
    return Enemy(
        501,
        "Lesser Demon",
        EnemyType::NORMAL,
        5,
        500,
        80,
        40,
        30,
        25,
        150,
        100
    );
}

// Demon General
Enemy Enemy::createDemonGeneral()
{
    return Enemy(
        502,
        "Demon General",
        EnemyType::ELITE,
        5,
        900,
        115,
        65,
        55,
        30,
        450,
        300
    );
}

// Demon Lord
Enemy Enemy::createDemonLord()
{
    return Enemy(
        503,
        "Demon Lord",
        EnemyType::BOSS,
        5,
        1800,
        160,
        85,
        100,
        35,
        1200,
        800
    );
}