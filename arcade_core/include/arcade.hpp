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
#include <fstream>
#include <chrono>

class Arcade
{
public:
    Arcade();
    ~Arcade();

    void get_shared_libs();
    void launch_menu(IGraphicLib *glib);
    std::vector<std::string> load_map(std::string path);
    void gest_input(IGraphicLib *glib);

private:
    std::vector<std::string> games;
    std::vector<std::string> libs;
};




#endif /* !CORE_HPP_ */
