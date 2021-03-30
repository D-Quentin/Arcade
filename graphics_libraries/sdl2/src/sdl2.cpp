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
    int h = 0;
    int x = 0;
    int y = 0;
    SDL_Surface * image = NULL;
    SDL_Texture * texture = NULL;
    SDL_Rect dstrect = {x, y, 40, 40};
    for (int i = 0; i != vs.size(); i++) {
        while (h != vs[i].size()) {
            if (vs[i][h] == ' ') {
                image = IMG_Load("Chloe-la-petite-fille-devenue-un-meme-en-2013-a-bien-grandi.jpg");
            }
            texture = SDL_CreateTextureFromSurface(renderer, image);
            dstrect = {x, y, 40, 40};
            SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            x = x + 40;
            h++;
        }
        h = 0;
        y = y + 40;
        x = 0;
    }
}

void sdl2Lib::printButton(int x, int y, std::string text)
{
    printText(x, y, text);
    SDL_Surface *image = IMG_Load("cadre_gauche.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dstrect = {x - 10, y - 10, 10, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_Surface *image = IMG_Load("cadre_milieu.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dstrect = {x, y - 10, text.size() * 2, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_Surface *image = IMG_Load("cadre_droite.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dstrect = {text.size() * 2, y - 10, 10, 40};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    
}

void sdl2Lib::printSelectedButton(int x, int y, std::string)
{

}

void sdl2Lib::printText(int x, int y, std::string text)
{
    TTF_Font *font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color color = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    int a = 0;
    int b = 0;
    SDL_QueryTexture(texture, NULL, NULL, &a, &b);
    SDL_Rect dstrect = {x, y, a, b};
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
void sdl2Lib::assetLoader(const std::string)
{
    
}