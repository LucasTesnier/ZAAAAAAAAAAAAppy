/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML()
{
    sf::ContextSettings settings;

    settings.antialiasingLevel = 8;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), "zappy_gui", sf::Style::Default, settings);
    _window->setFramerateLimit(60);
    _isWorking = true;
    map.setWindow(_window);
}

void SFML::display()
{
    while (_window->pollEvent(_event)) {
    if (_event.type == sf::Event::Closed || (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape))
        _window->close();
    }
    _isWorking = _window->isOpen();
    _window->clear();
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
