#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

#include <string>
#include <vector>

class Character; // Forward declaration

class ConsoleUtils {
public:
    // Cấu hình màn hình Console
    static void setFullscreen();
    static void hideCursor();
    static void clearScreen();
    static void getConsoleSize(int& width, int& height);

    // Xử lý chuỗi và định dạng UI
    static size_t getDisplayLength(const std::string& str);
    static void printCentered(const std::string& text, int consoleWidth, const std::string& color = "");

    // Xử lý Menu và Input người dùng
    static int showMenuCustom(const std::string& title, const std::vector<std::string>& options, const Character& player);
    static int getchInput();
};

#endif // CONSOLEUTILS_H