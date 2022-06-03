/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** main
*/

/// \file main of GUI

#include "data_game.h"
#include "GameInfo.hpp"
#include <exception>
#include <iostream>
#include <string>

int main(int ac, char **av)
{
    if (ac < 3)
        std::cerr << "Not enough arguments" << std::endl;
    if (ac > 3)
        std::cerr << "Too many arguments" << std::endl;
    try {
        std::string machine(av[2]);
        gui::GameInfo info = gui::GameInfo(std::stoi(av[1]), machine);
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
