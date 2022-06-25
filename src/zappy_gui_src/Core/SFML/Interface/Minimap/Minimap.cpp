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
    sf::FloatRect area;
    float ratio = 0;

    _window->draw(_minimap);
    _window->draw(_map);
    area = _map.getGlobalBounds();
    if (area.width > area.height)
        ratio = _minimapSize.x / area.width;
    else
        ratio = _minimapSize.y / area.height;
    for (std::tuple<std::string, sf::Vector2f> &it __attribute__((unused)): _playerList) {
        sf::Vector2f playerPosition = _toIsometric(sf::Vector2f(std::get<1>(it).x, std::get<1>(it).y), VIEW_ANGLE);
        sf::Vector2f scale = _toIsometric(sf::Vector2f(ratio, ratio), VIEW_ANGLE);
        _player.setPosition(_map.getPosition() + sf::Vector2f(playerPosition.x * scale.x, playerPosition.y * scale.y));
        _map.setPosition(sf::Vector2f(_minimap.getPosition().x - _map.getPoint(1).x * _map.getScale().x, _minimap.getPosition().y));
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
    const std::size_t tileNbrPoint = 4;
    const sf::Vector2f tilePointPosition[tileNbrPoint] = {{0, 0}, {0, _minimapSize.y}, _minimapSize, {_minimapSize.x, 0}};
    const sf::Vector2u windowSize = _window.get()->getSize();
    sf::FloatRect area;
    float ratio = 0;

    for (std::size_t i = 0; i < tileNbrPoint; i++) {
        _map.setPoint(i, _toIsometric(tilePointPosition[i], VIEW_ANGLE));
    }
    area = _map.getGlobalBounds();
    if (area.width > area.height)
        ratio = _minimapSize.x / area.width;
    else
        ratio = _minimapSize.y / area.height;
    _minimap.setSize(_minimapSize);
    _minimap.setPosition(sf::Vector2f(windowSize.x, _bottomMenuPosition.y) - _minimapSize);
    _map.setPosition(_minimap.getPosition());
    _map.scale(sf::Vector2f(ratio, ratio));
    _map.setPosition(sf::Vector2f(_minimap.getPosition().x - _map.getPoint(1).x * _map.getScale().x, _minimap.getPosition().y));
}

// void Minimap::_updateConvexShape()
// {
//     float max = (_mapSize.x > _mapSize.y) ? _mapSize.x : _mapSize.y;
//     sf::FloatRect area;
//     float ratio;

//     _map.setPoint(0, _toIsometric(sf::Vector2f(0, 0), sf::Vector2f(45, 45)));
//     _map.setPoint(1, _toIsometric(sf::Vector2f(0, 200 / max * _mapSize.y), sf::Vector2f(45, 45)));
//     _map.setPoint(2, _toIsometric(sf::Vector2f(200 / max * _mapSize.x, 200 / max * _mapSize.y), sf::Vector2f(45, 45)));
//     _map.setPoint(3, _toIsometric(sf::Vector2f(200 / max * _mapSize.x, 0), sf::Vector2f(45, 45)));
//     _minimap.setPosition(sf::Vector2f(_window->getSize().x - _minimapSize.x, _bottomMenuPosition.y - _minimapSize.y));
//     _minimap.setSize(_minimapSize);
//     _minimap.setFillColor(sf::Color(100, 100, 100));
//     area = _map.getGlobalBounds();
//     if (area.width > area.height)
//         ratio = _minimapSize.x / area.width;
//     else
//         ratio = _minimapSize.y / area.height;
//     _map.scale(sf::Vector2f(ratio, ratio));
//     _map.setPosition(sf::Vector2f(_minimap.getPosition().x - _map.getPoint(1).x * _map.getScale().x, _minimap.getPosition().y));
// }
