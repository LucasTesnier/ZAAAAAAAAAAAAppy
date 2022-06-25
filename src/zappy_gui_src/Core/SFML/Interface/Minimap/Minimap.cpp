/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Minimap
*/

/// \file src/zappy_gui_src/Core/SFML/Interface/Minimap/Minimap.cpp

#include "Minimap.hpp"
#include <math.h>

using namespace gui;

const sf::Vector2f VIEW_ANGLE = sf::Vector2f(45, 45);

Minimap::Minimap()
{
    const std::size_t tileNbrPoint = 4;
    const sf::Vector2f minimapPosition = {500, 500};
    const sf::Vector2f minimapSize = {200, 200};
    const sf::Vector2f tilePointPosition[tileNbrPoint] = {{0, 0}, {0, minimapSize.y}, minimapSize, {minimapSize.x, 0}};

    _playerList.clear();
    _minimap.setPosition(minimapPosition);
    _minimap.setSize(sf::Vector2f(100, 100));
    _minimap.setFillColor(sf::Color(100, 100, 100));
    _map.setPosition(_minimap.getPosition());
    _map.setFillColor(sf::Color::Green);
    _map.setPointCount(4);
    _map.setPoint(0, _toIsometric(tilePointPosition[0], VIEW_ANGLE));
    _map.setPoint(1, _toIsometric(tilePointPosition[1], VIEW_ANGLE));
    _map.setPoint(2, _toIsometric(tilePointPosition[2], VIEW_ANGLE));
    _map.setPoint(3, _toIsometric(tilePointPosition[3], VIEW_ANGLE));
    _minimapSize = minimapSize;
    isSwitch = false;
    _player.setRadius(3);
}

void Minimap::display()
{

    _window->draw(_minimap);
    // _window->draw(_map);
    for (std::tuple<std::string, sf::Vector2f> &it __attribute__((unused)): _playerList) {
        _player.setPosition(_minimap.getPosition() + sf::Vector2f(std::get<1>(it).x * _minimapSize.x / _mapSize.x, std::get<1>(it).y * _minimapSize.y / _mapSize.y));
        _window->draw(_player);
    }
}

void Minimap::removePlayer(const std::string &name __attribute__((unused)))
{
    for (auto it = _playerList.begin(); it != _playerList.end(); ++it) {
        if (std::get<0>((*it.base())) == name) {
            _playerList.erase(it);
            return;
        }
    }
}

void Minimap::addPlayer(const std::string &name, const sf::Vector2f &position)
{
    for (auto &it : _playerList) {
        if (std::get<0>(it) == name) {
            std::get<0>(it) = name;
            std::get<1>(it) = position;
            return;
        }
    }
    _playerList.push_back(std::tuple(name, position));
}

void Minimap::switchSize(bool state)
{
    if (state && isSwitch == false) {
        if (_minimapSize.x == 200 && _minimapSize.y == 200)
            _minimapSize = sf::Vector2f(_window->getSize().x, _window->getSize().y - _window->getSize().y / 5);
        else
            _minimapSize = {200, 200};
        _updateConvexShape();
        isSwitch = true;
    } else if (state == false)
        isSwitch = false;
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
    const sf::Vector2u windowSize = _window.get()->getSize();

    _minimap.setPosition(sf::Vector2f(windowSize.x, _bottomMenuPosition.y) - _minimapSize);
    _minimap.setSize(_minimapSize);
}
