/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** centipede
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include <iostream>
#include "IGame.hpp"
#include "IGraphicLib.hpp"

class Game : public IGame
{
private:
    /* data */
public:
    Game();
    ~Game();
    virtual void launchMenu(IGraphicLib *glib);
    virtual void launchGame(IGraphicLib *glib);
    virtual void gameLoop(IGraphicLib *glib);
};

#endif /* !CENTIPEDE_HPP_ */
