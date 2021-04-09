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

Game::Game()
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
    std::pair<int, int> value;
    value.first = 20;
    value.second = 9;
    this->fpos.push_back(value);
    value.first = 22;
    value.second = 9;
    this->fpos.push_back(value);
    value.first = 26;
    value.second = 9;
    this->fpos.push_back(value);
    value.first = 28;
    value.second = 9;
    this->fpos.push_back(value);
    this->ppos.first = 24;
    this->ppos.second = 15;
    this->fdir.push_back(0);
    this->fdir.push_back(0);
    this->fdir.push_back(0);
    this->fdir.push_back(0);
    behind_ghost.push_back(' ');
    behind_ghost.push_back(' ');
    behind_ghost.push_back(' ');
    behind_ghost.push_back(' ');
    this->pdir = 0;
    this->score = 0;
    this->ghost = 0;
    gameLoop(glib);
}

void Game::gest_exit(IGraphicLib *glib, int input)
{
    if (input == 'q') {
        glib->exit_lib();
        exit(0);
    }
}

std::string str_replace_str(std::string str, std::string str2, std::string str3)
{
    size_t a = 0;
    size_t b = 0;
    int x = 0;
    std::string str4 = "";

    while (a != str.size()) {
        b = 0;
        if (str[a] == str2[0]) {
            while (b != str2.size()) {
                x++;
                if (str[a] != str2[b]) {
                    b = str2.size();
                    str4 = str4 + str2[0];
                    a = ((a - x) + 1);
                }
                else {
                    a++;
                    b++;
                    if (b == str2.size()) {
                        str4 = str4 + str3;
                        a = a - 1;
                    }
                }
            }
        }
        x = 0;
        if (b == 0)
            str4 = str4 + str[a];
        a++;
    }
    return str4;
}

void Game::gest_input(IGraphicLib *glib, int input, std::vector<std::string> map)
{
    if (input == 259) 
        this->pdir = 0;
    if (input == 261)
        this->pdir = 1;
    if (input == 258)
        this->pdir = 2;
    if (input == 260) 
        this->pdir = 3;
}

std::vector<std::string> Game::move_pac(IGraphicLib *glib, int input, std::vector<std::string> map)
{
    std::vector<std::string> map_temp = map;
    int w = 0;
    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "🌕", "P ");
        map_temp[i] = str_replace_str(map_temp[i], "👻", "F ");
        map_temp[i] = str_replace_str(map_temp[i], "👽", "K ");
        map_temp[i] = str_replace_str(map_temp[i], "🧟", "L ");
        map_temp[i] = str_replace_str(map_temp[i], "👹", "X ");
        map_temp[i] = str_replace_str(map_temp[i], "█", "W");
        map_temp[i] = str_replace_str(map_temp[i], "🍑", "* ");
    }
    if (this->pdir == 3 and this->ppos.first == 0) {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][48] = 'P';
        this->ppos.first = 48;
    } else if(this->pdir == 3 and map_temp[this->ppos.second][this->ppos.first - 2] == '*') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first - 2] = 'P';
        this->ppos.first = this->ppos.first - 2;
        map_temp[this->ppos.second][this->ppos.first - 2] == ' ';
        this->score = this->score + 1;
    } else if(this->pdir == 3 and map_temp[this->ppos.second][this->ppos.first - 2] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first - 2] = 'P';
        this->ppos.first = this->ppos.first - 2;
    }

    if (this->pdir == 0 and map_temp[this->ppos.second - 1][this->ppos.first] == '*' and map_temp[this->ppos.second - 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second - 1][this->ppos.first] = 'P';
        map_temp[this->ppos.second - 1][this->ppos.first] == ' ';
        this->ppos.second = this->ppos.second -1;
        this->score = this->score + 1;
    } else if(this->pdir == 0 and map_temp[this->ppos.second - 1][this->ppos.first] == ' ' and map_temp[this->ppos.second - 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second - 1][this->ppos.first] = 'P';
        this->ppos.second = this->ppos.second -1;
    }

    if (this->pdir == 1 and this->ppos.first >= 48) {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first + 1] = ' ';
        map_temp[this->ppos.second][0] = 'P';
        this->ppos.first = 0;
    } else if (this->pdir == 1 and map_temp[this->ppos.second][this->ppos.first + 2] == '*') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first + 2] = 'P';
        this->ppos.first = this->ppos.first + 2;
        map_temp[this->ppos.second][this->ppos.first + 2] == ' ';
        this->score = this->score + 1;
    } else if (this->pdir == 1 and map_temp[this->ppos.second][this->ppos.first + 2] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first + 2] = 'P';
        this->ppos.first = this->ppos.first + 2;
    }

    if (this->pdir == 2 and map_temp[this->ppos.second + 1][this->ppos.first] == '*' and map_temp[this->ppos.second + 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second + 1][this->ppos.first] = 'P';
        this->ppos.second = this->ppos.second + 1;
        map_temp[this->ppos.second + 1][this->ppos.first] == ' ';
        this->score = this->score + 1;
    } else if(this->pdir == 2 and map_temp[this->ppos.second + 1][this->ppos.first] == ' ' and map_temp[this->ppos.second + 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second + 1][this->ppos.first] = 'P';
        this->ppos.second = this->ppos.second + 1;
    }
    
    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "P ", "🌕");
        map_temp[i] = str_replace_str(map_temp[i], "F ", "👻");
        map_temp[i] = str_replace_str(map_temp[i], "K ", "👽");
        map_temp[i] = str_replace_str(map_temp[i], "L ", "🧟");
        map_temp[i] = str_replace_str(map_temp[i], "X ", "👹");
        map_temp[i] = str_replace_str(map_temp[i], "WW", "██");
        map_temp[i] = str_replace_str(map_temp[i], "* ", "🍑");
    }
    return map_temp;
}
std::vector<std::string> Game::move_ghost(IGraphicLib *glib, std::vector<std::string> map)
{
    std::vector<std::string> map_temp = map;
    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "🌕", "P ");
        map_temp[i] = str_replace_str(map_temp[i], "👻", "0 ");
        map_temp[i] = str_replace_str(map_temp[i], "👽", "1 ");
        map_temp[i] = str_replace_str(map_temp[i], "🧟", "2 ");
        map_temp[i] = str_replace_str(map_temp[i], "👹", "3 ");
        map_temp[i] = str_replace_str(map_temp[i], "█", "W");
        map_temp[i] = str_replace_str(map_temp[i], "🍑", "* ");
    }
    int v1 = 0;
    int a = 0;
    int w, x, y, z = 0;
    srand((unsigned int) time(0));
    while (a != 1) {
        v1 = rand() % 4;
        if (v1 == 0) {
            w = 1;
            if (map_temp[this->fpos[this->ghost].second - 1][this->fpos[this->ghost].first] == '*' and this->fdir[this->ghost] != 2) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second - 1][this->fpos[this->ghost].first] = this->ghost + 48;
                this->fdir[this->ghost] = 0;
                this->behind_ghost[this->ghost] = '*';
                this->fpos[this->ghost].second = this->fpos[this->ghost].second - 1;
                a = 1;
            } else if (map_temp[this->fpos[this->ghost].second - 1][this->fpos[this->ghost].first] == ' ' and this->fdir[this->ghost] != 2) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second - 1][this->fpos[this->ghost].first] = this->ghost + 48;
                this->fdir[this->ghost] = 0;
                this->behind_ghost[this->ghost] = ' ';
                this->fpos[this->ghost].second = this->fpos[this->ghost].second - 1;
                a = 1;
            } else if (x == 1 and y == 1 and z == 1) {
                this->fdir[this->ghost] = 0;
                a = 1;
            }
        }
        if (v1 == 1) {
            x = 1;
            if (this->fdir[this->ghost] == 3 and this->fpos[this->ghost].first >= 48)
                a = 1;
            else if (this->fdir[this->ghost] != 3 and this->fpos[this->ghost].first >= 48) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = ' ';
                map_temp[this->fpos[this->ghost].second][0] = this->ghost + 48;
                this->behind_ghost[this->ghost] = ' ';
                this->fpos[this->ghost].first = 0;
                this->fdir[this->ghost] = 1;
                a = 1;
            } else if (map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first + 2] == '*' and this->fdir[this->ghost] != 3) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first + 2] = this->ghost + 48;
                this->fdir[this->ghost] = 1;
                this->behind_ghost[this->ghost] = '*';
                this->fpos[this->ghost].first = this->fpos[this->ghost].first + 2;
                a = 1;
            } else if (map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first + 2] == ' ' and this->fdir[this->ghost] != 3) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first + 2] = this->ghost + 48;
                this->fdir[this->ghost] = 1;
                this->behind_ghost[this->ghost] = ' ';
                this->fpos[this->ghost].first = this->fpos[this->ghost].first + 2;
                a = 1;
            } else if (w == 1 and y == 1 and z == 1) {
                if (map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first -2] == '*' or map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first -2] == ' ')
                    this->fdir[this->ghost] = 1;
                a = 1;
            }
        }
        if (v1 == 2) {
            y = 1;
            if (map_temp[this->fpos[this->ghost].second + 1][this->fpos[this->ghost].first] == '*' and this->fdir[this->ghost] != 0) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second + 1][this->fpos[this->ghost].first] = this->ghost + 48;
                this->fdir[this->ghost] = 2;
                this->behind_ghost[this->ghost] = '*';
                this->fpos[this->ghost].second = this->fpos[this->ghost].second + 1;
                a = 1;
            } else if (map_temp[this->fpos[this->ghost].second + 1][this->fpos[this->ghost].first] == ' ' and this->fdir[this->ghost] != 0) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second + 1][this->fpos[this->ghost].first] = this->ghost + 48;
                this->fdir[this->ghost] = 2;
                this->behind_ghost[this->ghost] = ' ';
                this->fpos[this->ghost].second = this->fpos[this->ghost].second + 1;
                a = 1;
            } else if (w == 1 and x == 1 and z == 1) {
                if (map_temp[this->fpos[this->ghost].second - 1][this->fpos[this->ghost].first] == '*' or map_temp[this->fpos[this->ghost].second - 1][this->fpos[this->ghost].first] == ' ')
                this->fdir[this->ghost] = 2;
                a = 1;
            }
        }
        if (v1 == 3) {
            z = 1;
            if (this->fdir[this->ghost] == 1 and this->fpos[this->ghost].first == 0) {
                a = 1;
            }
            else if (this->fdir[this->ghost] != 1 and this->fpos[this->ghost].first == 0) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = ' ';
                map_temp[this->fpos[this->ghost].second][48] = this->ghost + 48;
                this->fpos[this->ghost].first = 48;
                this->behind_ghost[this->ghost] = ' ';
                this->fdir[this->ghost] = 3;
                a = 1;
            } else if (map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first -2] == '*' and this->fdir[this->ghost] != 1) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first -2] = this->ghost + 48;
                this->fdir[this->ghost] = 3;
                this->behind_ghost[this->ghost] = '*';
                this->fpos[this->ghost].first = this->fpos[this->ghost].first - 2;
                a = 1;
            } else if (map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first -2] == ' ' and this->fdir[this->ghost] != 1) {
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first] = this->behind_ghost[this->ghost];
                map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first -2] = this->ghost + 48;
                this->fdir[this->ghost] = 3;
                this->behind_ghost[this->ghost] = ' ';
                this->fpos[this->ghost].first = this->fpos[this->ghost].first - 2;
                a = 1;
            } else if (w == 1 and x == 1 and y == 1) {
                if (map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first + 2] == '*' or map_temp[this->fpos[this->ghost].second][this->fpos[this->ghost].first + 2] == ' ')  
                this->fdir[this->ghost] = 3;
                a = 1;
            }
        }
        if (w == 1 and x == 1 and y == 1 and z == 1)
            a = 1;
    }
    if (this->ghost == 3)
        this->ghost = 0;
    else
        this->ghost = this->ghost + 1;
    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "P ", "🌕");
        map_temp[i] = str_replace_str(map_temp[i], "0 ", "👻");
        map_temp[i] = str_replace_str(map_temp[i], "1 ", "👽");
        map_temp[i] = str_replace_str(map_temp[i], "2 ", "🧟");
        map_temp[i] = str_replace_str(map_temp[i], "3 ", "👹");
        map_temp[i] = str_replace_str(map_temp[i], "WW", "██");
        map_temp[i] = str_replace_str(map_temp[i], "* ", "🍑");
    }
    return map_temp;
}

int Game::gameLoop(IGraphicLib *glib)
{
    int input = -1;
    auto pmove = std::chrono::high_resolution_clock::now();
    auto refresh = std::chrono::high_resolution_clock::now();
    std::vector<std::string> map_menu = this->load_map("assets/pacman/maps/map.txt");
    std::string affich_score;
    while (1) {
        input = glib->keyPressed();
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - refresh).count() > 10000000) {
            glib->clearWindow();
            glib->printMap(map_menu);
            auto s = std::to_string(this->score);
            affich_score = "Score : " + s;
            glib->printSelectedButton(50, 0, affich_score);
            if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - pmove).count() > 150000000) {
                map_menu = move_pac(glib, input, map_menu);
                if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - pmove).count() > 1500000) {
                map_menu = move_ghost(glib, map_menu);
                }
                pmove = std::chrono::high_resolution_clock::now();
            }
            glib->refreshWindow();
            refresh = std::chrono::high_resolution_clock::now();
        }
        this->gest_exit(glib, input);
        this->gest_input(glib, input, map_menu);
    }
    (void)glib;
}
