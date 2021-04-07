/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "pacman.hpp"


extern "C"
{
    Game *MakeGame()
    {
        return new Game();
    }
}

Game::Game(/* args */)
{
}

Game::~Game()
{
}

void Game::launchMenu(IGraphicLib *glib)
{
    (void)glib;
}

std::vector<std::string> Game::load_map(std::string path)
{
    std::vector<std::string> map;
    std::string line = "";
    std::ifstream file(path);
    char c;
    size_t i = 0;
    int j = 0;

    if (file) {
        while (file.get(c)) {
            line += c;
            if (c == '\n') {
                map.push_back(line);
                i++;
                j = 0;
                line = "";
            }
            j++;
        }
    } else {
        std::cerr << "load_map: wrong path to map : \"" << path << "\"" << std::endl;
    }
    return (map);
}

int Game::launchGame(IGraphicLib *glib)
{
    glib->clearWindow();
    gameLoop(glib);
}

void Game::gest_input(IGraphicLib *glib, int input)
{
    if (input == 'q') {
        glib->exit_lib();
        exit(0);
    }
}

int Game::gameLoop(IGraphicLib *glib)
{
    int input = -1;
    glib->clearWindow();
    std::vector<std::string> map_menu = this->load_map("assets/pacman/maps/map.txt");
    while (1) {
        input = glib->keyPressed();
        glib->printMap(map_menu);
        gest_input(glib, input);
    }
    (void)glib;
}
