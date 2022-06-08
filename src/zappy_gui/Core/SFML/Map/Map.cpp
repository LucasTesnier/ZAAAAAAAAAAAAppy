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
#include <iostream>

Map::Map()
{
    _mapSize = {10, 10};
    _tileSize = {100, 100};
    _tileOrigin = {0, 0};
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

void Map::Tile::setStatus(status_e status)
{
    _status = status;
}

void Map::Tile::setColor(sf::Color color)
{
    _shape.setFillColor(color);
}

void Map::selectTile()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window);

    for (auto &it : _tiles) {
        if (it.inTile(mouse)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if (it.isSelected())
                    it.setStatus(Map::Tile::NONE);
                else
                    it.setStatus(Map::Tile::SELECTED);
                it.setColor(sf::Color::Blue);
            } else if (!it.isSelected()) {
                it.setStatus(Map::Tile::HOVER);
                it.setColor(sf::Color::Red);
            }
        } else if (!it.isSelected()) {
            it.setStatus(Map::Tile::NONE);
            it.setColor(sf::Color::Green);
        }
    }
}

void Map::draw() const
{
    for (auto &it : _tiles) {
        _window->draw(it.getConvexShape());
    }
}

void Map::move(direction_e direction)
{
    sf::Vector2f move(0, 0);

    if (direction == UP)
        move.y = -10;
    if (direction == DOWN)
        move.y = 10;
    if (direction == LEFT)
        move.x = -10;
    if (direction == RIGHT)
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

bool Map::Tile::inTile(sf::Vector2i mouse)
{
    int res = 0;
    res += _onRight(_shape.getPoint(0) + _shape.getPosition() - _shape.getOrigin(), _shape.getPoint(1) + _shape.getPosition() - _shape.getOrigin(), mouse);
    res += _onRight(_shape.getPoint(1) + _shape.getPosition() - _shape.getOrigin(), _shape.getPoint(2) + _shape.getPosition() - _shape.getOrigin(), mouse);
    res += _onRight(_shape.getPoint(2) + _shape.getPosition() - _shape.getOrigin(), _shape.getPoint(3) + _shape.getPosition() - _shape.getOrigin(), mouse);
    res += _onRight(_shape.getPoint(3) + _shape.getPosition() - _shape.getOrigin(), _shape.getPoint(0) + _shape.getPosition() - _shape.getOrigin(), mouse);
    if (res >= 4) {
        _shape.setOutlineThickness(2);
        return true;
    }
    _shape.setOutlineThickness(1);
    return false;
}

sf::Vector2f Map::Tile::_toIsoProjection(sf::Vector2f point, sf::Vector2f angles)
{
    sf::Vector2f newPoint __attribute__((unused)) = {0, 0};

    newPoint.x = cos((360 - angles.x / 2) * M_PI / 180) * point.x - cos(angles.x / 2 * M_PI / 180) * point.y;
    newPoint.y = sin(angles.y / 2 * M_PI / 180) * point.y + sin(angles.y / 2 * M_PI / 180) * point.x;
    return newPoint;
}

int Map::Tile::_onRight(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2i mouse)
{
    sf::Vector2f vector1 = {point2.x - point1.x, point2.y - point1.y};
    sf::Vector2f vector2 = {mouse.x - point1.x, mouse.y - point1.y};
    int res = vector1.x * vector2.y - vector1.y * vector2.x;

    if (res > 0)
        return 1;
    return 0;
}
