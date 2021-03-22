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
        virtual void init_lib();
        virtual void exit_lib();
    protected:
    private:
};

#endif /* !NCURSES_HPP_ */
