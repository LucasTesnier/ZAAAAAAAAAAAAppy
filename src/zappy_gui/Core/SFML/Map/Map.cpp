/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui/Core/SFML/Map/Map.cpp

#include "Map.hpp"
#include <math.h>
#include <exception>

Map::Map()
{
}

void Map::setSize(int x, int y)
{
    _mapSize.x = x;
    _mapSize.y = y;
    _updateTilesVectorSize();
}

void Map::setSize(sf::Vector2f size)
{
    _mapSize = size;
    _updateTilesVectorSize();
}

void Map::setWindow(sf::RenderWindow *window)
{
    _window = window;
}

void Map::draw()
{
}

void Map::_updateTilesVectorSize()
{
    while (_mapSize.x * _mapSize.y > _tiles.size())
        _tiles.pop_back();
    while (_mapSize.x * _mapSize.y < _tiles.size())
        _tiles.push_back(sf::ConvexShape());
}

sf::Vector2f Map::_indexToPosition(std::size_t index)
{
    sf::Vector2f position(0, 0);

    if (index > _mapSize.x * _mapSize.y)
        throw (std::exception());
    position.x = index % (int)_mapSize.y;
    position.y = index / (int)_mapSize.y;
    return position;
}

sf::Vector2f Map::_toIsoProjection(sf::Vector2f point, sf::Vector2f angles)
{
    sf::Vector2f newPoint = {0, 0};

    newPoint.x = cos((360 - angles.x / 2) * M_PI / 180) * point.x - cos(angles.x / 2 * M_PI / 180) * point.y;
    newPoint.y = sin(angles.y / 2 * M_PI / 180) * point.y + sin(angles.y / 2 * M_PI / 180) * point.x;
    return newPoint;
}

Map::~Map()
{
}
