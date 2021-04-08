/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** Game
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include "IGame.hpp"
#include "IGraphicLib.hpp"
#include <dlfcn.h>
#include <vector>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <chrono>
class Game : public IGame
{
public:
    Game();
    ~Game();
    virtual void launchMenu(IGraphicLib *glib);
    virtual int launchGame(IGraphicLib *glib);
    virtual int gameLoop(IGraphicLib *glib);
    std::vector<std::string> load_map(std::string path);
    void gest_exit(IGraphicLib *glib, int input);
    void gest_input(IGraphicLib *glib, int input, std::vector<std::string> map);
    std::vector<std::string> move_pac(IGraphicLib *glib, int input, std::vector<std::string> map);
private:
    std::vector<std::pair<int, int>> fpos;
    std::pair<int, int> ppos;
    std::vector<int> fdir;
    int pdir;
    int score;
};


#endif /* !PACMAN_HPP_ */
