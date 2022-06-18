/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ServerCommunication
*/

#include "ServerCommunication.hpp"

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
}

void ServerCommunication::_updateBody()
{
    sf::Vector2u windowSize = _window->getSize();

    if (_isOpen) {
        _body.setSize(sf::Vector2f(windowSize.x / 10, windowSize.y));
        _body.setPosition(sf::Vector2f(0, 0));
        _button.setPosition(sf::Vector2f(_body.getPosition().x + _body.getSize().x - _button.getSize().x - 10, _body.getPosition().y + 10));
    } else {
        _body.setSize(sf::Vector2f(30, windowSize.y));
        _body.setPosition(sf::Vector2f(0, 0));
        _button.setPosition(sf::Vector2f(_body.getPosition().x + 10, _body.getPosition().y + 10));
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
    if (mouse.x >= _button.getPosition().x && mouse.x <= _button.getPosition().x + _button.getSize().x) {
        if (mouse.y >= _button.getPosition().y && mouse.y <= _button.getPosition().y + _button.getSize().y) {
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
    _body.setFillColor(sf::Color::Red);
    _button.setSize(sf::Vector2f(10, 10));
    _button.setPosition(_body.getPosition().x + _body.getSize().x - _button.getSize().x - 10, _body.getPosition().y + 10);
    _body.setFillColor(sf::Color::Green);
}