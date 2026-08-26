#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>

class Character;
class BattleSystem;
class InventorySystem;
class QuestSystem;
class Map;
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
    // Player
    // ==========================================

    std::unique_ptr<Character> player;

    // ==========================================
    // Game Systems
    // ==========================================

    std::unique_ptr<BattleSystem> battleSystem;
    std::unique_ptr<InventorySystem> inventorySystem;
    std::unique_ptr<QuestSystem> questSystem;
    std::unique_ptr<Map> mapSystem;
    std::unique_ptr<SaveSystem> saveSystem;
    std::unique_ptr<ShopSystem> shopSystem;

private:
    // ==========================================
    // Initialization
    // ==========================================

    void initializeSystems();

    // ==========================================
    // Exit
    // ==========================================

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
    // Main Menu Actions
    // ==========================================

    void startNewGame(int classChoice, const std::string& name);

    bool loadGame();
    bool saveGame();

    void showMap();
    void openInventory();
    void showQuests();
    void openShop();

    bool hasPlayer() const;

    // ==========================================
    // State
    // ==========================================

    bool isRunning() const;
};

#endif