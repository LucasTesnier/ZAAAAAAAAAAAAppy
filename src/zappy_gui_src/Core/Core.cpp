/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui_src/Core/Core.cpp

#include "ZappyGuiException.hpp"
#include "Core.hpp"
#include <getopt.h>
#include <unistd.h>
#include <netdb.h>

#include <time.h>

using namespace gui;

/// \brief The default value for the machine if it's not specify.
static const char *DEFAULT_MACHINE = "localhost";

void Core::run()
{
    int fps = 0;
    sf::Clock clock;

    while (_sfml.isRunning()) {
        _sfml.display();
        if (clock.getElapsedTime().asSeconds() >= 1) {
            clock.restart();
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
        }
        fps++;
    }
}

void Core::_resolveMachineHostname()
{
    hostent *host = gethostbyname2(_machine.c_str(), AF_INET);

    if (host)
        _machine = std::string(host->h_addr_list[0]);
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
                throw (CoreException("Core setup", "Invalid argument"));
        }
    }
    if (_machine.empty())
        _machine = DEFAULT_MACHINE;
    if (_port.empty())
        throw (CoreException("Core setup", "Empty port. Please select port with the flag \"-p PORT\"."));
    _resolveMachineHostname();
}

void Core::setup(int ac, char **av)
{
    _getArgs(ac, av);
}
