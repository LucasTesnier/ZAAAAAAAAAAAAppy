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
    const std::size_t tileNbrPoint = 4;
    const sf::Vector2f tilePointPosition[tileNbrPoint] = {{0, 0}, {50, 50}, {0, 100}, {-50, 50}};
    const sf::Vector2f minimapPosition = {500, 500};
    const sf::Vector2f minimapSize = {200, 200};

    _playerList.clear();
    _minimap.setPosition(minimapPosition);
    _minimap.setSize(sf::Vector2f(100, 100));
    _map.setPosition(_minimap.getPosition());
    _map.setFillColor(sf::Color::Green);
    _map.setPointCount(4);
    _map.setPoint(0, tilePointPosition[0]);
    _map.setPoint(1, tilePointPosition[1]);
    _map.setPoint(2, tilePointPosition[2]);
    _map.setPoint(3, tilePointPosition[3]);
    _minimapSize = minimapSize;
    isSwitch = false;
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

void Minimap::switchSize(bool state)
{
    if (state && isSwitch == false) {
        if (_minimapSize.x == 200 && _minimapSize.y == 200)
            _minimapSize = sf::Vector2f(_window->getSize());
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
    float max = (_mapSize.x > _mapSize.y) ? _mapSize.x : _mapSize.y;
    sf::FloatRect area;
    float ratio;

    _map.setPoint(0, _toIsometric(sf::Vector2f(0, 0), sf::Vector2f(45, 45)));
    _map.setPoint(1, _toIsometric(sf::Vector2f(0, 200 / max * _mapSize.y), sf::Vector2f(45, 45)));
    _map.setPoint(2, _toIsometric(sf::Vector2f(200 / max * _mapSize.x, 200 / max * _mapSize.y), sf::Vector2f(45, 45)));
    _map.setPoint(3, _toIsometric(sf::Vector2f(200 / max * _mapSize.x, 0), sf::Vector2f(45, 45)));
    _minimap.setPosition(sf::Vector2f(_window->getSize().x - _minimapSize.x, _window->getSize().y - _minimapSize.y));
    _minimap.setSize(_minimapSize);
    _minimap.setFillColor(sf::Color(100, 100, 100));
    area = _map.getGlobalBounds();
    if (area.width > area.height)
        ratio = _minimapSize.x / area.width;
    else
        ratio = _minimapSize.y / area.height;
    _map.scale(sf::Vector2f(ratio, ratio));
    _map.setPosition(sf::Vector2f(_minimap.getPosition().x - _map.getPoint(1).x * _map.getScale().x, _minimap.getPosition().y));
}
