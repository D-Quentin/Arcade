/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "IGraphicLib.hpp"

class IGame {
    public:
        virtual ~IGame() = default;
        virtual void launchGame(IGraphicLib *lib) const = 0;

    protected:
    private:
};

#endif /* !IGAME_HPP_ */
