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

const std::vector<std::vector<std::string>> PLAYERS_PATH = {{
        "assets/yellow_woman1.png",
        "assets/yellow_woman2.png",
        "assets/yellow_woman4.png",
        "assets/yellow_woman3.png",
    }, {
        "assets/purple_woman1.png",
        "assets/purple_woman2.png",
        "assets/purple_woman3.png",
        "assets/purple_woman4.png",
    }, {
        "assets/pink_woman1.png",
        "assets/pink_woman2.png",
        "assets/pink_woman3.png",
        "assets/pink_woman4.png",
    }, {
        "assets/black_woman1.png",
        "assets/black_woman2.png",
        "assets/black_woman3.png",
        "assets/black_woman4.png",
    }, {
        "assets/white_woman1.png",
        "assets/white_woman2.png",
        "assets/white_woman3.png",
        "assets/white_woman4.png",
    }
};

Map::Map()
{
    _tileSelected = -1;
    _tileHover = -1;
    _mapSize = {10, 10};
    _zoom = 1;
    _noTileSelected = {-1, -1};
    std::vector<int> tmpVec{0, 0, 0, 0, 0, 0, 0};
    _noTileSelectedInv = tmpVec;
    _initAnimationEntities();
    _initSounds();
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
        std::size_t index = 0;
        for (const std::vector<std::string> &PATHS : PLAYERS_PATH) {
            _playerAnimation.push_back(Animation());
            for (const std::string &it : PATHS) {
                _playerAnimation.at(index).addTexture(it, sf::Vector2f(), sf::Vector2f());
            }
            index++;
        }
        _eggAnimation.addTexture(EGG_PATH, sf::Vector2f(), sf::Vector2f());
    } catch (AnimationException &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Map::_initSound(int index)
{
    _sounds.push_back(std::make_shared<sf::Sound>(sf::Sound{}));
    _sounds.at(index)->setBuffer(_soundsBuffer.at(index));
}

void Map::_initSoundBuffer(const char *path, int index)
{
    _soundsBuffer.push_back(sf::SoundBuffer());
    if (!_soundsBuffer.at(index).loadFromFile(path)) {
        throw MapException("Cannot load sound file", "couldn't load file :" + std::string(path));
    }
}

void Map::_initSounds()
{
    try {
        _initSoundBuffer(SOUND_SPAWN_PATH, SPAWN_SOUND);
        _initSoundBuffer(SOUND_DEATH_PATH, DEATH_SOUND);
        _initSoundBuffer(SOUND_EGG_PATH, EGG_SOUND);
        _initSoundBuffer(SOUND_WIN_PATH, WIN_SOUND);
        _initSoundBuffer(SOUND_LOSE_PATH, LOSE_SOUND);
    } catch (MapException &e) {
        std::cerr << e.what() << std::endl;
    }
    _initSound(SPAWN_SOUND);
    _initSound(DEATH_SOUND);
    _initSound(EGG_SOUND);
    _initSound(WIN_SOUND);
    _initSound(LOSE_SOUND);
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

void Map::_SetDefaultMapOrigin()
{
    sf::Vector2f origin;
    sf::FloatRect firstTileRect = _tile.front().get()->getGlobalBound();
    sf::FloatRect lastTileRect = _tile.back().get()->getGlobalBound();
    sf::Vector2u windowSize = _window.get()->getSize();

    origin.x = -(int(windowSize.x) / 2);
    origin.y = (((lastTileRect.top + lastTileRect.height) - firstTileRect.top) / 2 - windowSize.y / 2);
    for (auto &it : _tile) {
        it.get()->setOrigin(origin);
    }
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
        _tile.back()->setSize(sf::Vector2f(150, 150));
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

bool Map::_mapCanMove(sf::Vector2f moveMap)
{
    sf::Vector2u windowSize = _window.get()->getSize();
    sf::FloatRect topTileRect = _tile.at(0).get()->getGlobalBound();
    sf::FloatRect bottomTileRect = _tile.at(_mapSize.x * _mapSize.y - 1).get()->getGlobalBound();
    sf::FloatRect leftTileRect = _tile.at((_mapSize.y - 1) * _mapSize.x).get()->getGlobalBound();
    sf::FloatRect rightTileRect = _tile.at(_mapSize.x - 1).get()->getGlobalBound();

    if (moveMap.x < 0 && leftTileRect.left > windowSize.x / 2)
        return false;
    if (moveMap.x > 0 && rightTileRect.left + rightTileRect.width < windowSize.x / 2)
        return false;
    if (moveMap.y < 0 && topTileRect.top > windowSize.y / 2)
        return false;
    if (moveMap.y > 0 && bottomTileRect.top + bottomTileRect.height < windowSize.y / 2)
        return false;
    return true;
}

void Map::_updateMoveMap()
{
    int value = 10;
    sf::Vector2f moveMap = {0, 0};

    if (_event->isKeyPressed(sf::Keyboard::G))
        _SetDefaultMapOrigin();
    if (_event->isKeyPressed(sf::Keyboard::Z))
        moveMap.y = value;
    if (_event->isKeyPressed(sf::Keyboard::Q))
        moveMap.x = value;
    if (_event->isKeyPressed(sf::Keyboard::S))
        moveMap.y = -value;
    if (_event->isKeyPressed(sf::Keyboard::D))
        moveMap.x = -value;
    if (!_mapCanMove(moveMap))
        return;
    if (moveMap.x || moveMap.y) {
        for (auto &it : _tile) {
            it->setOrigin(it->getOrigin() + moveMap);
        }
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

void Map::addPlayer(gui::entity::Player &player)
{
    for (auto &it : _players) {
        if (it._uuid == player._uuid) {
            _tile[itop(sf::Vector2f(it.getPosition().first, it.getPosition().second))]->removePlayer(it);
            it = player;
            _tile[itop(sf::Vector2f(player.getPosition().first, player.getPosition().second))]->addPlayer(player);
            return;
        }
    }
    _sounds.at(SPAWN_SOUND)->play();
    _players.emplace_back(player);
    _tile[itop(sf::Vector2f(player.getPosition().first, player.getPosition().second))]->addPlayer(player);
    for (auto &it : _teamsNames) {
        if (it == player._team_name)
            return;
    }
    _teamsNames.push_back(player._team_name);
}

void Map::removePlayer(gui::entity::Player &player)
{
    for (auto it = _players.begin(); it != _players.end(); ++it) {
        if (it.base()->_uuid == player._uuid) {
            _tile[itop(sf::Vector2f(it.base()->getPosition().first, it.base()->getPosition().second))]->removePlayer(*it.base());
            _players.erase(it);
            _sounds.at(DEATH_SOUND)->play() ;
            return;
        }
    }
}

void Map::removeEgg(gui::entity::Egg &egg)
{
    for (auto it = _eggs.begin(); it != _eggs.end(); ++it) {
        if (it.base()->_uuid == egg._uuid) {
            _tile[itop(sf::Vector2f(it.base()->getPosition().first, it.base()->getPosition().second))]->removeEgg(*it.base());
            _eggs.erase(it);
            return;
        }
    }
}

void Map::addTilesInfo(gui::entity::Tile &tileInfo)
{
    for (auto &it : _tilesInfo) {
        if (it._position == tileInfo._position) {
            it = tileInfo;
            _tile[itop(sf::Vector2f(tileInfo.getPosition().first, tileInfo.getPosition().second))]->setTileInfo(tileInfo);
            return;
        }
    }
    _tilesInfo.emplace_back(tileInfo);
    _tile[itop(sf::Vector2f(tileInfo.getPosition().first, tileInfo.getPosition().second))]->setTileInfo(tileInfo);
}

void Map::_displayPlayers(Tile &tile)
{
    std::size_t index = 0;

    if (tile.getPlayers().size()) {
        for (index = 0; tile.getPlayers().at(0).getTeamName() != _teamsNames.at(index); index++);
        if (tile.getPlayers().size() == 0) {
            _playerAnimation.at(index % 4).setSize(sf::Vector2f(56 / 2, 188 / 2));
            _playerAnimation.at(index % 4).setDuration(400);
            _playerAnimation.at(index % 4).setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - _playerAnimation.at(index % 4).getGlobalBounds().width / 2, tile.getGlobalBound().top - 50});
            _playerAnimation.at(index % 4).update();
            _window->draw(_playerAnimation.at(index % 4).getShape());
            return;
        }
        _playerAnimation.at(4).setSize(sf::Vector2f(56 / 2, 188 / 2));
        _playerAnimation.at(4).setDuration(400);
        _playerAnimation.at(4).setPosition({tile.getGlobalBound().left + tile.getGlobalBound().width / 2 - _playerAnimation.at(index % 4).getGlobalBounds().width / 2, tile.getGlobalBound().top - 50});
        _playerAnimation.at(4).moveShape({-6, 6});
        _playerAnimation.at(4).update();
        _window->draw(_playerAnimation.at(4).getShape());
        if (tile.getPlayers().size() >= 2) {
            _playerAnimation.at(4).moveShape({-6, 6});
            _playerAnimation.at(4).update();
            _window->draw(_playerAnimation.at(4).getShape());
        }
        if (tile.getPlayers().size() >= 3) {
            _playerAnimation.at(4).moveShape({12, 0});
            _playerAnimation.at(4).update();
            _window->draw(_playerAnimation.at(4).getShape());
        }
        if (tile.getPlayers().size() >= 4) {
            _playerAnimation.at(4).moveShape({-6, 6});
            _playerAnimation.at(4).update();
            _window->draw(_playerAnimation.at(4).getShape());
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
            _ressourcesAnim.at(index - 1).setSize(sf::Vector2f(30, 30));
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
        _eggAnimation.setSize(sf::Vector2f(40, 40));
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
