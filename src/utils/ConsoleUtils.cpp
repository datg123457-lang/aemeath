#include "utils/ConsoleUtils.h"
#include "entities/Character.h"
#include <iostream>
#include <iomanip>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

void ConsoleUtils::clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleUtils::hideCursor() {
#if defined(_WIN32) || defined(_WIN64)
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    std::cout << "\033[?25l";
#endif
}

void ConsoleUtils::setFullscreen() {
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(65001); // Bật UTF-8 cho Windows Console
#endif
}

void ConsoleUtils::getConsoleSize(int& width, int& height) {
#if defined(_WIN32) || defined(_WIN64)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    width = 80;
    height = 25;
#endif
}

size_t ConsoleUtils::getDisplayLength(const std::string& str) {
    size_t length = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if ((str[i] & 0xC0) != 0x80) { // Đếm các ký tự không phải byte nối UTF-8
            length++;
        }
    }
    return length;
}

void ConsoleUtils::printCentered(const std::string& text, int consoleWidth, const std::string& color) {
    size_t len = getDisplayLength(text);
    int padding = (consoleWidth - static_cast<int>(len)) / 2;
    if (padding > 0) {
        std::cout << std::string(padding, ' ');
    }
    std::cout << color << text << "\033[0m\n";
}

int ConsoleUtils::getchInput() {
#if defined(_WIN32) || defined(_WIN64)
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

int ConsoleUtils::showMenuCustom(const std::string& title, const std::vector<std::string>& options, const Character& player) {
    int selected = 0;
    int width = 60, height = 25;

    while (true) {
        clearScreen();
        std::cout << "============================================================\n";
        std::cout << "  " << title << "\n";
        std::cout << "  HP: " << player.getHP() << "/" << player.getMaxHP() 
                  << " | Gold: " << player.getGold() 
                  << " | Lv: " << player.getLevel() << "\n";
        std::cout << "============================================================\n\n";

        for (size_t i = 0; i < options.size(); ++i) {
            if (static_cast<int>(i) == selected) {
                std::cout << "  > " << options[i] << " <\n";
            } else {
                std::cout << "    " << options[i] << "\n";
            }
        }

        std::cout << "\n============================================================\n";
        std::cout << " (Dung phim W/S hoac Mui ten de di chuyen, Enter de chon)\n";

        int key = getchInput();
        if (key == 13 || key == 10) { // Phím Enter
            return selected;
        } else if (key == 'w' || key == 'W' || key == 72) { // Đi lên
            selected = (selected - 1 + static_cast<int>(options.size())) % static_cast<int>(options.size());
        } else if (key == 's' || key == 'S' || key == 80) { // Đi xuống
            selected = (selected + 1) % static_cast<int>(options.size());
        } else if (key == 27) { // Phím ESC
            return -1;
        }
    }
}