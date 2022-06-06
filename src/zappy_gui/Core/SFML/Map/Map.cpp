/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui/Core/SFML/Map/Map.cpp

#include "Map.hpp"
#include <math.h>

Map::Map()
{
    _shape.setFillColor(sf::Color::Red);
    _shape.setPosition(500, 500);
    _shape.setPointCount(4);
    _shape.setPoint(0, _toIsoProjection(sf::Vector2f({0, 0}), sf::Vector2f({35, 45})));
    _shape.setPoint(1, _toIsoProjection(sf::Vector2f({100, 0}), sf::Vector2f({35, 45})));
    _shape.setPoint(2, _toIsoProjection(sf::Vector2f({100, 100}), sf::Vector2f({35, 45})));
    _shape.setPoint(3, _toIsoProjection(sf::Vector2f({0, 100}), sf::Vector2f({35, 45})));
}

void Map::setWindow(sf::RenderWindow *window)
{
    _window = window;
}

void Map::draw()
{
    _window->draw(_shape);
}

sf::Vector2f Map::_toIsoProjection(sf::Vector2f point, sf::Vector2f angles)
{
    sf::Vector2f newPoint = {0, 0};

    newPoint.x = cos((360 - angles.x / 2) * M_PI / 180) * point.x - cos(angles.x / 2 * M_PI / 180) * point.y;
    newPoint.y = sin(angles.y / 2 * M_PI / 180) * point.y + sin(angles.y / 2 * M_PI / 180) * point.x;
    return newPoint;
}

// sf::Vector2f Map::isoProjection(int x, int y, int z, sf::Vector2f angles)

// {
//     sf::Vector2f point;

//     point.x = cos((360 - angles.x / 2) * M_PI / 180) *
//     x - cos(angles.x / 2 * M_PI / 180) * y;
//     point.y = sin(angles.y / 2 * M_PI / 180) * y +
//     sin(angles.y / 2 * M_PI / 180) * x - z;
//     return (point);
// }

Map::~Map()
{
}
