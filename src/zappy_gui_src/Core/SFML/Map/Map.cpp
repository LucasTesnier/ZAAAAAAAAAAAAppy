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
    _noTileSelected = {-1, -1};
    std::vector<int> tmpVec{0, 0, 0, 0, 0, 0, 0,};
    _noTileSelectedInv = tmpVec;
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
    }
    if (type == "player") {
        _players.clear();
        for (auto &it : _tile)
            it->removePlayers();
    }
    if (type == "egg") {
        _eggs.clear();
        for (auto &it : _tile)
            it->removeEggs();
    }
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

void Map::_displaySelectedTile(sf::RectangleShape &entityRepresentation)
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

void Map::_displayHoveredTile(sf::RectangleShape &entityRepresentation)
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
void Map::_displayPlayers(Tile &tile, sf::RectangleShape &playerRepresentation)
{
    playerRepresentation.setFillColor(sf::Color::Green);
    playerRepresentation.setSize(sf::Vector2f(10, 10));
    playerRepresentation.setOutlineColor(sf::Color::Black);
    playerRepresentation.setOutlineThickness(1);
    if (tile.getPlayers().size()) {
        playerRepresentation.setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - playerRepresentation.getGlobalBounds().width / 2, tile.getGlobalBound().top});
        _window->draw(playerRepresentation);
        if (tile.getPlayers().size() >= 2) {
            playerRepresentation.move(-4, 4);
            _window->draw(playerRepresentation);
        }
        if (tile.getPlayers().size() >= 3) {
            playerRepresentation.move(8, 0);
            _window->draw(playerRepresentation);
        }
        if (tile.getPlayers().size() >= 4) {
            playerRepresentation.move(-4, 4);
            _window->draw(playerRepresentation);
        }
    }
}

void Map::_displayResources(Tile &tile, sf::RectangleShape &ressourcesRepresentation)
{
    std::size_t index = 1;
    int multiplierFood = 10;
    int multiplierStone = 5;

    ressourcesRepresentation.setSize(sf::Vector2f(5, 5));
    ressourcesRepresentation.setOutlineThickness(0.5);
    ressourcesRepresentation.setFillColor(sf::Color(0, 0, 0));
    for (auto &it : tile.getTileInfo().getInventory()) {
        if (it) {
            ressourcesRepresentation.setPosition({tile.getGlobalBound().left + index * tile.getGlobalBound().width / 9, tile.getGlobalBound().top + tile.getGlobalBound().height / 2 - ressourcesRepresentation.getGlobalBounds().height / 2});
            _window->draw(ressourcesRepresentation);
            if (it >= 2 * (index == 1 ? multiplierFood : multiplierStone)) {
                ressourcesRepresentation.move(-4, 4);
                _window->draw(ressourcesRepresentation);
            }
            if (it >= 3 * (index == 1 ? multiplierFood : multiplierStone)) {
                ressourcesRepresentation.move(8, 0);
                _window->draw(ressourcesRepresentation);
            }
            if (it >= 4 * (index == 1 ? multiplierFood : multiplierStone)) {
                ressourcesRepresentation.move(-4, 4);
                _window->draw(ressourcesRepresentation);
            }
        }
        ressourcesRepresentation.setFillColor(ressourcesRepresentation.getFillColor() + sf::Color(30, 30, 30));
        index++;
    }
}

void Map::_displayEggs(Tile &tile, sf::RectangleShape &eggRepresentation)
{
    eggRepresentation.setFillColor(sf::Color::Yellow);
    eggRepresentation.setSize(sf::Vector2f(8, 8));
    eggRepresentation.setOutlineColor(sf::Color::Black);
    eggRepresentation.setOutlineThickness(1);
    if (tile.getEggs().size()) {
        eggRepresentation.setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - eggRepresentation.getGlobalBounds().width / 2, tile.getGlobalBound().top + tile.getGlobalBound().height - eggRepresentation.getGlobalBounds().height});
        _window->draw(eggRepresentation);
        if (tile.getEggs().size() >= 2) {
            eggRepresentation.move(-4, 4);
            _window->draw(eggRepresentation);
        }
        if (tile.getEggs().size() >= 3) {
            eggRepresentation.move(8, 0);
            _window->draw(eggRepresentation);
        }
        if (tile.getEggs().size() >= 4) {
            eggRepresentation.move(-4, 4);
            _window->draw(eggRepresentation);
        }
    }
}

void Map::display()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window.get());
    sf::FloatRect area;
    std::size_t tmp = 0;
    sf::RectangleShape entityReprensentation;

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
        _displayPlayers(*_tile[i], entityReprensentation);
        _displayResources(*_tile[i], entityReprensentation);
        _displayEggs(*_tile[i], entityReprensentation);
    }
    _displaySelectedTile(entityReprensentation);
    _displayHoveredTile(entityReprensentation);
}

Map::~Map()
{

}
