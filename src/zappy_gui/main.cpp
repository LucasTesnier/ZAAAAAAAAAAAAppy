/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main
*/

/// \file src/zappy_gui/main.cpp

#include "Core.hpp"
#include <iostream>
#include <string>

int main(int ac, char **av)
{
    Core core;

    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help")) {
        std::cerr << "USAGE: ./zappy_ai -p port -h machine" <<
        std::endl << "\tport\t is the port number" <<std::endl <<
        "\tmachine\t is the name of the machine; localhost by default" <<
        std::endl;
        return 84;
    }
    try {
        core.setup(ac, av);
    } catch (Core::CoreException &e) {
        std::cout << "Core setup failed" << std::endl;
    }
    try {
        core.run();
    } catch (Core::CoreException &e) {
        std::cout << "Core run failed" << std::endl;
    }
    return 0;
}
