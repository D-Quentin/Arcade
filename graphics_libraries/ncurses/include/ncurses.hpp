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

class GraphicLib : public IGraphicLib
{
    public:
        virtual int test(int i);
    protected:
    private:
};

#endif /* !NCURSES_HPP_ */
