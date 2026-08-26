#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "core/Game.h"
#include "core/MapSystem.h"
#include "core/BattleSystem.h"
#include "entities/Character.h"
#include "entities/Enemy.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <windows.h>
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_ENTER 13
    #define KEY_ESC 27

    // 1. Phóng to cửa sổ CMD thành Maximize
    void setFullscreen() {
        HWND hwnd = GetConsoleWindow();
        if (hwnd == NULL) return;
        ShowWindow(hwnd, SW_MAXIMIZE);
    }

    // 2. Bật / Ẩn con trỏ nhấp nháy trên Console
    void showCursor(bool show) {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = show ? TRUE : FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
    }

    // 3. Lấy kích thước thực tế của màn hình CMD
    void getConsoleSize(int& width, int& height) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #define KEY_UP 65
    #define KEY_DOWN 66
    #define KEY_ENTER 10
    #define KEY_ESC 27

    void setFullscreen() { std::cout << "\e[8;50;120t"; }
    void showCursor(bool show) { std::cout << (show ? "\e[?25h" : "\e[?25l"); }

    void getConsoleSize(int& width, int& height) {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        width = w.ws_col;
        height = w.ws_row;
    }

    int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        if (ch == 27) {
            if (std::cin.peek() == '[') {
                getchar();
                ch = getchar();
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

// Mã màu ANSI Escape Code
#define COLOR_RESET     "\033[0m"
#define COLOR_TITLE     "\033[1;36m"
#define COLOR_MENU_TEXT "\033[1;33m"
#define COLOR_SELECT    "\033[1;32m"
#define COLOR_INFO      "\033[0;35m"
#define COLOR_BORDER    "\033[1;34m"

// Tính số ký tự Unicode thực tế (Bỏ qua các byte phụ UTF-8 tiếng Việt)
size_t getDisplayLength(const std::string& str) {
    size_t len = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if ((str[i] & 0xC0) != 0x80) len++;
    }
    return len;
}

// In văn bản căn giữa theo chiều ngang
void printCentered(const std::string& text, int consoleWidth, const std::string& color = "") {
    size_t visibleLength = getDisplayLength(text);
    int padding = (consoleWidth - static_cast<int>(visibleLength)) / 2;
    if (padding < 0) padding = 0;

    std::cout << std::string(padding, ' ');
    if (!color.empty()) std::cout << color;
    std::cout << text;
    if (!color.empty()) std::cout << COLOR_RESET;
    std::cout << "\n";
}

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    system("cls");
#else
    system("clear");
#endif
}

// Hàm tạm dừng màn hình chờ bấm Enter chuẩn xác
void pauseScreen() {
    std::cout << "\nNhan Enter de tiep tuc...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Hàm hiển thị Menu tự động căn giữa
int showMenu(const std::string& subtitle, const std::vector<std::string>& options) {
    int selectedIndex = 0;
    showCursor(false); // Ẩn con trỏ chuột khi duyệt Menu

    while (true) {
        clearScreen();

        int consoleWidth = 120, consoleHeight = 30;
        getConsoleSize(consoleWidth, consoleHeight);

        std::vector<std::pair<std::string, std::string>> lines;

        lines.push_back({"  ______ _      _____   ____  _____  _____          ", COLOR_TITLE});
        lines.push_back({" |  ____| |    |  __ \\ / __ \\|  __ \\|_   _|/\\       ", COLOR_TITLE});
        lines.push_back({" | |__  | |    | |  | | |  | | |__) | | | /  \\      ", COLOR_TITLE});
        lines.push_back({" |  __| | |    | |  | | |  | |  _  /  | |/ /\\ \\     ", COLOR_TITLE});
        lines.push_back({" | |____| |____| |__| | |__| | | \\ \\ _| / ____ \\    ", COLOR_TITLE});
        lines.push_back({" |______|______|_____/ \\____/|_|  \\_\\___/_/    \\_\\   ", COLOR_TITLE});
        lines.push_back({"--- THE ORIGIN CRYSTAL (RPG CONSOLE) ---", COLOR_INFO});
        lines.push_back({"", ""});

        std::string border(64, '=');
        lines.push_back({border, COLOR_BORDER});
        lines.push_back({subtitle, COLOR_MENU_TEXT});
        lines.push_back({border, COLOR_BORDER});
        lines.push_back({"", ""});

        for (size_t i = 0; i < options.size(); ++i) {
            if (static_cast<int>(i) == selectedIndex) {
                lines.push_back({"  [=>]  " + options[i] + "  [<=]  ", COLOR_SELECT});
            } else {
                lines.push_back({"        " + options[i] + "        ", ""});
            }
        }

        lines.push_back({"", ""});
        lines.push_back({border, COLOR_BORDER});
        lines.push_back({"[Up/Down]: Di chuyển  |  [ENTER]: Chọn  |  [ESC]: Thoát", COLOR_INFO});

        int totalContentLines = static_cast<int>(lines.size());
        int topPadding = (consoleHeight - totalContentLines) / 2;
        if (topPadding < 0) topPadding = 0;

        for (int i = 0; i < topPadding; ++i) {
            std::cout << "\n";
        }

        for (const auto& line : lines) {
            printCentered(line.first, consoleWidth, line.second);
        }

        int key = getch();
        if (key == KEY_UP) {
            selectedIndex = (selectedIndex - 1 + static_cast<int>(options.size())) % static_cast<int>(options.size());
        } else if (key == KEY_DOWN) {
            selectedIndex = (selectedIndex + 1) % static_cast<int>(options.size());
        } else if (key == KEY_ENTER) {
            return selectedIndex;
        } else if (key == KEY_ESC) {
            return -1;
        }
    }
}

// ==========================================
// Helper: EnemyType -> nhan hien thi
// ==========================================

std::string enemyTypeLabel(EnemyType type) {
    switch (type) {
        case EnemyType::NORMAL: return "Thuong";
        case EnemyType::ELITE:  return "Tinh Anh";
        case EnemyType::BOSS:   return "TRUM";
    }
    return "";
}

// ==========================================
// BATTLE: tao Enemy tu EnemyData va chay BattleSystem hien tai
// ==========================================

void doBattle(Game& game, const EnemyData& data) {
    Character* player = game.getPlayer();

    if (player == nullptr) {
        return;
    }

    // Tao 1 Enemy moi tren heap tu du lieu trong EnemyData
    // (khong goi lai cac ham create...() vi Enemy khong the copy/move,
    //  nhung constructor cong khai cua Enemy thi dung duoc truc tiep).
    Character* enemyPtr = new Enemy(
        data.id,
        data.name,
        data.type,
        data.areaId,
        data.maxHP,
        data.attack,
        data.defense,
        data.intelligence,
        data.agility,
        data.experienceReward,
        data.goldReward
    );

    std::vector<Character*> enemies;
    enemies.push_back(enemyPtr);

    clearScreen();
    showCursor(true);

    std::cout << "\n=====================================\n";
    std::cout << "        ELDORIA - CHIEN DAU\n";
    std::cout << "=====================================\n";
    std::cout << "Ban cham tran voi " << data.name
               << " [" << enemyTypeLabel(data.type) << "]!\n";

    // Su dung dung BattleSystem hien tai, khong viet lai he thong khac
    BattleSystem battle(*player, enemies);
    battle.startBattle();

    if (player->isAlive()) {
        int totalGold = 0;

        for (Character* e : enemies) {
            if (e != nullptr && !e->isAlive()) {
                Enemy* asEnemy = dynamic_cast<Enemy*>(e);

                if (asEnemy != nullptr) {
                    totalGold += asEnemy->getGoldReward();
                }
            }
        }

        if (totalGold > 0) {
            player->setGold(player->getGold() + totalGold);

            std::cout << "\n>>> Ban nhan them " << totalGold
                       << " vang tu chien loi pham! <<<\n";
        }
    } else {
        // Defeat: hoi phuc HP de tro ve tiep tuc hanh trinh
        // (khong co man Game Over vinh vien theo yeu cau flow)
        player->setHP(player->getMaxHP());

        std::cout << "\n" << player->getName()
                   << " duoc dua ve noi an toan va hoi phuc HP.\n";
    }

    for (Character* e : enemies) {
        delete e;
    }

    showCursor(false);
    pauseScreen();
}

// ==========================================
// WORLD MAP: CHOOSE AREA -> CHOOSE ENEMY -> BATTLE
// ==========================================

void exploreWorld(Game& game) {
    if (!game.hasPlayer()) {
        clearScreen();
        showCursor(true);
        std::cout << "\nHay tao nhan vat truoc (New Game)!\n";
        pauseScreen();
        showCursor(false);
        return;
    }

    // Map chi quan ly du lieu khu vuc (khong doi tuong nao thay doi state
    // cua no), nen dung 1 instance rieng trong main la an toan va khong
    // can Game phai lo them mot getter moi.
    Map worldMap;

    bool exploring = true;

    while (exploring) {
        const std::vector<Area>& areas = worldMap.getAreas();

        std::vector<std::string> areaOptions;
        for (const Area& area : areas) {
            areaOptions.push_back(area.name);
        }
        areaOptions.push_back("Quay lai Menu chinh");

        int areaChoice = showMenu("CHON KHU VUC KHAM PHA (WORLD MAP)", areaOptions);

        if (areaChoice == -1 || areaChoice == static_cast<int>(areaOptions.size() - 1)) {
            exploring = false;
            break;
        }

        const Area& selectedArea = areas[static_cast<size_t>(areaChoice)];
        std::vector<EnemyData> enemyList = Enemy::getEnemiesByArea(selectedArea.id);

        bool inArea = true;

        while (inArea) {
            std::vector<std::string> enemyOptions;

            for (const EnemyData& e : enemyList) {
                enemyOptions.push_back(
                    e.name + " [" + enemyTypeLabel(e.type) + "] - Lv." + std::to_string(e.level)
                );
            }
            enemyOptions.push_back("Quay lai World Map");

            int enemyChoice = showMenu(
                "KHU VUC: " + selectedArea.name + " - CHON QUAI VAT",
                enemyOptions
            );

            if (enemyChoice == -1 || enemyChoice == static_cast<int>(enemyOptions.size() - 1)) {
                inArea = false;
                break;
            }

            doBattle(game, enemyList[static_cast<size_t>(enemyChoice)]);

            // Sau tran, hoi nguoi choi co muon kham pha tiep khu vuc nay khong
            std::vector<std::string> continueOptions = {
                "Kham pha tiep khu vuc nay",
                "Quay lai World Map"
            };

            int cont = showMenu("BAN MUON LAM GI TIEP THEO?", continueOptions);

            if (cont != 0) {
                inArea = false;
            }
        }
    }
}

// ==========================================
// INVENTORY: mo tui do that su cua nhan vat
// ==========================================

void openInventoryMenu(Game& game) {
    Character* player = game.getPlayer();

    if (player == nullptr) {
        clearScreen();
        showCursor(true);
        std::cout << "\nHay tao nhan vat truoc (New Game)!\n";
        pauseScreen();
        showCursor(false);
        return;
    }

    bool open = true;

    while (open) {
        clearScreen();
        showCursor(true);

        std::cout << "\n=====================================\n";
        std::cout << "             TUI DO ELDORIA\n";
        std::cout << "=====================================\n";

        player->getInventory().showInventory();

        std::cout << "\n1. Su dung / Trang bi vat pham\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Lua chon: ";

        int choice = -1;
        std::cin >> choice;

        if (choice == 1) {
            int count = player->getInventory().getItemCount();

            if (count == 0) {
                std::cout << "\nTui do dang trong!\n";
            } else {
                std::cout << "Chon vat pham (1-" << count << "): ";

                int idx = 0;
                std::cin >> idx;

                player->getInventory().useItem(idx - 1, *player);
            }

            pauseScreen();
        } else {
            open = false;
        }
    }

    showCursor(false);
}

int main() {
    setFullscreen();
    showCursor(false);

    Game game;
    game.initialize();

    std::vector<std::string> mainMenuOptions = {
        "Bắt đầu trò chơi mới (New Game)",
        "Chọn khu vực khám phá (World Map)",
        "Túi đồ (Inventory)",
        "Cửa hàng (Shop)",
        "Nhật ký nhiệm vụ (Quest Journal)",
        "Lưu trò chơi (Save Game)",
        "Tải trò chơi (Load Game)",
        "Thoát (Exit)"
    };

    bool isRunning = true;

    while (isRunning) {
        int choice = showMenu("MENU CHÍNH - ELDORIA: THE ORIGIN CRYSTAL", mainMenuOptions);

        switch (choice) {
            case 0: { // New Game
                int classChoice = showMenu(
                    "CHỌN CLASS NHÂN VẬT",
                    { "Warrior", "Mage", "Archer" }
                );

                if (classChoice == -1) break;

                clearScreen();
                showCursor(true); // Hiển thị lại con trỏ chuột để người dùng nhập tên

                std::string name;
                std::cout << "\n========================================";
                std::cout << "\n Nhap ten nhan vat: ";
                std::getline(std::cin >> std::ws, name);

                game.startNewGame(classChoice, name);

                if (game.hasPlayer()) {
                    std::cout << "\n=====================================\n";
                    std::cout << "           STARTING AREA\n";
                    std::cout << "=====================================\n";
                    std::cout << "Ban tinh day o ria phia Bac cua DARK FOREST,\n";
                    std::cout << "vung dat dau tien tren hanh trinh tim kiem\n";
                    std::cout << "The Origin Crystal cua Eldoria...\n";
                }

                showCursor(false);
                pauseScreen();
                break;
            }

            case 1: { // World Map -> Choose Area -> Choose Enemy -> Battle
                exploreWorld(game);
                break;
            }

            case 2: { // Inventory
                openInventoryMenu(game);
                break;
            }

            case 3: { // Shop
                clearScreen();
                showCursor(true);
                if (!game.hasPlayer()) {
                    std::cout << "\nHay tao nhan vat truoc!\n";
                    pauseScreen();
                } else {
                    game.openShop();
                    pauseScreen();
                }
                showCursor(false);
                break;
            }

            case 4: { // Quest Journal
                clearScreen();
                if (!game.hasPlayer()) {
                    std::cout << "\nHay tao nhan vat truoc!\n";
                    pauseScreen();
                } else {
                    showCursor(true);
                    game.showQuests();
                    showCursor(false);
                }
                break;
            }

            case 5: { // Save Game
                clearScreen();
                if (!game.hasPlayer()) {
                    std::cout << "\nHay tao nhan vat truoc!\n";
                } else if (game.saveGame()) {
                    std::cout << "\nLuu game thanh cong!\n";
                } else {
                    std::cout << "\nKhong the luu game!\n";
                }
                pauseScreen();
                break;
            }

            case 6: { // Load Game
                clearScreen();
                if (!game.hasPlayer()) {
                    std::cout << "\nHay tao nhan vat truoc!\n";
                } else if (game.loadGame()) {
                    std::cout << "\nLoad game thanh cong!\n";
                } else {
                    std::cout << "\nKhong the load game!\n";
                }
                pauseScreen();
                break;
            }

            case 7:
            case -1: { // Exit
                clearScreen();
                int w = 120, h = 30;
                getConsoleSize(w, h);

                for (int i = 0; i < h / 2; ++i) {
                    std::cout << "\n";
                }

                printCentered(
                    "Cảm ơn bạn đã chơi Eldoria: The Origin Crystal!",
                    w,
                    COLOR_TITLE
                );

                showCursor(true); // Trả lại con trỏ chuột ban đầu cho Terminal
                isRunning = false;
                break;
            }
        }
    }

    return 0;
}