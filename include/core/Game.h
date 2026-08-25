#ifndef GAME_H
#define GAME_H

#include <memory>

// Forward declaration
class BattleSystem;
class InventorySystem;
class QuestSystem;
class MapSystem;
class SaveSystem;
class ShopSystem;

class Game
{
private:
    // ==========================================
    // Game State
    // ==========================================

    bool running;
    bool initialized;

    // ==========================================
    // Game Systems
    // ==========================================

    std::unique_ptr<BattleSystem> battleSystem;
    std::unique_ptr<InventorySystem> inventorySystem;
    std::unique_ptr<QuestSystem> questSystem;
    std::unique_ptr<MapSystem> mapSystem;
    std::unique_ptr<SaveSystem> saveSystem;
    std::unique_ptr<ShopSystem> shopSystem;

private:
    // ==========================================
    // Initialization
    // ==========================================

    void initializeSystems();

    // ==========================================
    // Game Loop
    // ==========================================

    void processInput();
    void update();
    void render();

    // ==========================================
    // Menu
    // ==========================================

    void showMainMenu() const;

    void handleMainMenu();

    void startNewGame();
    void loadGame();
    void saveGame();

    void showMap();
    void openInventory();
    void showQuests();
    void openShop();

    void exitGame();

public:
    // ==========================================
    // Constructor / Destructor
    // ==========================================

    Game();
    ~Game();

    // ==========================================
    // Game Lifecycle
    // ==========================================

    void initialize();
    void run();
    void shutdown();

    // ==========================================
    // State
    // ==========================================

    bool isRunning() const;
};

#endif