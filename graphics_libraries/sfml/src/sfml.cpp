/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "sfml.hpp"

extern "C"
{
    SfmlLib *MakeGraphicLib()
    {
        return new SfmlLib();
    }
}

void SfmlLib::init_lib()
{
    this->_window.create(sf::VideoMode(1920, 1080), "My window");
    this->block_size = 16;
}

void SfmlLib::exit_lib()
{
    this->_window.close();
}

int SfmlLib::keyPressed()
{
    sf::Event event;
    if (this->_window.pollEvent(event) == false)
        return -1;
    if (event.type == sf::Event::KeyPressed) {
        if (event.type == sf::Event::Closed)
            return 'q';
        if (event.key.code == sf::Keyboard::Up)
            return 259;
        if (event.key.code == sf::Keyboard::Down)
            return 258;
        if (event.key.code == sf::Keyboard::Right)
            return 261;
        if (event.key.code == sf::Keyboard::Left)
            return 260;
        if (event.key.code == sf::Keyboard::BackSpace)
            return 263;
    }
    if (event.key.code == sf::Keyboard::Up || 
        event.key.code == sf::Keyboard::Down || 
        event.key.code == sf::Keyboard::Right || 
        event.key.code == sf::Keyboard::Left || 
        event.key.code == sf::Keyboard::BackSpace)
        return -1;
    return event.key.code;
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

void SfmlLib::printMap(std::vector<std::string> vs)
{
    int x = 0;
    int y = 0;
    std::string tmp = "";
    std::string tmp2 = "";
    std::string spe_char = "0";
    SDL_Texture *tex = NULL;
    std::string path = "";
    sf::Texture texture;
    sf::Sprite sprite;
    
    for (int i = 0; i != vs.size(); i++) {
        for (auto m = this->sprite.begin() ; m != this->sprite.end() ; m++) {
            vs[i] = str_replace_str(vs[i], m->first, spe_char);
            spe_char[0]++;
        }
        spe_char = "0";
        std::string test = "┃";
        for (auto m = this->sprite.begin() ; m != this->sprite.end() ; m++) {
           for (int h = 0 ; h != vs[i].size() ; h++, tmp = "") {
                if (vs[i][h] == spe_char[0]) {
                    tmp += m->first;
                    sprite.setScale(0.64, 0.64);
                    sprite.setTexture(m->second);
                    sprite.setPosition(x, y);
                    this->_window.draw(sprite);
                }
                x = x + this->block_size;
            }
            x = 0;
            spe_char[0]++;
        }
        spe_char = "0";
        y = y + this->block_size;
    }
    this->_window.display();
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

void SfmlLib::printOneSprite(int x, int y, sf::Texture texture)
{
    sf::Sprite sprite;
    sprite.setScale(0.64, 0.64);
    sprite.setTexture(this->bouton_sprite["clear"]);
    sprite.setPosition(x * this->block_size, y * this->block_size);
    this->_window.draw(sprite);
    
    sprite.setScale(0.64, 0.64);
    sprite.setTexture(texture);
    sprite.setPosition(x * this->block_size, y * this->block_size);
    this->_window.draw(sprite);
}

void SfmlLib::printSelectedButton(int x, int y, std::string text)
{
    size_t len = strlen_emoji(text);

    this->printOneSprite(x, y, this->bouton_sprite["┏"]);
    this->printOneSprite(x, y + 2, this->bouton_sprite["┗"]);
    this->printOneSprite(x + (int)len + 3, y, this->bouton_sprite["┓"]);
    this->printOneSprite(x + (int)len + 3, y + 2, this->bouton_sprite["┛"]);
    this->printOneSprite(x + (int)len + 3, y + 1, this->bouton_sprite["┇"]);
    this->printOneSprite(x, y + 1, this->bouton_sprite["┇"]);

    for (size_t i = 0 ; i != len + 2 ; i++) {
        this->printOneSprite(x + (int)i + 1, y + 2, this->bouton_sprite["┅"]);
        this->printOneSprite(x + (int)i + 1, y, this->bouton_sprite["┅"]);
    }
    printText(x + 2, y + 1, text);
}

void SfmlLib::printButton(int x, int y, std::string text)
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
    printText(x + 2, y + 1, text);
}


std::string SfmlLib::clean_emoji(std::string str)
{
    for (auto m = this->emoji.begin() ; m != this->emoji.end() ; m++)
        str = str_replace_str(str, m->first, m->second);
    return str;
}
    
void SfmlLib::printText(int x, int y, std::string string)
{
    std::string str;
    if (this->text.find(string) == this->text.end())
        str = clean_emoji(string).c_str();
    sf::Text text;
    text.setFont(this->MyFont);
    text.setString(str);
    text.setCharacterSize(this->block_size);
    text.setColor(sf::Color::White);
    text.setPosition(x *this->block_size, y * this->block_size - 2);
    this->_window.draw(text);
}

void SfmlLib::clearWindow()
{

}

void SfmlLib::refreshWindow()
{
    this->_window.display();
}
void SfmlLib::printWindow()
{
    this->_window.display();
}

void SfmlLib::printTitle(std::string text)
{
}

std::pair<int, int> SfmlLib::getWindowSize() const
{

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

void SfmlLib::assetLoader(const std::string str)
{
    std::string tmp = "";
    std::string tmp2 = "";
    std::string font = str + "/font";
    sf::Font MyFoont;
    DIR *rep = opendir(font.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".ttf") != NULL) {
                tmp = str + "/font/" + ent->d_name;
                MyFoont.loadFromFile(tmp);
                this->MyFont = MyFoont;
                tmp = "";
                break;
            }
        }
    }
    closedir(rep);
    tmp = "";
    sf::Texture texture;
    tmp2 = "";
    std::string tex = str + "/sprites";
    rep = opendir(tex.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".png") != NULL) {
                tmp = str + "/sprites/" + ent->d_name;
                tmp2 += begin_str(ent->d_name, '.');
                texture.loadFromFile(tmp.c_str());
                this->sprite[tmp2] = texture;
                texture = sf::Texture();
            }
            tmp = "";
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
    tex = "assets/sdl2/sprites";
    rep = opendir(tex.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        tmp = "assets/sdl2/sprites/";
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".png") != NULL) {
                tmp += ent->d_name;
                tmp2 += begin_str(ent->d_name, '.');
                texture.loadFromFile(tmp.c_str());
                this->bouton_sprite[tmp2] = texture;
            }
            tmp = "assets/sdl2/sprites/";
            tmp2 = "";
        }
    }
    closedir(rep);
}