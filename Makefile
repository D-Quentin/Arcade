##
## EPITECH PROJECT, 2021
## B-OOP-400-PAR-4-1-arcade-alexis.thomas
## File description:
## Makefile
##

all:
		make core
		make games
		make graphicals

core:
		rm -f arcade
		cd _build/arcade && cmake .
		cd _build/arcade && make
		cp _build/arcade/arcade .

games:
		rm -f lib/arcade_centipede.so
		cd _build/games/centipede && cmake .
		cd _build/games/centipede && make
		cp _build/games/centipede/libcentipede.so lib/arcade_centipede.so

		rm -f lib/arcade_pacman.so
		cd _build/games/pacman && cmake .
		cd _build/games/pacman && make
		cp _build/games/pacman/libpacman.so lib/arcade_pacman.so

graphicals:
		rm -f lib/arcade_ncurses.so
		cd _build/graphics_libraries/ncurses && cmake .
		cd _build/graphics_libraries/ncurses && make
		cp _build/graphics_libraries/ncurses/libncurses.so lib/arcade_ncurses.so

		rm -f lib/arcade_opengl.so
		cd _build/graphics_libraries/opengl && cmake .
		cd _build/graphics_libraries/opengl && make
		cp _build/graphics_libraries/opengl/libopengl.so lib/arcade_opengl.so

		rm -f lib/arcade_sdl2.so
		cd _build/graphics_libraries/sdl2 && cmake .
		cd _build/graphics_libraries/sdl2 && make
		cp _build/graphics_libraries/sdl2/libsdl2.so lib/arcade_sdl2.so

clean:
		rm -f _build/arcade/arcade
		rm -f _build/arcade/Makefile

		rm -f _build/games/centipede/libcentipede.so
		rm -f _build/games/centipede/Makefile

		rm -f _build/games/pacman/libpacman.so
		rm -f _build/games/pacman/Makefile

		rm -f _build/graphics_libraries/ncurses/libncurses.so
		rm -f _build/graphics_libraries/ncurses/Makefile

		rm -f _build/graphics_libraries/opengl/libopengl.so
		rm -f _build/graphics_libraries/opengl/Makefile

		rm -f _build/graphics_libraries/sdl2/libsdl2.so
		rm -f _build/graphics_libraries/sdl2/Makefile


fclean: clean
		rm -f arcade
		rm -rf _build/arcade/CMakeFiles
		rm -f _build/arcade/CMakeCache.txt
		rm -f _build/arcade/cmake_install.cmake

		rm -f lib/arcade_centipede.so
		rm -rf _build/games/centipede/CMakeFiles
		rm -f _build/games/centipede/CMakeCache.txt
		rm -f _build/games/centipede/cmake_install.cmake

		rm -f lib/arcade_pacman.so
		rm -rf _build/games/pacman/CMakeFiles
		rm -f _build/games/pacman/CMakeCache.txt
		rm -f _build/games/pacman/cmake_install.cmake

		rm -f lib/arcade_ncurses.so
		rm -rf _build/graphics_libraries/ncurses/CMakeFiles
		rm -f _build/graphics_libraries/ncurses/CMakeCache.txt
		rm -f _build/graphics_libraries/ncurses/cmake_install.cmake

		rm -f lib/arcade_opengl.so
		rm -rf _build/graphics_libraries/opengl/CMakeFiles
		rm -f _build/graphics_libraries/opengl/CMakeCache.txt
		rm -f _build/graphics_libraries/opengl/cmake_install.cmake

		rm -f lib/arcade_sdl2.so
		rm -rf _build/graphics_libraries/sdl2/CMakeFiles
		rm -f _build/graphics_libraries/sdl2/CMakeCache.txt
		rm -f _build/graphics_libraries/sdl2/cmake_install.cmake

re:		fclean
		make

.PHONY:	all clean fclean re games graphicals core