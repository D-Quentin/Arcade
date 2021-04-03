/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** sfml
*/

#ifndef sfml_HPP_
#define sfml_HPP_

#include "IGraphicLib.hpp"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System/Export.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include <SFML/Config.h>
#include <SFML/Window/Export.h>

class Smfl : public IGraphicLib
{
    public:
        virtual void init_lib();
        virtual void exit_lib();
        virtual int keyPressed();
        virtual void printMap(std::vector<std::string>);
        virtual void printButton(int x, int y, std::string);
        virtual void printSelectedButton(int x, int y, std::string);
        virtual void printText(int x, int y, std::string);
        virtual void clearWindow();
        virtual void refreshWindow();
        virtual void printWindow();
        virtual void printTitle(std::string);
        virtual std::pair<int, int> getWindowSize() const;
        virtual void assetLoader(const std::string);
    protected:
    private:
};

#endif /* !sfml_HPP_ */
