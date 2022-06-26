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

void ServerCommunication::addTilesInfo(gui::entity::Tile &tile)
{
    for (auto &it : _tiles) {
        if (it._position == tile._position) {
            it = tile;
            _updateText();
            return;
        }
    }
    _tiles.push_back(tile);
    _updateText();
}

void ServerCommunication::addPlayer(gui::entity::Player &player)
{
    for (gui::entity::Player &it : _players) {
        if (it._uuid == player._uuid) {
            it = player;
            return;
        }
    }
    _players.push_back(player);
    _updateText();
}

void ServerCommunication::removePlayer(gui::entity::Player &player)
{
    for (auto it = _players.begin(); it != _players.end(); ++it) {
        if (it.base()->_uuid == player._uuid) {
            _players.erase(it);
            break;
        }
    }
    _updateText();
}

void ServerCommunication::removeEgg(gui::entity::Egg &egg)
{
    for (auto it = _eggs.begin(); it != _eggs.end(); ++it) {
        if (it.base()->_uuid == egg._uuid) {
            _eggs.erase(it);
            break;
        }
    }
    _updateText();
}

void ServerCommunication::_updateBody()
{
    sf::Vector2u windowSize = _window->getSize();

    if (_isOpen) {
        _body.setSize(sf::Vector2f(windowSize.x / 8, windowSize.y));
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
    _body.setSize(sf::Vector2f(window.x / 8, window.y));
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

void ServerCommunication::scroll(const float &scrollValue)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window);

    if (mouse.x >= 0 && mouse.x <= _body.getSize().x && mouse.y >= 0 && mouse.y <= _body.getSize().y) {
        if ((_text.getPosition().y < 0 && scrollValue > 0) || (_text.getPosition().y + _text.getGlobalBounds().height > _window.get()->getSize().y && scrollValue < 0))
            _text.move(sf::Vector2f(0, scrollValue * 20));
    }
}

std::string ServerCommunication::_inventoryToString(const std::vector<int> &inventory)
{
    std::string inventoryAsString;

    inventoryAsString.append("\tInventory:\n");
    inventoryAsString.append("\t\tFood: ");
    inventoryAsString.append(std::to_string(inventory[0]));
    inventoryAsString.append("\n");
    inventoryAsString.append("\t\tLinemate: ");
    inventoryAsString.append(std::to_string(inventory[1]));
    inventoryAsString.append("\n");
    inventoryAsString.append("\t\tDeraumere: ");
    inventoryAsString.append(std::to_string(inventory[2]));
    inventoryAsString.append("\n");
    inventoryAsString.append("\t\tSibur: ");
    inventoryAsString.append(std::to_string(inventory[3]));
    inventoryAsString.append("\n");
    inventoryAsString.append("\t\tMendiane: ");
    inventoryAsString.append(std::to_string(inventory[4]));
    inventoryAsString.append("\n");
    inventoryAsString.append("\t\tPhiras: ");
    inventoryAsString.append(std::to_string(inventory[5]));
    inventoryAsString.append("\n");
    inventoryAsString.append("\t\tThystame: ");
    inventoryAsString.append(std::to_string(inventory[6]));
    inventoryAsString.append("\n");
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
