/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** nCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IGraphicLib.hpp"
#include <iostream>
#include <locale.h>
#define NCURSES_WIDECHAR 1
#include <ncursesw/curses.h>

class GraphicLib : public IGraphicLib
{
    public:
        virtual void init_lib();
        virtual void exit_lib();
        virtual int keyPressed() const;
        virtual void printMap(std::vector<std::string>);
        virtual void printButton(int x, int y, std::string);
        virtual void printSelectedButton(int x, int y, std::string);
        virtual void printText(int x, int y, std::string);
        virtual void clearWindow();
        virtual void refreshWindow();
        virtual void printWindow();
        virtual void printTitle(std::string);
        virtual std::pair<int, int> getWindowSize() const;
        virtual void assetLoader(const std::string);
    protected:
    private:
        std::map<std::string, std::vector<std::string>> _maps;
};

#endif /* !NCURSES_HPP_ */
