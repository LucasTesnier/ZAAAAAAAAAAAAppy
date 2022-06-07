/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SFML
*/

/// \file src/zappy_gui/Core/SFML/SFML.cpp

#include "SFML.hpp"

SFML::SFML()
{
    sf::ContextSettings settings;

    settings.antialiasingLevel = 8;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), "zappy_gui", sf::Style::Default, settings);
    _window->setFramerateLimit(60);
    _isWorking = true;
    map.setWindow(_window);
    map.setSize(10, 10);
}

void SFML::display()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed || (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape))
            _window->close();
        if (_event.type == sf::Event::KeyPressed) {
            map.move(_event.key.code);
            if (_event.key.code == sf::Keyboard::Add)
                map.setSize(map.getSize().x + 1, map.getSize().y + 1);
            if (_event.key.code == sf::Keyboard::Subtract)
                map.setSize(map.getSize().x - 1, map.getSize().y - 1);
        }
    }
    _isWorking = _window->isOpen();
    _window->clear(sf::Color(127, 127, 127, 255));
    map.draw();
    _window->display();
}

bool SFML::isWorking() const
{
    return _isWorking;
}

SFML::~SFML()
{
    delete _window;
}
