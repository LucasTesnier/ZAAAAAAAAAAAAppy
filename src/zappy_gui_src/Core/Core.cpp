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
#include <string>
#include <netdb.h>
#include <arpa/inet.h>

using namespace gui;

/// \brief The default value for the machine if it's not specify.
static const char *DEFAULT_MACHINE = "localhost";

void Core::run()
{
    int fps = 0;
    sf::Clock clock;

    while (_sfml->isRunning()) {
        _sfml->display();
        if (clock.getElapsedTime().asSeconds() >= 1) {
            clock.restart();
            fps = 0;
        }
        fps++;
        if (!c_interface_get_response_state())
            continue;
        if (!c_interface_get_unexpected_response_state())
            continue;
        std::cout << "Get : " << c_interface_get_unexpected_response() << std::endl;
    }
}

void Core::_resolveMachineHostname()
{
    hostent* hostname = gethostbyname(_machine.c_str());
    if(hostname)
        _machine = std::string(inet_ntoa(**(in_addr**)hostname->h_addr_list));
    // _machine = "127.0.0.1";
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
    if (_machine.empty()) {
        _machine = std::string(DEFAULT_MACHINE);
        std::cout << "machine empty: " << _machine << std::endl;
    }
    if (_port.empty())
        throw (CoreException("Core setup", "Empty port. Please select port with the flag \"-p PORT\"."));
    _resolveMachineHostname();
}

void Core::setup(int ac, char **av)
{
    char *str;

    _getArgs(ac, av);
    str = (char *)_machine.c_str();
    std::cout << "str: " << str << std::endl;
    if (!c_interface_try_to_connect_to_server(str, std::atoi(_port.c_str())))
        throw (CoreException("Core setup", "Unable to connect to the server"));
    while(!c_interface_get_response_state());
    if (!c_interface_get_unexpected_response_state())
        throw (CoreException("Core setup", "Invalid receive data"));
    std::string temp = std::string(c_interface_get_unexpected_response());
    _unpackObject.UnpackEntity(_startData, temp);
    const sf::Vector2f mapSize = {(float)_startData.size_x, (float)_startData.size_y};
    _sfml = std::make_unique<gui::SFML>(mapSize);
}

Core::Core()
{
    _unpackObject = gui::unpack::Unpack();
}

Core::~Core()
{
    if (c_interface_get_network_state()) {
        std::cout << "try to disconnect" << std::endl;
        c_interface_try_to_disconnect_to_server();
    }
}
