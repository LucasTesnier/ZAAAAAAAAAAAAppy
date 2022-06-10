/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main
*/

/// \file src/zappy_gui_src/main.cpp

#include "ZappyGuiException.hpp"
#include "Core.hpp"
#include <iostream>
#include <string>

static int usage(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help")) {
        std::cerr << "USAGE: ./zappy_ai -p port -h machine\n\tport\t is the port number\n\tmachine\t is the name of the machine; localhost by default" << std::endl;
        return -1;
    }
    return 0;
}

int main(int ac, char **av)
{
    Core core;

    if (usage(ac, av) < 0)
        return 84;
    try {
        core.setup(ac, av);
    } catch (CoreException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    try {
        core.run();
    } catch (CoreException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
