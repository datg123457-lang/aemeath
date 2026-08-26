#include <iostream>
#include <vector>
#include <string>
#include "core/Game.h"
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <windows.h>
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_ENTER 13
    #define KEY_ESC 27

    // 1. Phóng to cửa sổ CMD thành Toàn màn hình (Fullscreen)
    void setFullscreen() {
        HWND hwnd = GetConsoleWindow();
        if (hwnd == NULL) return;
        
        // Mở tối đa cửa sổ Console (Maximize)
        ShowWindow(hwnd, SW_MAXIMIZE);
    }

    // 2. Ẩn con trỏ nhấp nháy trên Console
    void hideCursor() {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
    }

    // 3. Lấy kích thước (Cột, Dòng) thực tế của màn hình CMD Fullscreen
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
    void hideCursor() { std::cout << "\e[?25l"; }

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
#define COLOR_RESET   "\033[0m"
#define COLOR_TITLE   "\033[1;36m"
#define COLOR_MENU_TEXT "\033[1;33m"
#define COLOR_SELECT  "\033[1;32m"
#define COLOR_INFO    "\033[0;35m"
#define COLOR_BORDER  "\033[1;34m"

// Tính số ký tự Unicode thực tế (Bỏ qua các byte phụ của UTF-8 tiếng Việt)
size_t getDisplayLength(const std::string& str) {
    size_t len = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if ((str[i] & 0xC0) != 0x80) len++;
    }
    return len;
}

// In văn bản căn giữa theo chiều ngang Cột của màn hình
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

// Hàm hiển thị Menu tự động căn giữa toàn bộ khi ở chế độ Fullscreen
int showMenu(const std::string& subtitle, const std::vector<std::string>& options) {
    int selectedIndex = 0;
    
    while (true) {
        clearScreen();

        // 1. Lấy độ phân giải (số Cột & Dòng) thực tế của màn hình Fullscreen
        int consoleWidth = 120, consoleHeight = 30;
        getConsoleSize(consoleWidth, consoleHeight);

        // 2. Tạo danh sách chứa toàn bộ các dòng nội dung cần vẽ
        std::vector<std::pair<std::string, std::string>> lines;

        // Banner ASCII Art lớn hơn phù hợp Fullscreen
        lines.push_back({"  ______ _      _____   ____  _____  _____          ", COLOR_TITLE});
        lines.push_back({" |  ____| |    |  __ \\ / __ \\|  __ \\|_   _|/\\       ", COLOR_TITLE});
        lines.push_back({" | |__  | |    | |  | | |  | | |__) | | | /  \\      ", COLOR_TITLE});
        lines.push_back({" |  __| | |    | |  | | |  | |  _  /  | |/ /\\ \\     ", COLOR_TITLE});
        lines.push_back({" | |____| |____| |__| | |__| | | \\ \\ _| / ____ \\    ", COLOR_TITLE});
        lines.push_back({" |______|______|_____/ \\____/|_|  \\_\\___/_/    \\_\\   ", COLOR_TITLE});
        lines.push_back({"--- THE ORIGIN CRYSTAL (RPG CONSOLE) ---", COLOR_INFO});
        lines.push_back({"", ""});

        // Khung Tiêu Đề
        std::string border(64, '=');
        lines.push_back({border, COLOR_BORDER});
        lines.push_back({subtitle, COLOR_MENU_TEXT});
        lines.push_back({border, COLOR_BORDER});
        lines.push_back({"", ""});

        // Tùy chọn Menu
        for (size_t i = 0; i < options.size(); ++i) {
            if (static_cast<int>(i) == selectedIndex) {
                lines.push_back({"  [=>]  " + options[i] + "  [<=]  ", COLOR_SELECT});
            } else {
                lines.push_back({"        " + options[i] + "        ", ""});
            }
        }

        // Hướng dẫn thao tác
        lines.push_back({"", ""});
        lines.push_back({border, COLOR_BORDER});
        lines.push_back({"[Up/Down]: Di chuyển  |  [ENTER]: Chọn  |  [ESC]: Thoát", COLOR_INFO});

        // 3. CĂN GIỮA CHIỀU DỌC (VERTICAL CENTER): 
        // Tính toán số lượng dòng trống đệm ở trên bằng 1/2 khoảng dư màn hình
        int totalContentLines = static_cast<int>(lines.size());
        int topPadding = (consoleHeight - totalContentLines) / 2;
        if (topPadding < 0) topPadding = 0;

        for (int i = 0; i < topPadding; ++i) {
            std::cout << "\n";
        }

        // 4. CĂN GIỮA CHIỀU NGANG (HORIZONTAL CENTER): In từng dòng ra giữa màn hình
        for (const auto& line : lines) {
            printCentered(line.first, consoleWidth, line.second);
        }

        // 5. Lấy phím bấm từ người dùng
        int key = getch();
        if (key == KEY_UP) {
            selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
        } else if (key == KEY_DOWN) {
            selectedIndex = (selectedIndex + 1) % options.size();
        } else if (key == KEY_ENTER) {
            return selectedIndex;
        } else if (key == KEY_ESC) {
            return -1;
        }
    }
}

int main() {
    // 1. Phóng to Fullscreen & Ẩn con trỏ chuột nhấp nháy
    setFullscreen();
    hideCursor();
Game game;
game.initialize();
    std::vector<std::string> mainMenuOptions = {
        "Bắt đầu trò chơi mới (New Game)",
        "Chọn khu vực khám phá (World Map)",
        "Nhật ký nhiệm vụ (Quest Journal)",
        "Tải game (Load Game)",
        "Cài đặt (Settings)",
        "Thoát (Exit)"
    };

    bool isRunning = true;

    while (isRunning)
{
    int choice = showMenu(
        "MENU CHÍNH TRÒ CHƠI",
        mainMenuOptions
    );

    switch (choice)
    {
        case 0:
        {
            // New Game

            int classChoice = showMenu(
                "CHỌN CLASS NHÂN VẬT",
                {
                    "Warrior",
                    "Mage",
                    "Archer"
                }
            );

            if (classChoice == -1)
            {
                break;
            }

            clearScreen();

            std::string name;

            std::cout << "\n";
            std::cout << "Nhap ten nhan vat: ";
            std::getline(std::cin >> std::ws, name);

            game.startNewGame(classChoice, name);

            std::cout << "\nNhan Enter de tiep tuc...";
            std::cin.get();

            break;
        }

        case 1:
        {
            // World Map
            clearScreen();

            game.showMap();

            std::cout << "\nNhan Enter de quay lai...";
            std::cin.get();

            break;
        }

        case 2:
        {
            // Quest Journal
            clearScreen();

            if (!game.hasPlayer())
            {
                std::cout << "\nHay tao nhan vat truoc!\n";
                std::cout << "\nNhan Enter de quay lai...";
                std::cin.get();
            }
            else
            {
                game.showQuests();
            }

            break;
        }

        case 3:
        {
            // Load Game
            clearScreen();

            if (!game.hasPlayer())
            {
                std::cout << "\nHay tao nhan vat truoc!\n";
            }
            else if (game.loadGame())
            {
                std::cout << "\nLoad game thanh cong!\n";
            }
            else
            {
                std::cout << "\nKhong the load game!\n";
            }

            std::cout << "\nNhan Enter de quay lai...";
            std::cin.get();

            break;
        }

        case 4:
        {
            // Settings
            clearScreen();

            std::cout << "\n";
            std::cout << "Settings chua duoc trien khai.\n";
            std::cout << "\nNhan Enter de quay lai...";
            std::cin.get();

            break;
        }

        case 5:
        case -1:
        {
            clearScreen();

            int w = 120;
            int h = 30;

            getConsoleSize(w, h);

            for (int i = 0; i < h / 2; ++i)
            {
                std::cout << "\n";
            }

            printCentered(
                "Cảm ơn bạn đã chơi Eldoria: The Origin Crystal!",
                w,
                COLOR_TITLE
            );

            isRunning = false;
            break;
        }
    }
}

    return 0;
}