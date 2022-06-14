/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui_src/Core/SFML/Map/Map.cpp

#include "Map.hpp"

using namespace gui;

Map::Map()
{
    _tileSelected = -1;
    _tileHover = -1;
    _mapSize = {10, 10};
    _zoom = 1;
}

void Map::_updateTileVectorSize()
{
    while (_mapSize.x * _mapSize.y < _tile.size())
        _tile.pop_back();
    while (_mapSize.x * _mapSize.y > _tile.size()) {
        _tile.push_back(std::make_unique<Tile>());
        _tile.back()->setPosition(sf::Vector2f((_tile.size() - 1) % (int)_mapSize.x, (_tile.size() - 1) / (int)_mapSize.x));
        _tile.back()->setSize(sf::Vector2f(100, 100));
        _tile.back()->setTexture("assets/season1_ground1.png");
    }
}

void Map::_updateMoveMap(sf::Vector2f &moveMap)
{
    int value = 10;

    if (_event->isKeyPressed(sf::Keyboard::Z))
        moveMap.y = value;
    if (_event->isKeyPressed(sf::Keyboard::Q))
        moveMap.x = value;
    if (_event->isKeyPressed(sf::Keyboard::S))
        moveMap.y = -value;
    if (_event->isKeyPressed(sf::Keyboard::D))
        moveMap.x = -value;
}

void Map::display()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window.get());
    std::size_t index = 0;
    sf::Vector2f moveMap = {0, 0};

    _updateMoveMap(moveMap);
    for (auto &it : _tile) {
        if (it->isOnTile(mouse)) {
            _tileHover = index;
            if (_event->isButtonPressed()) {
                _tileSelected = index;
            }
        }
        it->setColor(sf::Color(255, 255, 255));
        it->setOrigin(it->getOrigin() + moveMap);
        _window->draw(it->getShape());
        index++;
    }
    if (_tileSelected < _mapSize.x * _mapSize.y) {
        _tile[_tileSelected]->setColor(sf::Color(100, 100, 100, 100));
        _window->draw(_tile[_tileSelected]->getShape());
    }
    if (_tileHover < _mapSize.x * _mapSize.y) {
        _tile[_tileHover]->setColor(sf::Color(200, 200, 200, 200));
        _window->draw(_tile[_tileHover]->getShape());
    }
}

Map::~Map()
{

}
