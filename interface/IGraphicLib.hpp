/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** IGraphicLib
*/

#ifndef IGraphicLib_HPP_
#define IGraphicLib_HPP_

class IGraphicLib {
    public:
        virtual ~IGraphicLib() = default;
        virtual void init_lib() = 0;
        virtual void exit_lib() = 0;

    protected:
    private:
};

typedef IGraphicLib *(*MakerLib)();

#endif /* !IGraphicLib_HPP_ */
