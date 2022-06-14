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
    _texturePath = texturePath;
    if (!_texture.loadFromFile(texturePath))
        return;
    setTexture(_texture);
}

bool Tile::isOnTile(sf::Vector2i mouse)
{
    if (mouse.x >= _position.x && mouse.x <= _position.x + _size.x)
        if (mouse.y >= _position.y && mouse.y <= _position.y + _size.y)
            return true;
    return false;
}

sf::Vector2f Tile::_toIsometric(sf::Vector2f vector, sf::Vector2f angle, int zoom)
{
    vector.x = cos((360 - angle.x / 2) * M_PI / 180) * (vector.x * zoom);
    vector.x -= cos(angle.x / 2 * M_PI / 180) * vector.y;
    vector.y = sin(angle.y / 2 * M_PI / 180) * vector.y;
    vector.y += sin(angle.y / 2 * M_PI / 180) * vector.x;
    return (vector);
}

void Tile::_setShape()
{
    _shape.setPointCount(4);
    _shape.setPoint(0, {0, 0});
    _shape.setPoint(1, {0, _size.y});
    _shape.setPoint(2, {_size.x, _size.y});
    _shape.setPoint(3, {_size.x, 0});
}

Tile::~Tile()
{
}
