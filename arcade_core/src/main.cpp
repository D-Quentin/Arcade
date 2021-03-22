/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "arcade.hpp"

IGraphicLib *open_lib(char *lib_name)
{
    MakerLib pMaker;
    void *handle = dlopen(lib_name, RTLD_LAZY);
    if(handle == NULL) {
        std::cerr << "dlopen : "<< dlerror() << std::endl; 
        std::exit(84);
    }
    void *mkr = dlsym(handle, "MakeGraphicLib");
    IGraphicLib *lib = NULL;
    if (mkr == NULL) {
        std::cerr << "dlsym : " << dlerror() << std::endl;
        std::exit(84);
    }
    pMaker = (MakerLib)mkr;
    lib = pMaker();
    return (lib);
}

int main(int ac, char **av)
{
    IGraphicLib *lib = NULL;
    if (ac != 2)
        return (84);
    lib = open_lib(av[1]);
    if (lib == NULL)
        return (84);
    
    return (0);
}