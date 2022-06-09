/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SFML
*/

/// \file src/zappy_gui/Core/SFML/SFML.cpp

#include "SFML.hpp"
#include <iostream>

SFML::SFML() : _run(true)
{
    _event = std::make_shared<Event>();
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Default);
    _window.get()->setFramerateLimit(60);
}

void SFML::display()
{
    _getEvent();
    if (!_window.get()->isOpen())
        _run = false;
    _window.get()->clear(sf::Color(127, 127, 127, 255));
    _window.get()->display();
}

void SFML::_getEvent()
{
    sf::Event event;

    while (_window.get()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.get()->close();
        }
        if (event.type == sf::Event::KeyPressed) {
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
}
