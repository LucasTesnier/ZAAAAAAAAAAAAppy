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
}

void Map::_updateTileVectorSize()
{
    while (_mapSize.x * _mapSize.y < _tile.size())
        _tile.pop_back();
    while (_mapSize.x * _mapSize.y > _tile.size()) {
        _tile.push_back(std::make_unique<Tile>());
        _tile.back()->setColor(sf::Color::Red);
        _tile.back()->setPosition(sf::Vector2f((_tile.size() - 1) % (int)_mapSize.x, (_tile.size() - 1) / (int)_mapSize.x));
        _tile.back()->setSize(sf::Vector2f(100, 100));
    }
}

void Map::display()
{
    int moveOrigin = 0;
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window.get());
    std::size_t index = 0;

    if (_event->isKeyPressed(sf::Keyboard::Z))
        moveOrigin = 1;
    if (_event->isKeyPressed(sf::Keyboard::Q))
        moveOrigin = 2;
    if (_event->isKeyPressed(sf::Keyboard::S))
        moveOrigin = 3;
    if (_event->isKeyPressed(sf::Keyboard::D))
        moveOrigin = 4;
    for (auto &it : _tile) {
        if (it->isOnTile(mouse)) {
            _tileHover = index;
            if (_event->isButtonPressed()) {
                _tileSelected = index;
            }
        }
        it->setColor(sf::Color::Red);
        _window->draw(it->getShape());
        switch (moveOrigin) {
        case 1:
            it->setOrigin(it->getOrigin() + sf::Vector2f(0, 5));
            break;
        case 2:
            it->setOrigin(it->getOrigin() + sf::Vector2f(5, 0));
            break;
        case 3:
            it->setOrigin(it->getOrigin() + sf::Vector2f(0, -5));
            break;
        case 4:
            it->setOrigin(it->getOrigin() + sf::Vector2f(-5, 0));
            break;
        }
        index++;
    }
    if (_tileSelected < _mapSize.x * _mapSize.y) {
        _tile[_tileSelected]->setColor(sf::Color::Blue);
        _window->draw(_tile[_tileSelected]->getShape());
    }
    if (_tileHover < _mapSize.x * _mapSize.y) {
        _tile[_tileHover]->setColor(sf::Color::Green);
        _window->draw(_tile[_tileHover]->getShape());
    }
}

Map::~Map()
{

}
