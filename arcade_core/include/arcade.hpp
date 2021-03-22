/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <dlfcn.h>
#include <iostream>
#include "IGraphicLib.hpp"
#include <vector>
#include <dirent.h>
#include <string.h>

class Arcade
{
public:
    Arcade();
    ~Arcade();

    std::vector<std::string> get_libs_name();
    std::vector<std::string> get_games_name();

private:
    std::vector<std::string> games;
    std::vector<std::string> libs;
};




#endif /* !CORE_HPP_ */
