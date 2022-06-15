/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Minimap
*/

#include "Minimap.hpp"

using namespace gui;

Minimap::Minimap()
{
    _playerList.clear();
}

void Minimap::display()
{
    _window->draw(_minimap);
    _window->draw(_map);
    for (std::tuple<std::string, sf::Vector2f> &it : _playerList) {}
}

void Minimap::removePlayer(const std::string &name)
{

}

void Minimap::switchSize()
{

}
