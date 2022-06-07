/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** main
*/

/// \file src/zappy_gui/main.cpp


#include "data_game.h"
#include "GameInfo.hpp"
#include "Exception.hpp"
#include <exception>
#include <iostream>
#include <string>

void check_ac(int ac)
{
    if (ac != 3)
        throw gui::ErrorArgs("Wrong number of arguments, Must be only 2.", "main: " + std::to_string(ac));
}

int main(int ac, char **av)
{
    try {
        check_ac(ac);
        std::string machine(av[2]);
        gui::GameInfo info = gui::GameInfo(std::stoi(av[1]), machine);
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
