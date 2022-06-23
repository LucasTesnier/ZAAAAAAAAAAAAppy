/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ServerCommunication
*/

#include "ServerCommunication.hpp"
#include "ZappyGuiException.hpp"

using namespace gui;

ServerCommunication::ServerCommunication()
{
    _isOpen = true;
}

ServerCommunication::ServerCommunication(std::shared_ptr<sf::RenderWindow> window)
{
    _window = window;
}

void ServerCommunication::display()
{
    _window->draw(_body);
    _window->draw(_button);
    if (!_isOpen)
        return;
    _window->draw(_text);
}

void ServerCommunication::_updateBody()
{
    sf::Vector2u windowSize = _window->getSize();

    if (_isOpen) {
        _body.setSize(sf::Vector2f(windowSize.x / 10, windowSize.y));
        _body.setPosition(sf::Vector2f(0, 0));
        _button.setPosition(sf::Vector2f(_body.getPosition().x + _body.getSize().x - _button.getGlobalBounds().width - 10, _body.getPosition().y + 10));
        _button.setPoint(0, {10, 0});
        _button.setPoint(1, {0, 5});
        _button.setPoint(2, {10, 10});
    } else {
        _body.setSize(sf::Vector2f(30, windowSize.y));
        _body.setPosition(sf::Vector2f(0, 0));
        _button.setPosition(sf::Vector2f(_body.getPosition().x + 10, _body.getPosition().y + 10));
        _button.setPoint(0, {0, 0});
        _button.setPoint(1, {10, 5});
        _button.setPoint(2, {0, 10});
    }
}

void ServerCommunication::update(bool forceUpdate)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window);

    if (_clock.getElapsedTime().asSeconds() < 0.2) {
        return;
    }
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

void ServerCommunication::initializeShapes()
{
    sf::Vector2u window = _window->getSize();
    sf::Vector2f pos;

    _body.setOutlineThickness(1);
    _body.setSize(sf::Vector2f(window.x / 10, window.y));
    _body.setPosition(sf::Vector2f(0, 0));
    _button.setPointCount(3);
    _button.setPoint(0, {10, 0});
    _button.setPoint(1, {0, 5});
    _button.setPoint(2, {10, 10});
    pos.x = _body.getPosition().x + _body.getSize().x - _button.getGlobalBounds().width - 10;
    pos.y = _body.getPosition().y + 10;
    _button.setPosition(pos);
    if (!_font.loadFromFile(FONT_PATH))
        throw (ServerCommunicationException("Server communication", "Could not load font"));
    pos.x = _body.getPosition().x + 10;
    pos.y =  _body.getPosition().y + 10;
    _text.setPosition(pos);
    _text.setFillColor(sf::Color::White);
    _text.setFont(_font);
    _text.setString("Server communication");
    _text.setCharacterSize(16);
}

void ServerCommunication::removeEntities(std::string &type)
{
    if (type == "tile") {
        _tiles.clear();
    }
    if (type == "player") {
        _players.clear();
    }
    if (type == "egg") {
        _eggs.clear();
    }
    _updateText();
}

std::string ServerCommunication::_inventoryToString(const std::vector<int> &inventory)
{
    std::string inventoryAsString;

    inventoryAsString.append("\tInventory:\n");
    inventoryAsString.append("\t\tFood: " + std::to_string(inventory[0]) + "\n");
    inventoryAsString.append("\t\tLinemate: " + std::to_string(inventory[1]) + "\n");
    inventoryAsString.append("\t\tDeraumere: " + std::to_string(inventory[2]) + "\n");
    inventoryAsString.append("\t\tSibur: " + std::to_string(inventory[3]) + "\n");
    inventoryAsString.append("\t\tMendiane: " + std::to_string(inventory[4]) + "\n");
    inventoryAsString.append("\t\tPhiras: " + std::to_string(inventory[5]) + "\n");
    inventoryAsString.append("\t\tThystame: " + std::to_string(inventory[6]) + "\n");
    return inventoryAsString;
}

void ServerCommunication::_updateText()
{
    _serverInformation.clear();
    _serverInformation.append("SERVER COMMUNICATION\n");
    _serverInformation.append("PLAYERS\n");
    for (auto it : _players) {
        _serverInformation.append("\tPosition: " + std::to_string(it._position.first) + ", " + std::to_string(it._position.second) + "\n");
        _serverInformation.append("\tTeam name: " + it._team_name + "\n");
        _serverInformation.append("\tLevel: " + std::to_string(it._level) + "\n");
        _serverInformation.append(_inventoryToString(it._inventory));
    }
    _serverInformation.append("EGGS\n");
    for (auto it : _eggs) {
        _serverInformation.append("\tPosition: " + std::to_string(it._position.first) + ", " + std::to_string(it._position.second) + "\n");
        _serverInformation.append("\tTeam name: " + it._team_name + "\n");
    }
    _serverInformation.append("TILES\n");
    for (auto it : _tiles) {
        _serverInformation.append(std::string(std::to_string(it._position.first) + ", " + std::to_string(it._position.second)) + "\n");
        _serverInformation.append(_inventoryToString(it._inventory));
    }
    _text.setString(_serverInformation);
}
