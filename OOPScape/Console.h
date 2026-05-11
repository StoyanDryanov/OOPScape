#pragma once

#include <windows.h>

namespace Console
{
    enum Color
    {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        GRAY = 7,
        DARK_GRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };

    inline void setColor(Color text, Color background = BLACK)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (WORD)(background << 4 | text));
    }

    inline void reset()
    {
        setColor(GRAY, BLACK);
    }

    inline void clear()
    {
        system("cls");
    }
}