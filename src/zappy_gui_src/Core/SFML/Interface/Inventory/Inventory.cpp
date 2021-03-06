/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Inventory
*/

/// \file src/zappy_gui_src/Core/SFML/Interface/Inventory/Inventory.cpp

#include "Inventory.hpp"
#include "ZappyGuiException.hpp"
#include <string>

using namespace gui;

const std::vector<std::string> RESSOURCE_PATH = {
    "assets/food.png",
    "assets/linemate.png",
    "assets/deraumere.png",
    "assets/mendiane.png",
    "assets/sibur.png",
    "assets/phiras.png",
    "assets/thystame.png"};

Inventory::Inventory()
{
    std::vector<int> tmpvec = {-1, -1, -1, -1, -1, -1, -1};
    _tileInventory = tmpvec;
    _startPlayerText = 0;
}

Inventory::Inventory(std::shared_ptr<sf::RenderWindow> window)
{
    setWindow(window);
}

void Inventory::initShapes()
{
    sf::Vector2u windowSize = _window->getSize();

    _isOpen = true;
    _body.setOutlineThickness(1);
    _body.setSize(sf::Vector2f(windowSize.x, windowSize.y / 5));
    _body.setPosition(sf::Vector2f(0, windowSize.y / 5 * 4));
    _button.setPosition(sf::Vector2f(_body.getPosition().x + 10, _body.getPosition().y + 10));
    _button.setPointCount(3);
    _button.setPoint(0, {0, 10});
    _button.setPoint(1, {5, 0});
    _button.setPoint(2, {10, 10});
    if (!_font.loadFromFile(FONT_PATH))
        throw InventoryException("Inventory Exception", "Could not load font");
    _title.setFont(_font);
    _title.setCharacterSize(20);
    _title.setFillColor(sf::Color::Black);
    _title.setString("Inventory");
    _title.setPosition(sf::Vector2f(_body.getPosition().x + 40, _body.getPosition().y + 10));
}

void Inventory::display()
{
    _window->draw(_body);
    _window->draw(_button);
    if (!_isOpen)
        return;
    _window->draw(_title);
    _window->draw(_textPos);
    for (auto &t : _textsInv) {
        _window->draw(t.second.first);
        _window->draw(t.first);
    }
    for (auto &t : _textsPlayer)
        _window->draw(t);
    for (auto &t : _textsEgg)
        _window->draw(t);
}

void Inventory::initTextTilePosition()
{
    _textPos.setFont(_font);
    _textPos.setCharacterSize(20);
    _textPos.setFillColor(sf::Color::Black);
}

void Inventory::initTextTileInventory()
{
    std::pair<sf::Text, std::pair<sf::RectangleShape, sf::Texture>> text;

    for (auto &val : _tileInventory) {
        text.first.setString(std::to_string(val));
        text.second.first.setSize(sf::Vector2f(30, 30));
        _textsInv.push_back(text);
    }
    std::size_t i = 0;
    for (auto &t : _textsInv) {
        if (!t.second.second.loadFromFile(RESSOURCE_PATH[i]))
            return;
        t.second.first.setTexture(&t.second.second);
        t.first.setFont(_font);
        t.first.setFillColor(sf::Color::Black);
        t.first.setCharacterSize(20);
        i++;
    }
    setPosTextsInv();
}

void Inventory::initTextPlayer()
{
    _textsPlayer = initTextEntities(std::string("Player"));
}

void Inventory::initTextEgg()
{
    _textsEgg = initTextEntities(std::string("Egg"));
}

std::vector<sf::Text> Inventory::initTextEntities(std::string string)
{
    sf::Text text;
    std::vector<sf::Text> vecText;

    for (int i = 0; i < 4; i++)
        vecText.emplace_back(text);
    for (auto &t : vecText) {
        t.setFont(_font);
        t.setFillColor(sf::Color::Black);
        t.setCharacterSize(20);
        t.setString(string);
    }
    return vecText;
}

void Inventory::setPosTextsInv()
{
    _textsInv.at(0).first.setPosition(sf::Vector2f(_body.getPosition().x + 230, _body.getPosition().y + 80));
    _textsInv.at(1).first.setPosition(sf::Vector2f(_body.getPosition().x + 430, _body.getPosition().y + 60));
    _textsInv.at(2).first.setPosition(sf::Vector2f(_body.getPosition().x + 430, _body.getPosition().y + 120));
    _textsInv.at(3).first.setPosition(sf::Vector2f(_body.getPosition().x + 630, _body.getPosition().y + 60));
    _textsInv.at(4).first.setPosition(sf::Vector2f(_body.getPosition().x + 630, _body.getPosition().y + 120));
    _textsInv.at(5).first.setPosition(sf::Vector2f(_body.getPosition().x + 830, _body.getPosition().y + 60));
    _textsInv.at(6).first.setPosition(sf::Vector2f(_body.getPosition().x + 830, _body.getPosition().y + 120));
    for (std::size_t i = 0; i < _textsInv.size(); i++) {
        _textsInv.at(i).second.first.setPosition(_textsInv.at(i).first.getPosition() - sf::Vector2f(50, 0));
    }
}

void Inventory::setPosTextsPlayer(int x, int y, int offset)
{
    try {
        _textsPlayer.at(_startPlayerText + 0).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y));
        _textsPlayer.at(_startPlayerText + 1).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y + 60));
        _textsPlayer.at(_startPlayerText + 2).setPosition(sf::Vector2f(_body.getPosition().x + x + offset, _body.getPosition().y + y));
        _textsPlayer.at(_startPlayerText + 3).setPosition(sf::Vector2f(_body.getPosition().x + x + offset, _body.getPosition().y + y + 60));
    } catch (...) {}
}

void Inventory::setPosTextsEgg(int x, int y, int offset)
{
    if (_startPlayerText >= _textsPlayer.size())
        return;
    _textsEgg.at(0).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y));
    _textsEgg.at(1).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y + 60));
    if (_startPlayerText + 2 >= _textsPlayer.size())
        return;
    _textsEgg.at(2).setPosition(sf::Vector2f(_body.getPosition().x + x + offset, _body.getPosition().y + y));
    _textsEgg.at(3).setPosition(sf::Vector2f(_body.getPosition().x + x + offset, _body.getPosition().y + y + 60));
}

void Inventory::setPosSpritesInv()
{
    _spritesInv.at(0).setPosition(sf::Vector2f(_body.getPosition().x + 120, _body.getPosition().y + 45));
}

void Inventory::_updateBody()
{
    sf::Vector2u windowSize = _window->getSize();

    if (_isOpen) {
        _body.setSize(sf::Vector2f(windowSize.x, windowSize.y / 5));
        _body.setPosition(sf::Vector2f(_areaServer.left + _areaServer.width, windowSize.y / 5 * 4));
        _button.setPosition(sf::Vector2f(_body.getPosition().x + 10, _body.getPosition().y + 10));
        _button.setPoint(0, {0, 0});
        _button.setPoint(1, {5, 10});
        _button.setPoint(2, {10, 0});
    } else {
        _body.setSize(sf::Vector2f(windowSize.x, 30));
        _body.setPosition(sf::Vector2f(_areaServer.left + _areaServer.width, windowSize.y - 30));
        _button.setPosition(sf::Vector2f(_body.getPosition().x + 10, _body.getPosition().y + 10));
        _button.setPoint(0, {0, 10});
        _button.setPoint(1, {5, 0});
        _button.setPoint(2, {10, 10});
    }
    _title.setPosition(sf::Vector2f(_body.getPosition().x + 40, _body.getPosition().y + 10));
    if (_tilePosition.x == -1 && _tilePosition.y == -1)
        _textPos.setString(std::string("x: None\n\n\ny: None"));
    else
        _textPos.setString(std::string("x: " + std::to_string(int(_tilePosition.x)) + "\n\n\ny: " + std::to_string(int(_tilePosition.y))));
    _textPos.setPosition(sf::Vector2f(_body.getPosition().x + 50, _body.getPosition().y + 60));
    int i = 0;
    for (auto &t : _textsInv) {
        t.first.setString(std::to_string(_tileInventory.at(i)));
        i++;
    }
    std::size_t j = 0;
    for (auto &t : _textsPlayer) {
        if (_startPlayerText + j < _players.size())
            t.setString("Team: " + _players.at(_startPlayerText + j).getTeamName() +
                        "\nLevel: " + std::to_string(_players.at(_startPlayerText + j).getLevel()));
        else
            t.setString("Player");
        j++;
    }
    std::size_t k = 0;
    for (auto &t : _textsEgg) {
        if (_startEggText + k < _eggs.size())
            t.setString("Team: " + _eggs.at(_startEggText + k).getTeamName());
        else
            t.setString("Egg");
        k++;
    }
    setPosTextsInv();
    setPosTextsPlayer(1030, 50, 150);
    setPosTextsEgg(1330, 50, 150);
}

bool Inventory::_isButtonClicked(sf::Vector2i mouse)
{
    if (mouse.x >= _button.getPosition().x && mouse.x <= _button.getPosition().x + _button.getGlobalBounds().width)
        if (mouse.y >= _button.getPosition().y && mouse.y <= _button.getPosition().y + _button.getGlobalBounds().height)
            return true;
    return false;
}

void Inventory::update(bool forceUpdate)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window);

    if (_clock.getElapsedTime().asSeconds() < 0.2)
        return;
    if (forceUpdate) {
        _isOpen = (_isOpen) ? false : true;
        _updateBody();
        _clock.restart();
        return;
    }
    if (_isButtonClicked(mouse)) {
        _isOpen = (_isOpen) ? false : true;
        _updateBody();
        _clock.restart();
    }
}

void Inventory::scroll(const float &scroll __attribute__((unused)))
{
}
