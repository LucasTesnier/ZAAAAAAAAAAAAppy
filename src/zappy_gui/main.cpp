/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main
*/

/// \file src/zappy_gui/main.cpp

#include <iostream>
#include <string>

int launch_gui(int ac, char **av);

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help")) {
        std::cerr << "USAGE: ./zappy_ai -p port -h machine" <<
        std::endl << "\tport\t is the port number" <<std::endl <<
        "\tmachine\t is the name of the machine; localhost by default" <<
        std::endl;
        return 84;
    }
    return launch_gui(ac, av);
}
