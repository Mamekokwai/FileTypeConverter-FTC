#include "main.h"

void setup_console_encoding()
{
    // 方法1: 使用系统命令
    system("chcp 65001 > nul");

    // 方法2: 使用 Windows API
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // 方法3: 设置控制台字体支持中文
    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(font);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
    wcscpy(font.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
}
