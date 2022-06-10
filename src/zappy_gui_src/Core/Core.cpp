/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui_src/Core/Core.cpp

#include "Core.hpp"
#include <getopt.h>
#include <unistd.h>
#include "ZappyGuiException.hpp"

void Core::run()
{
    while (_sfml.isRunning())
        _sfml.display();
}

void Core::_getArgs(int ac, char **av)
{
    int opt = 0;

    if (ac < 3 || ac > 5)
        throw (CoreException("Core setup", "Invalid arguments number."));
    for (opt = getopt(ac, av, "ph:"); opt != -1; opt = getopt(ac, av, "ph")) {
        if (optind >= ac)
            throw (CoreException("Core setup", "Invalid argument"));
        switch (opt) {
            case 'p':
                _port = std::string(av[optind]);
                break;
            case 'h':
                _machine = av[optind];
                break;
            default:
                throw (CoreException("Core seupt", "Invalid argument"));
        }
    }
    if (_machine.empty())
        _machine = DEFAULT_MACHINE;
    if (_port.empty())
        throw (CoreException("Core setup", "Empty port. Please select port with the flag \"-p PORT\"."));
}

void Core::setup(int ac, char **av)
{
    _getArgs(ac, av);
}
