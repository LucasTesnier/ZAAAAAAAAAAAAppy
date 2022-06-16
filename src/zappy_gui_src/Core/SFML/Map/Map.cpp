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
        if (_tile.size() == 1)
            _tile.back()->setTexture("assets/season1_ground1.png");
        else
            _tile.back()->setTexture(_tile[0]->getTexture());
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
    std::size_t index = -1;
    sf::Vector2f moveMap = {0, 0};
    sf::FloatRect area;
    std::vector<int> times(6);
    sf::Clock clock;
    std::size_t tmp = 0;

    times[0] = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    _updateMoveMap(moveMap);
    times[1] = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    for (auto &it : _tile) {
        if (moveMap.x || moveMap.y)
            it->setOrigin(it->getOrigin() + moveMap);
    }
    times[2] = clock.getElapsedTime().asMicroseconds();
    times[3] = 0;
    times[4] = 0;
    times[5] = 0;
    for (std::size_t i = 0; i < _tile.size(); i++) {
        times[3] += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        area = _tile[i]->getIsoPosition();
        if (area.left > _window->getSize().x && area.top > _window->getSize().y)
            continue;
        if (area.left < 0 && area.top > _window->getSize().y)
            continue;
        if (area.left + area.width < 0)
            continue;
        if (area.left > _window->getSize().x && tmp) {
            i = tmp + _mapSize.x - 2;
            tmp = 0;
            continue;
        }
        if (area.top + area.height < 0)
            continue;
        if (area.top > _window->getSize().y && tmp) {
            i = tmp + _mapSize.x - 2;
            tmp = 0;
            continue;
        }
        index++;
        if (tmp == 0)
            tmp = i;
        if (_tile[i]->isOnTile(mouse)) {
            _tileHover = i;
            if (_event->isButtonPressed()) {
                _tileSelected = i;
            }
        }
        times[3] += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        _tile[i]->setColor(sf::Color(255, 255, 255));
        times[4] += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        _window->draw(_tile[i]->getShape());
        times[5] += clock.getElapsedTime().asMicroseconds();
        clock.restart();
    }
    if (_tileSelected < _mapSize.x * _mapSize.y) {
        _tile[_tileSelected]->setColor(sf::Color(100, 100, 100, 100));
        _window->draw(_tile[_tileSelected]->getShape());
    }
    if (_tileHover < _mapSize.x * _mapSize.y) {
        _tile[_tileHover]->setColor(sf::Color(200, 200, 200, 200));
        _window->draw(_tile[_tileHover]->getShape());
    }
    index = 0;
}

Map::~Map()
{

}
