/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** arcade
*/

#include "arcade.hpp"

Arcade::Arcade()
{
    get_shared_libs();
}

Arcade::~Arcade()
{
}

void Arcade::get_shared_libs()
{
    DIR *rep = opendir("lib/");
    std::vector<std::string> shared_libs;
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".so") != NULL) {
                std::string mystring = std::string(ent->d_name);
                shared_libs.push_back("lib/" + mystring);
            }
        }
        closedir(rep);
    }
    void *handle = NULL;
    void *mkr = NULL;
    for (size_t i = 0 ; i != shared_libs.size() ; i++) {
        handle = dlopen(shared_libs[i].c_str(), RTLD_LAZY);
        if (handle != NULL) {
            mkr = dlsym(handle, "MakeGraphicLib");
            if (mkr != NULL)
                this->libs.push_back(shared_libs[i]);
            mkr = dlsym(handle, "MakeGame");
            if (mkr != NULL)
                this->games.push_back(shared_libs[i]);
        }
    }
    std::cout << "Libs :" << std::endl;
    for (size_t i = 0 ; i != this->libs.size() ; i++) {
        std::cout << this->libs[i] << std::endl;
    }
    std::cout << "Games :" << std::endl;
    for (size_t i = 0 ; i != this->games.size() ; i++) {
        std::cout << this->games[i] << std::endl;
    }
}

void Arcade::launch_menu(IGraphicLib *glib)
{
    std::vector<std::string> map_menu = this->load_map("assets/arcade/maps/menu.txt");
    auto start = std::chrono::high_resolution_clock::now();
    
    while (1) {
        //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() > 1000000000) {
            glib->printMap(map_menu);
            start = std::chrono::high_resolution_clock::now();
        }
        this->gest_input(glib);
    }
}

void Arcade::gest_input(IGraphicLib *glib)
{
    if (glib->keyPressed() == 'q') {
        glib->exit_lib();
        std::exit(0);
    }

}

std::vector<std::string> Arcade::load_map(std::string path)
{
    std::vector<std::string> map;
    std::string line = "";
    std::ifstream file(path);
    char c;
    int i = 0;
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