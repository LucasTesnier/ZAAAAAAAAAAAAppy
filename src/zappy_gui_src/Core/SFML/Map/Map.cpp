/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui_src/Core/SFML/Map/Map.cpp

#include "Map.hpp"
#include "ZappyGuiException.hpp"

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
    _initAnimationEntities();
}

void Map::_initAnimationEntities()
{
    try {
        _initRessourcesPaths();
        for (size_t i = 0; i < _ressourcesPaths.size(); i++) {
            Animation tmpAnim;
            tmpAnim.addTexture(_ressourcesPaths.at(i), sf::Vector2f(), sf::Vector2f());
            _ressourcesAnim.emplace_back(tmpAnim);
        }
        _playerAnimation.addTexture(PLAYER1_PATH,sf::Vector2f(), sf::Vector2f());
        _playerAnimation.addTexture(PLAYER2_PATH,sf::Vector2f(), sf::Vector2f());
        _playerAnimation.addTexture(PLAYER3_PATH,sf::Vector2f(), sf::Vector2f());
        _eggAnimation.addTexture(EGG_PATH, sf::Vector2f(), sf::Vector2f());
    } catch (AnimationException &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Map::_initRessourcesPaths()
{
    _ressourcesPaths.emplace_back(FOOD_PATH);
    _ressourcesPaths.emplace_back(LINEMATE_PATH);
    _ressourcesPaths.emplace_back(DERAUMERE_PATH);
    _ressourcesPaths.emplace_back(SIBUR_PATH);
    _ressourcesPaths.emplace_back(MENDIANE_PATH);
    _ressourcesPaths.emplace_back(PHIRAS_PATH);
    _ressourcesPaths.emplace_back(THYSTAME_PATH);

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
            _tile.back()->setTexture("assets/ground1.png");
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

void Map::_displaySelectedTile()
{
    if (_tileSelected < _mapSize.x * _mapSize.y) {
        _tile[_tileSelected]->setColor(sf::Color(100, 100, 100, 100));
        _window->draw(_tile[_tileSelected]->getShape());
        _tile[_tileSelected]->setColor(sf::Color(255, 255, 255));
        _displayPlayers(*_tile[_tileSelected]);
        _displayResources(*_tile[_tileSelected]);
        _displayEggs(*_tile[_tileSelected]);
    }
}

void Map::_displayHoveredTile()
{
    if (_tileHover < _mapSize.x * _mapSize.y) {
        _tile[_tileHover]->setColor(sf::Color(200, 200, 200, 200));
        _window->draw(_tile[_tileHover]->getShape());
        _tile[_tileHover]->setColor(sf::Color(255, 255, 255));
        _displayPlayers(*_tile[_tileHover]);
        _displayResources(*_tile[_tileHover]);
        _displayEggs(*_tile[_tileHover]);
    }
}

sf::Color Map::_findTeamColor(const std::string &teamName)
{
    int i = 0;

    for (auto &team : _teams) {
        if (team == teamName)
            return _teamsColor.at(i);
        i++;
    }
    return sf::Color::Transparent;
}

void Map::_displayPlayers(Tile &tile)
{
    if (tile.getPlayers().size()) {
        _playerAnimation.setSize(sf::Vector2f(58, 58));
        _playerAnimation.setDuration(100);
        _playerAnimation.setColor(_findTeamColor(tile.getPlayers().at(0).getTeamName()));
        _playerAnimation.setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - _playerAnimation.getGlobalBounds().width / 2, tile.getGlobalBound().top - 25});
        _playerAnimation.update();
        _window->draw(_playerAnimation.getShape());
        if (tile.getPlayers().size() >= 2) {
            _playerAnimation.moveShape({-6, 6});
            _playerAnimation.setColor(_findTeamColor(tile.getPlayers().at(1).getTeamName()));
            _playerAnimation.update();
            _window->draw(_playerAnimation.getShape());
        }
        if (tile.getPlayers().size() >= 3) {
            _playerAnimation.moveShape({12, 0});
            _playerAnimation.setColor(_findTeamColor(tile.getPlayers().at(2).getTeamName()));
            _playerAnimation.update();
            _window->draw(_playerAnimation.getShape());
        }
        if (tile.getPlayers().size() >= 4) {
            _playerAnimation.moveShape({-6, 6});
            _playerAnimation.setColor(_findTeamColor(tile.getPlayers().at(3).getTeamName()));
            _playerAnimation.update();
            _window->draw(_playerAnimation.getShape());
        }
    }
}

void Map::_displayResources(Tile &tile)
{
    std::size_t index = 1;
    std::size_t multiplier = 1;
    int multiplierFood = 10;
    int multiplierStone = 5;
    sf::Vector2f temp;

    for (auto &it : tile.getTileInfo().getInventory()) {
        if (index == 1)
            multiplier = multiplierFood;
        else
            multiplier = multiplierStone;
        if (it) {
            _ressourcesAnim.at(index - 1).setSize(sf::Vector2f(18, 18));
            _ressourcesAnim.at(index - 1).setPosition({tile.getGlobalBound().left + index * tile.getGlobalBound().width / 9 - 10, tile.getGlobalBound().top + tile.getGlobalBound().height / 2 - _ressourcesAnim.at(index - 1).getGlobalBounds().height / 2 - 10});
            _ressourcesAnim.at(index - 1).update();
            _window->draw(_ressourcesAnim.at(index - 1).getShape());
            if (it >= int(2 * multiplier)) {
                _ressourcesAnim.at(index - 1).moveShape({-6, 6});
                _ressourcesAnim.at(index - 1).update();
                _window->draw(_ressourcesAnim.at(index - 1).getShape());
            }
            if (it >= int(3 * multiplier)) {
                _ressourcesAnim.at(index - 1).moveShape({12, 0});
                _ressourcesAnim.at(index - 1).update();
                _window->draw(_ressourcesAnim.at(index - 1).getShape());
            }
            if (it >= int(4 * multiplier)) {
                _ressourcesAnim.at(index - 1).moveShape({-6, 6});
                _ressourcesAnim.at(index - 1).update();
                _window->draw(_ressourcesAnim.at(index - 1).getShape());
            }
        }
        index++;
    }
}

void Map::_displayEggs(Tile &tile)
{
    if (tile.getEggs().size()) {
        _eggAnimation.setSize(sf::Vector2f(28, 28));
        _eggAnimation.setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - _eggAnimation.getGlobalBounds().width / 2, tile.getGlobalBound().top + 20});
        _eggAnimation.update();
        _window->draw(_eggAnimation.getShape());
        if (tile.getEggs().size() >= 2) {
            _eggAnimation.moveShape({-6, 6});
            _eggAnimation.update();
            _window->draw(_eggAnimation.getShape());
        }
        if (tile.getEggs().size() >= 3) {
            _eggAnimation.moveShape({12, 0});
            _eggAnimation.update();
            _window->draw(_eggAnimation.getShape());
        }
        if (tile.getEggs().size() >= 4) {
            _eggAnimation.moveShape({-6, 6});
            _eggAnimation.update();
            _window->draw(_eggAnimation.getShape());
        }
    }
}

void Map::display()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window.get());
    sf::FloatRect area;
    std::size_t tmp = 0;

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
        _displayResources(*_tile[i]);
        _displayEggs(*_tile[i]);
        _displayPlayers(*_tile[i]);
    }
    _displaySelectedTile();
    _displayHoveredTile();
}
