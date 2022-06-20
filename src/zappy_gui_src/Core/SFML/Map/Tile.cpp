/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Tile
*/

#include "Tile.hpp"
#include "math.h"

using namespace gui;

Tile::Tile()
{
    _size = {0, 0};
    _texturePath = "";
    _shape.setOutlineThickness(1);
    _shape.setOutlineColor(sf::Color(150, 150, 150));
    _setShape();
    _zoom = 1;
}

Tile::Tile(Tile &tile)
{
    _shape = tile._shape;
    _size = tile._size;
    _texturePath = tile._texturePath;
}

Tile Tile::operator=(const Tile &tile)
{
    Tile newTile;

    newTile._shape = tile._shape;
    newTile._size = tile._size;
    newTile._texturePath = tile._texturePath;
    return newTile;
}

void Tile::setTexture(const std::string &texturePath)
{
    _texture = std::make_shared<sf::Texture>();

    if (!_texture->loadFromFile(texturePath)) {
        return;
    }
    _texturePath = texturePath;
    _shape.setTexture(_texture.get());
}

int Tile::isOnRight(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2i mouse)
{
    sf::Vector2f vector1 = {point2.x - point1.x, point2.y - point1.y};
    sf::Vector2f vector2 = {mouse.x - point1.x, mouse.y - point1.y};
    int res = vector1.x * vector2.y - vector1.y * vector2.x;

    if (res < 0)
        return 1;
    return 0;
}

bool Tile::isOnTile(sf::Vector2i mouse)
{
    int res = 0;
    sf::Vector2f position = _toIsometric(sf::Vector2f(_position.x * _size.x, _position.y * _size.y), sf::Vector2f(45, 35));

    mouse.x -= position.x - _shape.getOrigin().x;
    mouse.y -= position.y - _shape.getOrigin().y;
    res += isOnRight(_shape.getPoint(0), _shape.getPoint(1), mouse);
    res += isOnRight(_shape.getPoint(1), _shape.getPoint(2), mouse);
    res += isOnRight(_shape.getPoint(2), _shape.getPoint(3), mouse);
    res += isOnRight(_shape.getPoint(3), _shape.getPoint(0), mouse);
    if (res == 4)
        return true;
    return false;
}

sf::Vector2f Tile::_toIsometric(sf::Vector2f vector, sf::Vector2f angle)
{
    sf::Vector2f point;

    point.x = cos((360 - angle.x / 2) * M_PI / 180) * vector.x - cos(angle.x / 2 * M_PI / 180) * vector.y;
    point.y = sin(angle.y / 2 * M_PI / 180) * vector.y + sin(angle.y / 2 * M_PI / 180) * vector.x;
    return (point);
}

void Tile::_setShape()
{
    _shape.setPosition(_toIsometric({_position.x * _size.x, _position.y * _size.y}, {45, 35}));
    _shape.setPointCount(4);
    _shape.setPoint(0, _toIsometric({0, 0}, {45, 35}));
    _shape.setPoint(1, _toIsometric({0, _size.y}, {45, 35}));
    _shape.setPoint(2, _toIsometric({_size.x, _size.y}, {45, 35}));
    _shape.setPoint(3, _toIsometric({_size.x, 0}, {45, 35}));
}

void Tile::setZoom(float zoom)
{
    if (zoom == _zoom)
        return;
    _zoom = zoom;
    _size.x *= zoom;
    _size.y *= zoom;
    _setShape();
}

Tile::~Tile()
{
}
