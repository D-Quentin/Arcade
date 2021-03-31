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

void sdl2Lib::printMap(std::vector<std::string> vs)
{
    int x = 0;
    int y = 0;
    std::map<std::string, SDL_Texture *> texture;

    for (auto i = this->sprite.begin() ; i != this->sprite.end() ; i++)
        texture[i->first] = SDL_CreateTextureFromSurface(renderer, i->second);

    SDL_Rect dstrect = {x, y, 19, 19};
    std::string tmp = "";
    for (int i = 0; i != vs.size(); i++) {
        for (int h = 0 ; h != vs[i].size() ; h++, tmp = "") {
            tmp +=vs[i][h];
            dstrect = {x, y, 19, 19};
            SDL_RenderCopy(renderer, texture[tmp], NULL, &dstrect);
            x = x + 19;
        }
        y = y + 19;
        x = 0;
    }
    SDL_RenderPresent(renderer);
}

void sdl2Lib::printButton(int x, int y, std::string text)
{
    /*
    printText(x, y, text);
    SDL_Surface *image = IMG_Load("cadre_gauche.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dstrect = {x - 10, y - 10, 10, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    image = IMG_Load("cadre_milieu.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);
    dstrect = {x, y - 10, text.size() * 2, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    image = IMG_Load("cadre_droite.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);
    dstrect = {text.size() * 2, y - 10, 10, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    */
}

void sdl2Lib::printSelectedButton(int x, int y, std::string)
{

}

void sdl2Lib::printText(int x, int y, std::string text)
{
    SDL_Color color = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderUTF8_Blended(TTF_OpenFont(this->font.c_str(), 19), text.c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    int a = 0;
    int b = 0;
    SDL_QueryTexture(texture, NULL, NULL, &a, &b);
    SDL_Rect dstrect = {x * 19, y * 19, a, b};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
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
                tmp2 += ent->d_name[0];
                this->font = tmp;
                tmp = "";
                tmp2 = "";
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
                tmp2 += ent->d_name[0];
                sprite[tmp2] = IMG_Load(tmp.c_str());
            }
            std::cout << tmp << std::endl;
            tmp = "";
            tmp2 = "";
        }
    }
    closedir(rep);
}