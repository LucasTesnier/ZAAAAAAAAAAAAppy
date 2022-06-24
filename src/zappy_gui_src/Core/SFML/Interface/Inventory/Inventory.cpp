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

Inventory::Inventory()
{
    std::vector<int> tmpvec = {-1, -1, -1, -1, -1, -1, -1};
    _tileInventory = tmpvec;
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
    for (auto &t : _textsInv)
        _window->draw(t);
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
    sf::Text text;

    for (auto &val : _tileInventory) {
        text.setString(std::to_string(val));
        _textsInv.push_back(text);
    }
    for (auto &t : _textsInv) {
        t.setFont(_font);
        t.setFillColor(sf::Color::Black);
        t.setCharacterSize(20);
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
    _textsInv.at(0).setPosition(sf::Vector2f(_body.getPosition().x + 230, _body.getPosition().y + 80));
    _textsInv.at(1).setPosition(sf::Vector2f(_body.getPosition().x + 430, _body.getPosition().y + 60));
    _textsInv.at(2).setPosition(sf::Vector2f(_body.getPosition().x + 430, _body.getPosition().y + 120));
    _textsInv.at(3).setPosition(sf::Vector2f(_body.getPosition().x + 630, _body.getPosition().y + 60));
    _textsInv.at(4).setPosition(sf::Vector2f(_body.getPosition().x + 630, _body.getPosition().y + 120));
    _textsInv.at(5).setPosition(sf::Vector2f(_body.getPosition().x + 830, _body.getPosition().y + 60));
    _textsInv.at(6).setPosition(sf::Vector2f(_body.getPosition().x + 830, _body.getPosition().y + 120));
}

void Inventory::setPosTextsPlayer(int x, int y, int offset)
{
    _textsPlayer.at(0).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y));
    _textsPlayer.at(1).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y + 60));
    _textsPlayer.at(2).setPosition(sf::Vector2f(_body.getPosition().x + x + offset, _body.getPosition().y + y));
    _textsPlayer.at(3).setPosition(sf::Vector2f(_body.getPosition().x + x + offset, _body.getPosition().y + y + 60));
}

void Inventory::setPosTextsEgg(int x, int y, int offset)
{
    _textsEgg.at(0).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y));
    _textsEgg.at(1).setPosition(sf::Vector2f(_body.getPosition().x + x, _body.getPosition().y + y + 60));
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
        t.setString(std::to_string(_tileInventory.at(i)));
        i++;
    }
    std::size_t j = 0;
    for (auto &t : _textsPlayer) {
        if (_players.empty())
            t.setString("Player");
        else if (j < _players.size())
            t.setString("Team: " + _players.at(j).getTeamName() +
                        "\nLevel: " + std::to_string(_players.at(j).getLevel()));
        j++;
    }
    std::size_t k = 0;
    for (auto &t : _textsEgg) {
        if (_eggs.empty())
            t.setString("Egg");
        else if (k < _eggs.size())
            t.setString("Team: " + _eggs.at(k).getTeamName());
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

