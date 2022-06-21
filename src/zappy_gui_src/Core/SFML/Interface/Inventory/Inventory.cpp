/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Inventory
*/

#include "Inventory.hpp"
#include "ZappyGuiException.hpp"
#include <string>
#include <iostream>

using namespace gui;

Inventory::Inventory()
{
    _tileInventory.emplace_back(190);
    _tileInventory.emplace_back(1);
    _tileInventory.emplace_back(2);
    _tileInventory.emplace_back(3);
    _tileInventory.emplace_back(4);
    _tileInventory.emplace_back(5);
    _tileInventory.emplace_back(6);
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
    _text.setFont(_font);
    _text.setCharacterSize(16);
    _text.setFillColor(sf::Color::Black);
    _text.setString("Inventory");
    _text.setPosition(_body.getPosition().x + 40, _body.getPosition().y + 10);
}

void Inventory::display()
{
    _window->draw(_body);
    _window->draw(_button);
    if (!_isOpen)
        return;
    _window->draw(_text);
    _window->draw(_textPos);
    for (auto &t : _textsInv)
        _window->draw(t);
    for (auto &s : _spritesInv)
        _window->draw(s);
}

void Inventory::initTilePosition()
{
    _textPos.setFont(_font);
    _textPos.setCharacterSize(20);
    _textPos.setFillColor(sf::Color::Black);
    _textPos.setString(std::string("x: " + std::to_string(int(_tilePosition.x)) + "\n\n\ny: " + std::to_string(int(_tilePosition.y))));
    _textPos.setPosition(_body.getPosition().x + 50, _body.getPosition().y + 60);
}

void Inventory::initTileInventory()
{
    sf::Texture texture;
    sf::Sprite sprite;
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
    if (!texture.loadFromFile(FOOD_PATH)) {
        throw InventoryException("Inventory Exception", "Could not load texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.2, 0.2);
    sprite.setPosition(_body.getPosition().x + 120, _body.getPosition().y + 45);
    _spritesInv.push_back(sprite);
}

void Inventory::setPosTextsInv()
{
    _textsInv.at(0).setPosition(_body.getPosition().x + 230, _body.getPosition().y + 80);
    _textsInv.at(1).setPosition(_body.getPosition().x + 430, _body.getPosition().y + 60);
    _textsInv.at(2).setPosition(_body.getPosition().x + 430, _body.getPosition().y + 120);
    _textsInv.at(3).setPosition(_body.getPosition().x + 630, _body.getPosition().y + 60);
    _textsInv.at(4).setPosition(_body.getPosition().x + 630, _body.getPosition().y + 120);
    _textsInv.at(5).setPosition(_body.getPosition().x + 830, _body.getPosition().y + 60);
    _textsInv.at(6).setPosition(_body.getPosition().x + 830, _body.getPosition().y + 120);
}

void Inventory::setPosSpritesInv()
{
    _spritesInv.at(0).setPosition(_body.getPosition().x + 120, _body.getPosition().y + 45);
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
    _text.setPosition(_body.getPosition().x + 40, _body.getPosition().y + 10);
    _textPos.setPosition(_body.getPosition().x + 50, _body.getPosition().y + 60);
    _textPos.setString(std::string("x: " + std::to_string(int(_tilePosition.x)) + "\n\n\ny: " + std::to_string(int(_tilePosition.y))));
    setPosTextsInv();
    setPosSpritesInv();
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
    if (mouse.x >= _button.getPosition().x && mouse.x <= _button.getPosition().x + _button.getGlobalBounds().width) {
        if (mouse.y >= _button.getPosition().y && mouse.y <= _button.getPosition().y + _button.getGlobalBounds().height) {
            _isOpen = (_isOpen) ? false : true;
            _updateBody();
            _clock.restart();
        }
    }
}

Inventory::~Inventory()
{
}
