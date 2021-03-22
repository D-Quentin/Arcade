/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** arcade
*/

#include "arcade.hpp"

Arcade::Arcade()
{
}

Arcade::~Arcade()
{
}

std::vector<std::string> Arcade::get_libs_name()
{
    DIR *rep = opendir("lib/");
    std::vector<std::string> toto;
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".so") != NULL) {
                std::string mystring = std::string(ent->d_name);
                toto.push_back(mystring);
            }
        }
        closedir(rep);
    }
    std::cout << toto[0] << std::endl;
    return toto;
}

std::vector<std::string> Arcade::get_games_name()
{

}
