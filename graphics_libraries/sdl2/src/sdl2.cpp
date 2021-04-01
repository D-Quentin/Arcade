/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "sdl2.hpp"

extern "C"
{
    sdl2Lib *MakeGraphicLib()
    {
        return new sdl2Lib();
    }
}

void sdl2Lib::init_lib()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    this->win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_FULLSCREEN);
    this->renderer = SDL_CreateRenderer(this->win, -1, 0);
    this->block_size = 16;
}

void sdl2Lib::exit_lib()
{
    SDL_DestroyWindow(this->win);
    SDL_Quit();
    TTF_Quit();
}

int sdl2Lib::keyPressed() const
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.key.keysym.scancode) {
        case 82:
            return 403;
        case 79:
            return 405;
        case 81:
            return 402;
        case 80:
            return 404;                                                                                                                                        
        default:
            return event.key.keysym.scancode;
            }
        }
}

std::string str_replace_str(std::string str, std::string str2, std::string str3)
{
    int a = 0;
    int b = 0;
    int c = 0;
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

void sdl2Lib::printMap(std::vector<std::string> vs)
{
    int x = 0;
    int y = 0;
    std::map<std::string, SDL_Texture *> texture;
    SDL_Rect dstrect = {x, y, this->block_size, this->block_size};
    std::string tmp = "";
    std::string tmp2 = "";
    std::string spe_char = "0";
    SDL_Texture *tex = NULL;

    for (int i = 0; i != vs.size(); i++) {
        for (auto m = this->sprite.begin() ; m != this->sprite.end() ; m++) {
            tmp2 = str_replace_str(vs[i], m->first, spe_char);
            // std::cout << "Char : " << m->first << std::endl;
            // std::cout << "Replace char : " << spe_char << std::endl;
            // std::cout << "Avant : " << vs[i];
            // std::cout << "Après : " << tmp2;
            // std::cout << "Path tex : " << m->second << std::endl;

            for (int h = 0 ; h != tmp2.size() ; h++, tmp = "") {
                if (tmp2[h] == spe_char[0]) {
                    tmp += m->first;
                    dstrect = {x, y, this->block_size, this->block_size};
                    tex = SDL_CreateTextureFromSurface(renderer, m->second);
                    SDL_RenderCopy(renderer, tex, NULL, &dstrect);
                    SDL_DestroyTexture(tex);
                }
                x = x + this->block_size;
            }
            x = 0;
            spe_char[0]++;
        }
        spe_char = "0";
        y = y + this->block_size;
    }
    SDL_RenderPresent(renderer);
}
std::string begin_str(std::string str, char a)
{
    int b = 0;
    std::string str2;
    int c = 0;

    while (b != str.size()) {
        if (str[b] == a)
            break;
        b++;
    }
    while (c != b) {
        str2 = str2 + str[c];
        c++;
    }
    return str2;
}

void sdl2Lib::printButton(int x, int y, std::string text)
{
    printText(x, y, text);
    SDL_Surface *image = IMG_Load("cadre_gauche.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dstrect = {x - 10, y - 10, 10, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    image = IMG_Load("cadre_milieu.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);
    dstrect = {x, y - 10, (int)text.size() * 2, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    image = IMG_Load("cadre_droite.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);
    dstrect = {(int)text.size() * 2, y - 10, 10, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
}

void sdl2Lib::printSelectedButton(int x, int y, std::string)
{

}

void sdl2Lib::printText(int x, int y, std::string string)
{
    SDL_Color color = {255, 255, 255, 255};
    if (this->text.find(string) == this->text.end())
        this->text[string] = TTF_RenderText_Solid(TTF_OpenFont(this->font.c_str(), this->block_size), string.c_str(), color);

    SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, this->text[string]);
    int a = 0;
    int b = 0;
    SDL_QueryTexture(texture, NULL, NULL, &a, &b);
    SDL_Rect dstrect = {x * this->block_size, y * this->block_size, a, b};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

void sdl2Lib::clearWindow()
{
    SDL_RenderClear(this->renderer);
}

void sdl2Lib::refreshWindow()
{

}
void sdl2Lib::printWindow()
{

}
void sdl2Lib::printTitle(std::string)
{

}
std::pair<int, int> sdl2Lib::getWindowSize() const
{

}
void sdl2Lib::assetLoader(const std::string str)
{
    std::string tmp = "";
    std::string tmp2 = "";
    std::string font = str + "/font";
    DIR *rep = opendir(font.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".ttf") != NULL) {
                tmp = str + "/font/" + ent->d_name;
                this->font = tmp;
                tmp = "";
                break;
            }
        }
    }
    closedir(rep);
    std::string tex = str + "/sprites";
    rep = opendir(tex.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".png") != NULL) {
                tmp = str + "/sprites/" + ent->d_name;
                tmp2 += begin_str(ent->d_name, '.');
                sprite[tmp2] = IMG_Load(tmp.c_str());
            }
            std::cout << tmp2 << std::endl;
            tmp = "";
            tmp2 = "";
        }
    }
    closedir(rep);
}