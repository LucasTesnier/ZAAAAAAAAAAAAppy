/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** launch_gui
*/

/// \file src/zappy_gui/launch_gui.cpp

#include <string>

int launch_gui(int ac, char **av)
{
    std::string port;
    std::string machine;

    if (ac != 4 && ac != 5)
        return 84;
    for (int i = 0; i < ac; i++) {
        if (std::string(av[i]) == "-p" && i + 1 < ac)
            port = av[i + 1];
        if (std::string(av[i]) == "-h" && i + 1 < ac)
            machine = av[i + 1];
    }
    if (port.empty())
        return 84;
    if (machine.empty())
        machine = "127.0.0.1";
    return 0;
}
