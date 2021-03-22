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

}

void GraphicLib::exit_lib()
{

}

int GraphicLib::test(int i)
{
    std::cout << i << std::endl;
    i++;
    return (i);
}