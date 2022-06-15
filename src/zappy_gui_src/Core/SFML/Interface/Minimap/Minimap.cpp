/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Minimap
*/

#include "Minimap.hpp"
#include <math.h>

using namespace gui;

Minimap::Minimap()
{
    _playerList.clear();
    _minimap.setPosition(500, 500);
    _minimap.setSize(sf::Vector2f(100, 100));
    _map.setPosition(_minimap.getPosition());
    _map.setFillColor(sf::Color::Green);
    _map.setPointCount(4);
    _map.setPoint(0, {0, 0});
    _map.setPoint(1, {50, 50});
    _map.setPoint(2, {0, 100});
    _map.setPoint(3, {-50, 50});
}

void Minimap::display()
{
    _window->draw(_minimap);
    _window->draw(_map);
    for (std::tuple<std::string, sf::Vector2f> &it __attribute__((unused)): _playerList) {}
}

void Minimap::removePlayer(const std::string &name __attribute__((unused)))
{

}

void Minimap::switchSize()
{

}

sf::Vector2f Minimap::_toIsometric(sf::Vector2f vector, sf::Vector2f angle)
{
    sf::Vector2f point;

    point.x = cos((360 - angle.x / 2) * M_PI / 180) * vector.x - cos(angle.x / 2 * M_PI / 180) * vector.y;
    point.y = sin(angle.y / 2 * M_PI / 180) * vector.y + sin(angle.y / 2 * M_PI / 180) * vector.x;
    return (point);
}

void Minimap::_updateConvexShape()
{
    float max = (_mapSize.x > _mapSize.y) ? _mapSize.x : _mapSize.y;

    _map.setPoint(0, _toIsometric(sf::Vector2f(0, 0), sf::Vector2f(45, 45)));
    _map.setPoint(1, _toIsometric(sf::Vector2f(0, 200 / max * _mapSize.y), sf::Vector2f(45, 45)));
    _map.setPoint(2, _toIsometric(sf::Vector2f(200 / max * _mapSize.x, 200 / max * _mapSize.y), sf::Vector2f(45, 45)));
    _map.setPoint(3, _toIsometric(sf::Vector2f(200 / max * _mapSize.x, 0), sf::Vector2f(45, 45)));
    _map.setPosition(sf::Vector2f(_window->getSize().x - _map.getPoint(3).x, _window->getSize().y - (_map.getPoint(2).y)));
    _minimap.setPosition(sf::Vector2f(_map.getPosition().x + _map.getPoint(1).x, _map.getPosition().y));
    _minimap.setSize(sf::Vector2f(-_map.getPoint(1).x + _map.getPoint(3).x, _map.getPoint(2).y));
}
