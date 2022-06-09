/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui/Core/Core.cpp

#include "Core.hpp"

void Core::run()
{
    /// Need to implement game loop
}

void Core::_getArgs(int ac, char **av)
{
    if (ac < 3 || ac > 5)
        throw (CoreException("Core setup", "Invalid arguments number."));
    for (int i = 1; i < ac; i++) {
        if (std::string(av[i]) == "-p") {
            if (i + 1 >= ac)
                throw (CoreException("Core setup", "Flag \"-p\" doesn't have argument."));
            if (!_port.empty())
                throw (CoreException("Core setup", "Flag \"-p\" already have argument."));
            _port = av[i + 1];
        }
        if (std::string(av[i]) == "-h") {
            if (!_machine.empty())
                throw (CoreException("Core setup", "Flag \"-h\" already have argument."));
            if (i + 1 >= ac && std::string(av[i + 1]) != "-h")
                _machine = "127.0.0.1";
            else
                _machine = av[i + 1];
        }
    }
}

void Core::setup(int ac, char **av)
{
    _getArgs(ac, av);
}
