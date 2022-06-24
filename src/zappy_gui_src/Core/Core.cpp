/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui_src/Core/Core.cpp

#include "ZappyGuiException.hpp"
#include "Entity.hpp"
#include "Core.hpp"
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>

using namespace gui;

/// \brief The default value for the machine if it's not specify.
static const char *DEFAULT_MACHINE = "localhost";

std::vector<std::string> Core::_stringToVector(std::string text, std::string delim)
{
    std::vector<std::string> vec;
    size_t pos = 0;
    size_t prevPos = 0;

    while (1) {
        pos = text.find(delim, prevPos);
        if (pos == std::string::npos) {
            vec.push_back(text.substr(prevPos));
            return vec;
        }
        vec.push_back(text.substr(prevPos, pos - prevPos));
        prevPos = pos + delim.length();
    }
}

void Core::run()
{
    std::string response;

    while (_sfml->isRunning()) {
        _sfml->display();
        if (!c_interface_get_response_state())
            continue;
        if (!c_interface_get_unexpected_response_state())
            continue;
        response = std::string(c_interface_get_unexpected_response());
        _updateEntities(response);
    }
}

void Core::_removeEntities(std::string &type)
{
    _sfml->removeEntities(type);
}

void Core::_resolveMachineHostname()
{
    hostent* hostname = gethostbyname(_machine.c_str());

    if (hostname)
        _machine = std::string(inet_ntoa(**(in_addr**)hostname->h_addr_list));
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
    }
    if (_port.empty())
        throw (CoreException("Core setup", "Empty port. Please select port with the flag \"-p PORT\"."));
    _resolveMachineHostname();
}

void Core::_connectToServer()
{
    char *str = NULL;

    str = (char *)_machine.c_str();
    if (!c_interface_try_to_connect_to_server(str, std::atoi(_port.c_str())))
        throw (CoreException("Core setup", "Unable to connect to the server"));
}

void Core::_waitForServerAnswer()
{
    while(!c_interface_get_response_state());
}

bool Core::_canEntityUpdate(std::vector<std::string> &entityAsString, std::string &type, std::string &response)
{
    bool remove = false;

    entityAsString = _stringToVector(response, type);
    if (response.find(type) != (size_t)-1)
        remove = true;
    if (!entityAsString.empty() && entityAsString.at(0).rfind("start", 0) == 0)
        entityAsString.erase(entityAsString.begin());
    if (!entityAsString.empty() && remove) {
        // _removeEntities(type);
        return true;
    }
    return false;
}

void Core::_updateEntities(std::string &type, std::string &response)
{
    std::vector<std::string> entityAsString;

    if (!_canEntityUpdate(entityAsString, type, response))
        return;
    for (std::string &it : entityAsString) {
        if (it.empty())
            continue;
        it.insert(0, type);
        if (type == "player") {
            entity::Player p;
            try {
                _unpackObject->UnpackEntity(p, it);
                _sfml->addPlayer(p);
            } catch (...) {}
        }
        if (type == "egg") {
            entity::Egg e;
            try {
                _unpackObject->UnpackEntity(e, it);
                _sfml->addEgg(e);
            } catch (...) {}
        }
        if (type == "tile") {
            entity::Tile t;
            try {
                _unpackObject->UnpackEntity(t, it);
                _sfml->addTilesInfo(t);
            } catch (...) {}
        }
    }
    entityAsString.clear();
}

void Core::_updateEntities(std::string &response)
{
    gui::entity::Tile t;
    gui::entity::Player p;
    gui::entity::Egg e;
    std::string tilestr = std::string("tile");
    std::string playerstr = std::string("player");
    std::string eggstr = std::string("egg");

    if (response.empty()) {
        _removeEntities(playerstr);
        _removeEntities(eggstr);
        return;
    }
    _updateEntities(tilestr, response);
    _updateEntities(playerstr, response);
    _updateEntities(eggstr, response);
}

void Core::setup(int ac, char **av)
{
    std::string response;
    sf::Vector2f mapSize;

    _getArgs(ac, av);
    _connectToServer();
    _waitForServerAnswer();
    if (!c_interface_get_unexpected_response_state())
        throw (CoreException("Core setup", "Invalid receive data"));
    response = std::string(c_interface_get_unexpected_response());
    _unpackObject->UnpackEntity(*_startData, response);
    mapSize = {(float)_startData->size_x, (float)_startData->size_y};
    _sfml = std::make_unique<gui::SFML>(mapSize);
    _updateEntities(response);
}

Core::Core()
{
    _unpackObject = std::make_unique<unpack::Unpack>();
    _startData = std::make_unique<unpack::Start>();
}

Core::~Core()
{
    if (c_interface_get_network_state()) {
        std::cout << "try to disconnect" << std::endl;
        c_interface_try_to_disconnect_to_server();
    }
}
