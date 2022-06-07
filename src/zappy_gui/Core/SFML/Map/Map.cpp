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
    _mapSize = {10, 10};
    _tileSize = {100, 100};
    _tileOrigin = {-1000, -100};
    _rotation = 0;
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

sf::Vector2f Map::getSize() const
{
    return _mapSize;
}

void Map::setWindow(sf::RenderWindow *window)
{
    _window = window;
}

void Map::_drawRotation0()
{
    std::size_t index = 0;
    sf::Vector2f position(0, 0);
    sf::Vector2f startPos(0, 0);
    bool increase = true;

    while (index < _mapSize.x * _mapSize.y) {
        _window->draw(_tiles[_positionToIndex(position)].getConvexShape());
        _window->display();
        if (increase && startPos.x + 1 == _mapSize.x) {
            increase = false;
        }
        if (position.x == 0 || position.y + 1 == _mapSize.y) {
            if (increase) {
                startPos.x += 1;
            } else {
                startPos.y += 1;
            }
            position = startPos;
            index++;
            continue;
        }
        position.x += -1;
        position.y += 1;
        index++;
    }
}

void Map::draw()
{
    for (auto &it : _tiles) {
        _window->draw(it.getConvexShape());
    }
}

void Map::move(sf::Keyboard::Key key)
{
    sf::Vector2f move(0, 0);

    if (key == sf::Keyboard::Up || key == sf::Keyboard::Z)
        move.y = -10;
    if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
        move.y = 10;
    if (key == sf::Keyboard::Left || key == sf::Keyboard::Q)
        move.x = -10;
    if (key == sf::Keyboard::Right || key == sf::Keyboard::D)
        move.x = 10;
    if (move.x == 0 && move.y == 0)
        return;
    _tileOrigin.x -= move.x;
    _tileOrigin.y -= move.y;
    for (auto &it : _tiles) {
        it.setOrigin(_tileOrigin);
    }
}

void Map::_updateTilesPosition()
{
    std::size_t index = 0;
    sf::Vector2f position(0, 0);

    for (auto &it : _tiles) {
        position = _indexToPosition(index);
        position.x *= _tileSize.x;
        position.y *= _tileSize.y;
        it.setPosition(position);
        it.setOrigin(_tileOrigin);
        index++;
    }
}

void Map::_updateTilesVectorSize()
{
    while (_mapSize.x * _mapSize.y < _tiles.size())
        _tiles.pop_back();
    while (_mapSize.x * _mapSize.y > _tiles.size())
        _tiles.push_back(Map::Tile(_indexToPosition(_tiles.size()), _tileSize));
    _updateTilesPosition();
}

sf::Vector2f Map::_indexToPosition(std::size_t index)
{
    sf::Vector2f position(0, 0);

    position.x = index % (int)_mapSize.y;
    position.y = index / (int)_mapSize.y;
    return position;
}

std::size_t Map::_positionToIndex(sf::Vector2f position)
{
    std::size_t index = 0;

    index = position.y * _mapSize.x + position.x;
    return index;
}

Map::~Map()
{
}

Map::Tile::Tile(const sf::Vector2f &position, const sf::Vector2f &size)
{
    _shape.setFillColor(sf::Color::Green);
    _shape.setOutlineThickness(1);
    _shape.setPosition(_toIsoProjection(position, sf::Vector2f(45, 45)));
    _shape.setPointCount(4);
    _shape.setPoint(0, _toIsoProjection(sf::Vector2f(0, 0), sf::Vector2f(45, 45)));
    _shape.setPoint(1, _toIsoProjection(sf::Vector2f(size.x, 0), sf::Vector2f(45, 45)));
    _shape.setPoint(2, _toIsoProjection(sf::Vector2f(size.x, size.y), sf::Vector2f(45, 45)));
    _shape.setPoint(3, _toIsoProjection(sf::Vector2f(0, size.y), sf::Vector2f(45, 45)));
}

Map::Tile::Tile(const Tile &tile)
{
    _shape = tile._shape;
}

Map::Tile Map::Tile::operator=(const Tile &tile)
{
    Tile t;

    t._shape = tile._shape;
    t._size = tile._size;
    return t;
}

const sf::ConvexShape &Map::Tile::getConvexShape() const
{
    return _shape;
}

void Map::Tile::setConvexShape(const sf::ConvexShape &shape)
{
    _shape = shape;
}

const sf::Vector2f &Map::Tile::getSize() const
{
    return _size;
}

void Map::Tile::setSize(const sf::Vector2f &size)
{
    _size = size;
}

const sf::Vector2f &Map::Tile::getPosition() const
{
    return _shape.getPosition();
}

void Map::Tile::setPosition(const sf::Vector2f &position)
{
    _shape.setPosition(_toIsoProjection(position, sf::Vector2f(45, 45)));
}

const sf::Vector2f &Map::Tile::getOrigin() const
{
    return _shape.getOrigin();
}

void Map::Tile::setOrigin(const sf::Vector2f &origin)
{
    _shape.setOrigin(origin);
}

sf::Vector2f Map::Tile::_toIsoProjection(sf::Vector2f point, sf::Vector2f angles)
{
    sf::Vector2f newPoint = {0, 0};

    newPoint.x = cos((360 - angles.x / 2) * M_PI / 180) * point.x - cos(angles.x / 2 * M_PI / 180) * point.y;
    newPoint.y = sin(angles.y / 2 * M_PI / 180) * point.y + sin(angles.y / 2 * M_PI / 180) * point.x;
    return newPoint;
}
