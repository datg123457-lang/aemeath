#include "core/Game.h"

#include <iostream>
#include <memory>

// Các system của game
#include "core/BattleSystem.h"
#include "core/InventorySystem.h"
#include "core/QuestSystem.h"
#include "core/MapSystem.h"
#include "core/SaveSystem.h"
#include "core/ShopSystem.h"

using namespace std;

// ==========================================
// Constructor
// ==========================================

Game::Game()
    : running(false),
      initialized(false),
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

    /*
     * Khởi tạo các system.
     *
     * Lưu ý:
     * Constructor thực tế của từng System
     * phải phù hợp với code của project.
     */

    battleSystem =
        make_unique<BattleSystem>();

    inventorySystem =
        make_unique<InventorySystem>();

    questSystem =
        make_unique<QuestSystem>();

    mapSystem =
        make_unique<MapSystem>();

    saveSystem =
        make_unique<SaveSystem>();

    shopSystem =
        make_unique<ShopSystem>();

    cout << "BattleSystem      [OK]\n";
    cout << "InventorySystem   [OK]\n";
    cout << "QuestSystem       [OK]\n";
    cout << "MapSystem         [OK]\n";
    cout << "SaveSystem        [OK]\n";
    cout << "ShopSystem        [OK]\n";

    cout << "\nAll systems initialized.\n";
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

    cout << "\nGame initialized successfully!\n";
}

// ==========================================
// Main Game Loop
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

    cout << "\nStarting game...\n";

    while (running)
    {
        processInput();
        update();
        render();
    }
}

// ==========================================
// Process Input
// ==========================================

void Game::processInput()
{
    handleMainMenu();
}

// ==========================================
// Update
// ==========================================

void Game::update()
{
    /*
     * Phần này dùng để cập nhật trạng thái game.
     *
     * Ví dụ:
     * - cập nhật nhân vật
     * - cập nhật quest
     * - cập nhật map
     * - cập nhật trạng thái battle
     */
}

// ==========================================
// Render
// ==========================================

void Game::render()
{
    /*
     * Game console hiện tại không cần
     * render liên tục.
     *
     * Nếu sau này làm UI/game engine,
     * phần này có thể dùng để vẽ giao diện.
     */
}

// ==========================================
// Main Menu
// ==========================================

void Game::showMainMenu() const
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "              MAIN MENU\n";
    cout << "=====================================\n";

    cout << "1. New Game\n";
    cout << "2. Load Game\n";
    cout << "3. Map\n";
    cout << "4. Inventory\n";
    cout << "5. Quest\n";
    cout << "6. Shop\n";
    cout << "7. Save Game\n";
    cout << "0. Exit\n";

    cout << "=====================================\n";
}

// ==========================================
// Handle Main Menu
// ==========================================

void Game::handleMainMenu()
{
    showMainMenu();

    int choice;

    cout << "Choose: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            startNewGame();
            break;

        case 2:
            loadGame();
            break;

        case 3:
            showMap();
            break;

        case 4:
            openInventory();
            break;

        case 5:
            showQuests();
            break;

        case 6:
            openShop();
            break;

        case 7:
            saveGame();
            break;

        case 0:
            exitGame();
            break;

        default:
            cout << "Invalid choice!\n";
            break;
    }
}

// ==========================================
// New Game
// ==========================================

void Game::startNewGame()
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "             NEW GAME\n";
    cout << "=====================================\n";

    cout << "Creating new adventure...\n";

    /*
     * Sau này có thể:
     *
     * - tạo Player
     * - tạo Character
     * - reset Inventory
     * - reset Quest
     * - đặt Map hiện tại
     */

    cout << "New game started!\n";
}

// ==========================================
// Load Game
// ==========================================

void Game::loadGame()
{
    cout << "\n";
    cout << "Loading save data...\n";

    /*
     * Sau này:
     *
     * saveSystem->load(...);
     */

    cout << "Load system ready.\n";
}

// ==========================================
// Save Game
// ==========================================

void Game::saveGame()
{
    cout << "\n";
    cout << "Saving game...\n";

    /*
     * Sau này:
     *
     * saveSystem->save(...);
     */

    cout << "Game saved!\n";
}

// ==========================================
// Map
// ==========================================

void Game::showMap()
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "                MAP\n";
    cout << "=====================================\n";

    /*
     * Sau này:
     *
     * mapSystem->showMap();
     */

    cout << "MapSystem is ready.\n";
}

// ==========================================
// Inventory
// ==========================================

void Game::openInventory()
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "             INVENTORY\n";
    cout << "=====================================\n";

    /*
     * Sau này:
     *
     * inventorySystem->open();
     */

    cout << "InventorySystem is ready.\n";
}

// ==========================================
// Quest
// ==========================================

void Game::showQuests()
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "               QUEST\n";
    cout << "=====================================\n";

    /*
     * Sau này:
     *
     * questSystem->showQuests();
     */

    cout << "QuestSystem is ready.\n";
}

// ==========================================
// Shop
// ==========================================

void Game::openShop()
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "                SHOP\n";
    cout << "=====================================\n";

    /*
     * Sau này:
     *
     * shopSystem->open();
     */

    cout << "ShopSystem is ready.\n";
}

// ==========================================
// Exit
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

    /*
     * unique_ptr sẽ tự động giải phóng
     * các System.
     */

    battleSystem.reset();
    inventorySystem.reset();
    questSystem.reset();
    mapSystem.reset();
    saveSystem.reset();
    shopSystem.reset();

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