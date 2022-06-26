/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SFML
*/

/// \file src/zappy_gui_src/Core/SFML/SFML.cpp

#include "SFML.hpp"

using namespace gui;

SFML::SFML(const sf::Vector2f mapSize) : _run(true)
{
    sf::ContextSettings settings;
    const std::size_t maxFps = 60;

    settings.antialiasingLevel = 8;
    _event = std::make_shared<Event>();
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1000), "Zappy", sf::Style::Close, settings);
    _window->setPosition(sf::Vector2i(0, 0));
    _window.get()->setFramerateLimit(maxFps);
    _map.setWindow(_window);
    _map.setEvent(_event);
    _map.setMapSize(mapSize);
    _interface.setEvent(_event);
    _interface.setWindow(_window);
    _interface.setMapSize(mapSize);
    _runIntroMenu = true;
    _introMenuShape.second.loadFromFile("assets/logo.png");
    _introMenuShape.first.setTexture(&_introMenuShape.second);
    _introMenuShape.first.setSize(sf::Vector2f(_window.get()->getSize().x / 100, _window.get()->getSize().y / 100));
    _introMenuShape.first.setPosition(sf::Vector2f(_window.get()->getSize().x / 2, _window.get()->getSize().y / 2) - sf::Vector2f(_introMenuShape.first.getSize().x / 2, _introMenuShape.first.getSize().y / 2));
    _clock.restart();
}

void SFML::removeEntities(std::string &type)
{
    _map.removeEntities(type);
    _interface.removeEntities(type);
}

void SFML::_changeMapSize(const sf::Vector2f mapSize)
{
    _map.setMapSize(mapSize);
    _interface.setMapSize(mapSize);
}

void SFML::_displayIntroMenu()
{
    if (_clock.getElapsedTime().asSeconds() > 3)
        _runIntroMenu = false;
    if (_introMenuShape.first.getSize().x < sf::Vector2f(_window.get()->getSize()).x || _introMenuShape.first.getSize().y < _window.get()->getSize().y) {
        _introMenuShape.first.setSize(_introMenuShape.first.getSize() + sf::Vector2f(_window.get()->getSize().x / 100, _window.get()->getSize().y / 100));
        _introMenuShape.first.setPosition(sf::Vector2f(_window.get()->getSize().x / 2, _window.get()->getSize().y / 2) - sf::Vector2f(_introMenuShape.first.getSize().x / 2, _introMenuShape.first.getSize().y / 2));
    }
    _window.get()->draw(_introMenuShape.first);
}

void SFML::display()
{
    if (_runIntroMenu) {
        _window->clear(sf::Color(127, 127, 127, 255));
        _displayIntroMenu();
        _window->display();
        return;
    }
    _getEvent();
    if (!_window->isOpen())
        _run = false;
    _window->clear(sf::Color(127, 127, 127, 255));
    _map.display();
    _interface.updateAndDisplay();
    _interface.setInventoryTilePos(_map.getSelectedTilePos());
    _interface.setInventoryTileInv(_map.getSelectedTileInventory());
    _interface.setInventoryPlayers(_map.getSelectedTilePlayers());
    _interface.setInventoryEggs(_map.getSelectedTileEggs());
    _window->display();
}

void SFML::_getEvent()
{
    sf::Event event;
    bool eventOccurs = false;

    while (_window.get()->pollEvent(event)) {
        eventOccurs = true;
        if (event.type == sf::Event::Closed) {
            _window.get()->close();
        }
        _event.get()->setMouseScrollValue(event.mouseWheelScroll.delta);
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                _window.get()->close();
            }
            if (event.key.alt || event.key.code == sf::Keyboard::RAlt || event.key.code == sf::Keyboard::LAlt) {
                _event.get()->altPressed();
                continue;
            }
            if (event.key.control || event.key.code == sf::Keyboard::RControl || event.key.code == sf::Keyboard::LControl) {
                _event.get()->ctrlPressed();
                continue;
            }
            if (event.key.shift || event.key.code == sf::Keyboard::RShift || event.key.code == sf::Keyboard::LShift) {
                _event.get()->shiftPressed();
                continue;
            }
            _event.get()->keyPressed(event.key.code);
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.alt || event.key.code == sf::Keyboard::RAlt || event.key.code == sf::Keyboard::LAlt) {
                _event.get()->altReleased();
                continue;
            }
            if (event.key.control || event.key.code == sf::Keyboard::RControl || event.key.code == sf::Keyboard::LControl) {
                _event.get()->ctrlReleased();
                continue;
            }
            if (event.key.shift || event.key.code == sf::Keyboard::RShift || event.key.code == sf::Keyboard::LShift) {
                _event.get()->shiftReleased();
                continue;
            }
            _event.get()->keyReleased();
            continue;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            _event.get()->buttonPressed(event.mouseButton.button);
            continue;
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            _event.get()->buttonReleased();
            continue;
        }
    }
    if (!eventOccurs)
        _event.get()->setMouseScrollValue(0);
}
