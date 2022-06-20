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

    _body.setSize(sf::Vector2f(window.x / 10, window.y));
    _body.setPosition(sf::Vector2f(0, 0));
    _button.setPointCount(3);
    _button.setPoint(0, {10, 0});
    _button.setPoint(1, {0, 5});
    _button.setPoint(2, {10, 10});
    _button.setPosition(_body.getPosition().x + _body.getSize().x - _button.getGlobalBounds().width - 10, _body.getPosition().y + 10);
    if (!_font.loadFromFile(FONT_PATH))
        throw (ServerCommunicationException("Server communication", "Could not load font"));
    _text.setPosition(_body.getPosition().x + 10, _body.getPosition().y + 10);
    _text.setFillColor(sf::Color::White);
    _text.setFont(_font);
    _text.setString("Server communication");
    _text.setCharacterSize(16);
}
