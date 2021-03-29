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
    this->player_name = "";
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
    int input = -1;

    this->init_bouton();
    while (1) {
        input = glib->keyPressed();
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() > 100000000) {
            glib->printMap(map_menu);
            this->print_bouton(glib);
            start = std::chrono::high_resolution_clock::now();
        }
        this->gest_name(input);
        this->gest_bouton(input);
        this->gest_input(glib, input);
    }
}

void Arcade::gest_input(IGraphicLib *glib, int input)
{
    if (input == 'q' && this->bouton[2][0].first != 1) {
        glib->exit_lib();
        std::exit(0);
    }
    if (input != -1)
        glib->printButton(100, 2, std::to_string(input));
}

std::vector<std::string> Arcade::load_map(std::string path)
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

void Arcade::gest_name(int input)
{
    std::string your_name = "Your name:            ";
    if (this->bouton[2][0].first == 1) {
        if (this->player_name.size() <= 10 && input >= 32 && input <= 126)
            this->player_name += input;
        if (input == KEY_DEL && this->player_name.size() > 0)
            this->player_name = this->player_name.erase(this->player_name.size() - 1);
        for (size_t i = 11, j = 0 ; j != this->player_name.size() ; i++, j++)
            your_name[i] = this->player_name[j];
        this->bouton[2][0].second = your_name;
    }
}

void Arcade::gest_bouton(int input)
{
    int key = input;

    if (key == ARROW_DOWN) {
        for (size_t i = 0 ; i != this->libs.size() ; i++) {
            if (this->bouton[0][i].first == 1 && i + 1 != this->libs.size()) {
                this->bouton[0][i].first = 0;
                this->bouton[0][i + 1].first = 1;
            }
        }
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1 && i + 1 != this->games.size()) {
                this->bouton[1][i].first = 0;
                this->bouton[1][i + 1].first = 1;
            }
        }
    }
    if (key == ARROW_UP) {
        for (size_t i = 0 ; i != this->libs.size() ; i++) {
            if (this->bouton[0][i].first == 1 && i != 0) {
                this->bouton[0][i].first = 0;
                this->bouton[0][i - 1].first = 1;
            }
        }
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1 && i != 0) {
                this->bouton[1][i].first = 0;
                this->bouton[1][i - 1].first = 1;
            }
        }
    }
    if (key == ARROW_RIGHT) {
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1) {
                this->bouton[1][i].first = 0;
                this->bouton[2][0].first = 1;
            }
        }
        for (size_t i = 0 ; i != this->libs.size() ; i++) {
            if (this->bouton[0][i].first == 1) {
                this->bouton[0][i].first = 0;
                this->bouton[1][0].first = 1;
            }
        }
    }
    if (key == ARROW_LEFT) {
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1) {
                this->bouton[1][i].first = 0;
                this->bouton[0][0].first = 1;
            }
        }
        if (this->bouton[2][0].first == 1) {
                this->bouton[2][0].first = 0;
                this->bouton[1][0].first = 1;
        }
    }
}

void Arcade::print_bouton(IGraphicLib *glib)
{
    for (size_t i = 0 ; i != this->bouton[0].size() ; i++) {
        if (this->bouton[0][i].first == 1)
            glib->printSelectedButton(3, 4 + i * 4, this->bouton[0][i].second);
        else
            glib->printButton(3, 4 + i * 4, this->bouton[0][i].second);
    }
    for (size_t i = 0 ; i != this->bouton[1].size() ; i++) {
        if (this->bouton[1][i].first == 1)
            glib->printSelectedButton(17, 4 + i * 4, this->bouton[1][i].second);
        else
            glib->printButton(17, 4 + i * 4, this->bouton[1][i].second);
    }
    if (this->bouton[2][0].first == 1)
            glib->printSelectedButton(31, 4, this->bouton[2][0].second);
    else
        glib->printButton(31, 4, this->bouton[2][0].second);
}

std::string Arcade::get_logo(std::string name)
{
    std::ifstream file("assets/" + name + "/logo");
    char c;
    std::string line = "";

    if (file) {
        while (file.get(c)) {
            line += c;
        }
        return (line);
    } else {
        return (name);
    }
}

void Arcade::init_bouton()
{
    std::vector<std::pair<bool, std::string>> lib;
    std::vector<std::pair<bool, std::string>> game;
    std::vector<std::pair<bool, std::string>> name;
    std::pair<bool, std::string> tmp;
    int j = 1;

    for (size_t i = 0 ; i != this->libs.size() ; i++) {
        tmp.first = j;
        j = 0;
        tmp.second = this->libs[i].substr(11, this->libs[i].find(".so") - 11);
        lib.push_back(tmp);
    }
    for (size_t i = 0 ; i != this->games.size() ; i++) {
        tmp.first = 0;
        tmp.second = this->get_logo(this->games[i].substr(11, this->games[i].find(".so") - 11));
        game.push_back(tmp);
    }
    tmp.first = 0;
    tmp.second = "Your name:           ";
    name.push_back(tmp);
    this->bouton.push_back(lib);
    this->bouton.push_back(game);
    this->bouton.push_back(name);
}