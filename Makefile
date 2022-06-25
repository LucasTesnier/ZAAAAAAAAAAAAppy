##
## EPITECH PROJECT, 2022
## ZAPPYMIRROR
## File description:
## Makefile
##

all:
	cmake -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
	cmake --build ./build

clean:
	make clean -C ./build

fclean: clean
	rm -rf zappy_server
	rm -rf zappy_ai
	rm -rf zappy_gui
	rm -rf build

re: all clean
	make

.PHONY: all clean fclean re
