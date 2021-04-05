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
    this->input_time = std::chrono::high_resolution_clock::now();
    this->clearWindow();
}

void sdl2Lib::exit_lib()
{
    this->clearWindow();
    SDL_DestroyWindow(this->win);
    SDL_Quit();
    TTF_Quit();
}

int sdl2Lib::keyPressed()
{
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event)) {
        if (keys[SDL_SCANCODE_BACKSPACE])
            return 263;
        if (keys[SDL_SCANCODE_DOWN])
            return 258;
        if (keys[SDL_SCANCODE_UP])
            return 259;
        if (keys[SDL_SCANCODE_LEFT])
            return 260;
        if (keys[SDL_SCANCODE_RIGHT])
            return 261;
        if (keys[SDL_SCANCODE_RETURN])
            return 10;
        if (event.key.keysym.scancode >= 'a' && event.key.keysym.scancode <= 'z')
            return event.key.keysym.scancode;
        return -1;
    }
    return (-1);
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
            vs[i] = str_replace_str(vs[i], m->first, spe_char);
            spe_char[0]++;
        }
        spe_char = "0";
        for (auto m = this->sprite.begin() ; m != this->sprite.end() ; m++) {
            for (int h = 0 ; h != vs[i].size() ; h++, tmp = "") {
                if (vs[i][h] == spe_char[0]) {
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

int str_in_str(std::string str, std::string str2)
{
    int a = 0;
    int b = 0;
    int c = 0;
    int result = 0;

    while (a != str.size()) {
        if (str[a] == str2[0]) {
            b = 0;
            c = a;
            while (b != str2.size()) {
                if (str[c] != str2[b])
                    b = str2.size();
                else {
                    c++;
                    b++;
                    if (b == str2.size())
                        result++;
                }
            }
        }
        a++;
    }
    return result;
}

size_t strlen_emoji(const std::string& str)
{
    size_t length = 0;
    size_t emoji = 0;

    for (size_t i = 0 ; i != str.length() ; i++) {
        if ((str[i] & 0xC0) != 0x80) {
            length++;
        }
    }
    emoji += str_in_str(str, "🐍");
    emoji += str_in_str(str, "👻");
    return (length + emoji);
}

void sdl2Lib::printOneSprite(int x, int y, SDL_Surface *surface)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, this->bouton_sprite["clear"]);
    SDL_Rect dstrect = {x * this->block_size, y * this->block_size, this->block_size, this->block_size};
    SDL_RenderCopy(this->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_RenderCopy(this->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}

void sdl2Lib::printSelectedButton(int x, int y, std::string text)
{
    size_t len = strlen_emoji(text);

    this->printOneSprite(x, y, this->bouton_sprite["┏"]);
    this->printOneSprite(x, y + 2, this->bouton_sprite["┗"]);
    this->printOneSprite(x + (int)len + 3, y, this->bouton_sprite["┓"]);
    this->printOneSprite(x + (int)len + 3, y + 2, this->bouton_sprite["┛"]);
    this->printOneSprite(x + (int)len + 3, y + 1, this->bouton_sprite["┃"]);
    this->printOneSprite(x, y + 1, this->bouton_sprite["┃"]);

    for (size_t i = 0 ; i != len + 2 ; i++) {
        this->printOneSprite(x + (int)i + 1, y + 2, this->bouton_sprite["━"]);
        this->printOneSprite(x + (int)i + 1, y, this->bouton_sprite["━"]);
    }
    SDL_RenderPresent(renderer);
    printText(x + 2, y + 1, text);
}

void sdl2Lib::printButton(int x, int y, std::string text)
{
    size_t len = strlen_emoji(text);

    this->printOneSprite(x, y, this->bouton_sprite["┌"]);
    this->printOneSprite(x, y + 2, this->bouton_sprite["└"]);
    this->printOneSprite(x + (int)len + 3, y, this->bouton_sprite["┐"]);
    this->printOneSprite(x + (int)len + 3, y + 2, this->bouton_sprite["┘"]);
    this->printOneSprite(x + (int)len + 3, y + 1, this->bouton_sprite["┆"]);
    this->printOneSprite(x, y + 1, this->bouton_sprite["┆"]);

    for (size_t i = 0 ; i != len + 2 ; i++) {
        this->printOneSprite(x + (int)i + 1, y + 2, this->bouton_sprite["┄"]);
        this->printOneSprite(x + (int)i + 1, y, this->bouton_sprite["┄"]);
    }
    SDL_RenderPresent(renderer);
    printText(x + 2, y + 1, text);
}


std::string sdl2Lib::clean_emoji(std::string str)
{
    for (auto m = this->emoji.begin() ; m != this->emoji.end() ; m++)
        str = str_replace_str(str, m->first, m->second);
    return str;
}

void sdl2Lib::printText(int x, int y, std::string string)
{
    SDL_Color color = {255, 255, 255, 255};
    if (this->text.find(string) == this->text.end())
        this->text[string] = TTF_RenderText_Solid(TTF_OpenFont(this->font.c_str(), this->block_size + 2), clean_emoji(string).c_str(), color);
    
    SDL_Texture *tex_clear = SDL_CreateTextureFromSurface(this->renderer, this->bouton_sprite["clear"]);
    SDL_Rect dstrect_clear = {x * this->block_size, y * this->block_size, this->block_size * clean_emoji(string).size(), this->block_size};
    SDL_RenderCopy(this->renderer, tex_clear, NULL, &dstrect_clear);
    SDL_DestroyTexture(tex_clear);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, this->text[string]);
    int a = 0;
    int b = 0;
    SDL_QueryTexture(texture, NULL, NULL, &a, &b);
    SDL_Rect dstrect = {x * this->block_size, y * this->block_size - 3, a, b};
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
                this->sprite[tmp2] = IMG_Load(tmp.c_str());
            }
            tmp = "";
            tmp2 = "";
        }
    }
    closedir(rep);
    tex = "assets/sdl2/sprites";
    rep = opendir(tex.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        tmp = "assets/sdl2/sprites/";
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".png") != NULL) {
                tmp += ent->d_name;
                tmp2 += begin_str(ent->d_name, '.');
                this->bouton_sprite[tmp2] = IMG_Load(tmp.c_str());
            }
            tmp = "assets/sdl2/sprites/";
            tmp2 = "";
        }
    }
    closedir(rep);

    std::ifstream file(str + "/emoji");
    tmp = "";
    char c;
    std::string line = "";

    if (file) {
        while (file.get(c)) {
            if (c == '=') {
                tmp += line;
                line = "";
                continue;
            }
            if (c == '\n') {
                this->emoji[tmp] = line;
                line = "";
                tmp = "";
                continue;
            }
            line += c;
        }
    }
}