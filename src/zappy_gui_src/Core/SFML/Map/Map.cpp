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
    if (_mapSize.x * _mapSize.y > _tile.size()) {
        for (auto &it : _tile) {
            it->setPosition(sf::Vector2f((_tile.size() - 1) % (int)_mapSize.x, (_tile.size() - 1) / (int)_mapSize.x));
        }
    }
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

void Map::removeEntities(std::string &type)
{
    if (type == "tile") {
        _tilesInfo.clear();
        for (auto &it : _tile)
            it->removeTileInfo();
    } else if (type == "player") {
        _players.clear();
        for (auto &it : _tile)
            it->removePlayers();
    } else if (type == "egg") {
        _eggs.clear();
        for (auto &it : _tile)
            it->removeEggs();
    } else
        return;
}

void Map::_updateMoveMap()
{
    int value = 10;
    sf::Vector2f moveMap = {0, 0};

    if (_event->isKeyPressed(sf::Keyboard::Z))
        moveMap.y = value;
    if (_event->isKeyPressed(sf::Keyboard::Q))
        moveMap.x = value;
    if (_event->isKeyPressed(sf::Keyboard::S))
        moveMap.y = -value;
    if (_event->isKeyPressed(sf::Keyboard::D))
        moveMap.x = -value;
    for (auto &it : _tile) {
        if (moveMap.x || moveMap.y)
            it->setOrigin(it->getOrigin() + moveMap);
    }
}

bool Map::_tileMustBeDisplayed(const sf::FloatRect &area, const sf::Vector2u windowSize, std::size_t &tmp, sf::Vector2f &mapSize, std::size_t &i)
{
    if (area.left > windowSize.x && area.top > windowSize.y)
        return false;
    if (area.left < 0 && area.top > windowSize.y)
        return false;
    if (area.left + area.width < 0)
        return false;
    if (area.left > windowSize.x && tmp) {
        i = tmp + mapSize.x - 2;
        tmp = 0;
        return false;
    }
    if (area.top + area.height < 0)
        return false;
    if (area.top > windowSize.y && tmp) {
        i = tmp + mapSize.x - 2;
        tmp = 0;
        return false;
    }
    return true;
}

void Map::_findSelectedAndHoverTiles(std::size_t &i, const sf::Vector2i &mouse)
{
    if (_tile[i]->isOnTile(mouse)) {
        _tileHover = i;
        if (_event->isButtonPressed()) {
            _tileSelected = i;
        }
    }
}

void Map::_displaySelectedTile(sf::CircleShape &entityRepresentation)
{
    if (_tileSelected < _mapSize.x * _mapSize.y) {
        _tile[_tileSelected]->setColor(sf::Color(100, 100, 100, 100));
        _window->draw(_tile[_tileSelected]->getShape());
        _tile[_tileSelected]->setColor(sf::Color(255, 255, 255));
        _displayPlayers(*_tile[_tileSelected], entityRepresentation);
        _displayResources(*_tile[_tileSelected], entityRepresentation);
        _displayEggs(*_tile[_tileSelected], entityRepresentation);
    }
}

void Map::_displayHoveredTile(sf::CircleShape &entityRepresentation)
{
    if (_tileHover < _mapSize.x * _mapSize.y) {
        _tile[_tileHover]->setColor(sf::Color(200, 200, 200, 200));
        _window->draw(_tile[_tileHover]->getShape());
        _tile[_tileHover]->setColor(sf::Color(255, 255, 255));
        _displayPlayers(*_tile[_tileHover], entityRepresentation);
        _displayResources(*_tile[_tileHover], entityRepresentation);
        _displayEggs(*_tile[_tileHover], entityRepresentation);
    }
}
void Map::_displayPlayers(Tile &tile, sf::CircleShape &playerRepresentation)
{
    playerRepresentation.setFillColor(sf::Color::Green);
    playerRepresentation.setRadius(10);
    if (tile.getPlayers().size()) {
        playerRepresentation.setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - playerRepresentation.getGlobalBounds().width / 2, tile.getGlobalBound().top});
        _window->draw(playerRepresentation);
    }
}

void Map::_displayResources(Tile &tile, sf::CircleShape &resourcesRepresentation)
{
    std::size_t index = 1;

    resourcesRepresentation.setRadius(5);
    resourcesRepresentation.setFillColor(sf::Color(0, 0, 0));
    for (auto &it : tile.getTileInfo()._inventory) {
        if (it) {
            resourcesRepresentation.setPosition({tile.getGlobalBound().left + index * tile.getGlobalBound().width / 9, tile.getGlobalBound().top + tile.getGlobalBound().height / 2 - resourcesRepresentation.getGlobalBounds().height / 2});
            _window->draw(resourcesRepresentation);
        }
        resourcesRepresentation.setFillColor(resourcesRepresentation.getFillColor() + sf::Color(30, 30, 30));
        index++;
    }
}

void Map::_displayEggs(Tile &tile, sf::CircleShape &eggRepresentation)
{
    eggRepresentation.setFillColor(sf::Color::Yellow);
    eggRepresentation.setRadius(8);
    if (tile.getEggs().size()) {
        eggRepresentation.setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - eggRepresentation.getGlobalBounds().width / 2, tile.getGlobalBound().top + tile.getGlobalBound().height - eggRepresentation.getGlobalBounds().height});
        _window->draw(eggRepresentation);
    }
}

void Map::display()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window.get());
    sf::FloatRect area;
    std::size_t tmp = 0;
    sf::CircleShape _entityReprensentation;

    _updateMoveMap();
    for (std::size_t i = 0; i < _tile.size(); i++) {
        area = _tile[i]->getGlobalBound();
        if (!_tileMustBeDisplayed(area, _window->getSize(), tmp, _mapSize, i))
            continue;
        if (i % (int)_mapSize.x == 0)
            tmp = i + 1;
        if (tmp == 0)
            tmp = i;
        _findSelectedAndHoverTiles(i, mouse);
        _window->draw(_tile[i]->getShape());
        _displayPlayers(*_tile[i], _entityReprensentation);
        _displayResources(*_tile[i], _entityReprensentation);
        _displayEggs(*_tile[i], _entityReprensentation);
    }
    _displaySelectedTile(_entityReprensentation);
    _displayHoveredTile(_entityReprensentation);
}

Map::~Map()
{

}
