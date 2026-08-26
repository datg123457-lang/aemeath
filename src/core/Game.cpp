#include "core/Game.h"

#include <iostream>
#include <memory>
#include <string>

// ==========================================
// Game Systems
// ==========================================

#include "core/BattleSystem.h"
#include "core/InventorySystem.h"
#include "core/QuestSystem.h"
#include "core/MapSystem.h"
#include "core/SaveSystem.h"
#include "core/ShopSystem.h"

// ==========================================
// Entities
// ==========================================

#include "entities/Character.h"
#include "entities/Warrior.h"
#include "entities/Mage.h"
#include "entities/Archer.h"

using namespace std;

// ==========================================
// Constructor
// ==========================================

Game::Game()
    : running(false),
      initialized(false),
      player(nullptr),
      battleSystem(nullptr),
      inventorySystem(nullptr),
      questSystem(nullptr),
      mapSystem(nullptr),
      saveSystem(nullptr),
      shopSystem(nullptr)
{
}

// ==========================================
// Destructor
// ==========================================

Game::~Game()
{
    shutdown();
}

// ==========================================
// Initialize Systems
// ==========================================

void Game::initializeSystems()
{
    cout << "\n";
    cout << "Initializing game systems...\n";

    // ------------------------------------------
    // Inventory
    // ------------------------------------------

    inventorySystem =
        make_unique<InventorySystem>();

    // ------------------------------------------
    // Quest
    // ------------------------------------------

    questSystem =
        make_unique<QuestSystem>();

    // ------------------------------------------
    // Map
    // ------------------------------------------

    mapSystem =
        make_unique<Map>();

    // ------------------------------------------
    // Save / Load
    // ------------------------------------------

    saveSystem =
        make_unique<SaveSystem>();

    // ------------------------------------------
    // Shop
    // ------------------------------------------

    shopSystem =
        make_unique<ShopSystem>();

    /*
     * BattleSystem KHÔNG được tạo ở đây.
     *
     * BattleSystem cần:
     *
     * Character& player
     * vector<Character*> enemies
     *
     * Hai dữ liệu này chỉ tồn tại khi
     * một trận chiến thực sự bắt đầu.
     */

    battleSystem.reset();

    cout << "InventorySystem   [OK]\n";
    cout << "QuestSystem       [OK]\n";
    cout << "MapSystem         [OK]\n";
    cout << "SaveSystem        [OK]\n";
    cout << "ShopSystem        [OK]\n";

    cout << "\n";
    cout << "All systems initialized.\n";
}

// ==========================================
// Initialize Game
// ==========================================

void Game::initialize()
{
    if (initialized)
    {
        return;
    }

    cout << "\n";
    cout << "=====================================\n";
    cout << "           AEMEATH RPG\n";
    cout << "=====================================\n";

    initializeSystems();

    initialized = true;
    running = true;

    cout << "\n";
    cout << "Game initialized successfully!\n";
}

// ==========================================
// Run
// ==========================================

void Game::run()
{
    if (!initialized)
    {
        initialize();
    }

    if (!running)
    {
        return;
    }

    /*
     * Menu chính hiện tại nằm trong main.cpp.
     *
     * Vì vậy Game không tạo thêm một menu
     * thứ hai ở đây.
     *
     * main.cpp sẽ gọi trực tiếp:
     *
     * startNewGame()
     * showMap()
     * showQuests()
     * loadGame()
     * ...
     */
}

// ==========================================
// Start New Game
// ==========================================

void Game::startNewGame(
    int classChoice,
    const string& name
)
{
    // ------------------------------------------
    // Validate name
    // ------------------------------------------

    if (name.empty())
    {
        cout << "\n";
        cout << "Ten nhan vat khong duoc de trong!\n";
        return;
    }

    // ------------------------------------------
    // Create Character
    // ------------------------------------------

    switch (classChoice)
    {
        case 0:
        {
            player =
                make_unique<Warrior>(
                    1,
                    name
                );

            break;
        }

        case 1:
        {
            player =
                make_unique<Mage>(
                    1,
                    name
                );

            break;
        }

        case 2:
        {
            player =
                make_unique<Archer>(
                    1,
                    name
                );

            break;
        }

        default:
        {
            cout << "\n";
            cout << "Class khong hop le!\n";
            return;
        }
    }

    // ------------------------------------------
    // Starting Gold
    // ------------------------------------------

    player->setGold(100);

    // ------------------------------------------
    // Result
    // ------------------------------------------

    cout << "\n";
    cout << "=====================================\n";
    cout << "          CHARACTER CREATED\n";
    cout << "=====================================\n";

    cout << "Name  : "
         << player->getName()
         << "\n";

    cout << "Class : "
         << player->getClassName()
         << "\n";

    cout << "Level : "
         << player->getLevel()
         << "\n";

    cout << "HP    : "
         << player->getHP()
         << "/"
         << player->getMaxHP()
         << "\n";

    cout << "Attack: "
         << player->getAttack()
         << "\n";

    cout << "Defense: "
         << player->getDefense()
         << "\n";

    cout << "Gold  : "
         << player->getGold()
         << "\n";

    cout << "=====================================\n";
}

// ==========================================
// Load Game
// ==========================================

bool Game::loadGame()
{
    if (!player)
    {
        cout << "\n";
        cout << "Chua co nhan vat de load game!\n";
        return false;
    }

    if (!saveSystem)
    {
        cout << "\n";
        cout << "SaveSystem chua duoc khoi tao!\n";
        return false;
    }

    cout << "\n";
    cout << "Loading save data...\n";

    bool result =
        saveSystem->loadGame(*player);

    if (result)
    {
        cout << "Load game thanh cong!\n";
    }
    else
    {
        cout << "Load game that bai!\n";
    }

    return result;
}

// ==========================================
// Save Game
// ==========================================

bool Game::saveGame()
{
    if (!player)
    {
        cout << "\n";
        cout << "Chua co nhan vat de save game!\n";
        return false;
    }

    if (!saveSystem)
    {
        cout << "\n";
        cout << "SaveSystem chua duoc khoi tao!\n";
        return false;
    }

    cout << "\n";
    cout << "Saving game...\n";

    bool result =
        saveSystem->saveGame(*player);

    if (result)
    {
        cout << "Game saved successfully!\n";
    }
    else
    {
        cout << "Save game that bai!\n";
    }

    return result;
}

// ==========================================
// Show Map
// ==========================================

void Game::showMap()
{
    if (!mapSystem)
    {
        cout << "\n";
        cout << "MapSystem chua duoc khoi tao!\n";
        return;
    }

    cout << "\n";
    cout << "=====================================\n";
    cout << "                MAP\n";
    cout << "=====================================\n";

    mapSystem->showMap();
}

// ==========================================
// Open Inventory
// ==========================================

void Game::openInventory()
{
    if (!inventorySystem)
    {
        cout << "\n";
        cout << "InventorySystem chua duoc khoi tao!\n";
        return;
    }

    cout << "\n";
    cout << "=====================================\n";
    cout << "             INVENTORY\n";
    cout << "=====================================\n";

    inventorySystem->showInventory();
}

// ==========================================
// Show Quests
// ==========================================

void Game::showQuests()
{
    if (!player)
    {
        cout << "\n";
        cout << "Hay tao nhan vat truoc!\n";
        return;
    }

    if (!questSystem)
    {
        cout << "\n";
        cout << "QuestSystem chua duoc khoi tao!\n";
        return;
    }

    cout << "\n";
    cout << "=====================================\n";
    cout << "             QUEST JOURNAL\n";
    cout << "=====================================\n";

    questSystem->openQuestLog(*player);
}

// ==========================================
// Open Shop
// ==========================================

void Game::openShop()
{
    if (!player)
    {
        cout << "\n";
        cout << "Hay tao nhan vat truoc!\n";
        return;
    }

    if (!shopSystem)
    {
        cout << "\n";
        cout << "ShopSystem chua duoc khoi tao!\n";
        return;
    }

    cout << "\n";
    cout << "=====================================\n";
    cout << "                SHOP\n";
    cout << "=====================================\n";

    shopSystem->openShop(*player);
}

// ==========================================
// Has Player
// ==========================================

bool Game::hasPlayer() const
{
    return player != nullptr;
}

// ==========================================
// Exit Game
// ==========================================

void Game::exitGame()
{
    cout << "\n";
    cout << "Exiting Aemeath...\n";

    running = false;
}

// ==========================================
// Shutdown
// ==========================================

void Game::shutdown()
{
    if (!initialized)
    {
        return;
    }

    cout << "\n";
    cout << "Shutting down game systems...\n";

    // ------------------------------------------
    // Destroy Battle
    // ------------------------------------------

    battleSystem.reset();

    // ------------------------------------------
    // Destroy Systems
    // ------------------------------------------

    inventorySystem.reset();
    questSystem.reset();
    mapSystem.reset();
    saveSystem.reset();
    shopSystem.reset();

    // ------------------------------------------
    // Destroy Player
    // ------------------------------------------

    player.reset();

    // ------------------------------------------
    // Reset State
    // ------------------------------------------

    running = false;
    initialized = false;

    cout << "Game shutdown complete.\n";
}

// ==========================================
// Is Running
// ==========================================

bool Game::isRunning() const
{
    return running;
}