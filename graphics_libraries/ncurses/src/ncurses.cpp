/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "ncurses.hpp"

extern "C"
{
    GraphicLib *MakeGraphicLib()
    {
        return new GraphicLib();
    }
}

void GraphicLib::init_lib()
{
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

void GraphicLib::exit_lib()
{
    refresh();
    endwin();
}

int GraphicLib::keyPressed() const
{
    int my_getch = getch();

    return (my_getch);
}

void GraphicLib::printMap(std::vector<std::string> map)
{
    size_t y = 0;

    while (map.size() != y) {
        mvprintw(y, 0, map[y].c_str());
        y++;
    }

}

size_t strlen_emoji(const std::string& str)
{
    size_t length = 0;
    size_t tmp = 0;
    size_t emoji = 0;

    for (char c : str) {
        if ((c & 0xC0) != 0x80 || tmp % 2 == 0) {
            length++;
            tmp++;
        }
        if ((c & 0xC0) == 0x80)
            emoji = 1;

    }
    return (length + emoji);
}

void GraphicLib::printButton(int x, int y, std::string name)
{
    std::string line1 = "┏";
    std::string line2 = "┃ ";
    std::string line3 = "┗";

    for (size_t i = 0 ; i != strlen_emoji(name) + 2 ; i++) {
        line1 += "━";
        line3 += "━";
    }
    line2 += name;
    line1 += "┓";
    line2 += " ┃";
    line3 += "┛";
    mvprintw(y, x, line1.c_str());
    mvprintw(y + 1, x, line2.c_str());
    mvprintw(y + 2, x, line3.c_str());
}

void GraphicLib::printSelectedButton(int x, int y, std::string name)
{
    std::string line1 = "┌";
    std::string line2 = "┆ ";
    std::string line3 = "└";

    for (size_t i = 0 ; i != strlen_emoji(name) + 2 ; i++) {
        line1 += "╌";
        line3 += "╌";
    }
    line2 += name;
    line1 += "┐";
    line2 += " ┆";
    line3 += "┘";
    mvprintw(y, x, line1.c_str());
    mvprintw(y + 1, x, line2.c_str());
    mvprintw(y + 2, x, line3.c_str());
}

void GraphicLib::printText(int x, int y, std::string)
{

}

void GraphicLib::clearWindow()
{

}

void GraphicLib::refreshWindow()
{

}

void GraphicLib::printWindow()
{

}

void GraphicLib::printTitle(std::string)
{

}

std::pair<int, int> GraphicLib::getWindowSize() const
{

}

void GraphicLib::assetLoader(const std::string)
{

}
