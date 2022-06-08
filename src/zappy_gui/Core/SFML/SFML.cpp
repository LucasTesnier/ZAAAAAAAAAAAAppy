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
    _eventHandling();
    _isWorking = _window->isOpen();
    _window->clear(sf::Color(127, 127, 127, 255));
    if (_event.isKeyPressed(sf::Keyboard::Z) || _event.isKeyPressed(sf::Keyboard::Up))
        map.move(Map::UP);
    if (_event.isKeyPressed(sf::Keyboard::S) || _event.isKeyPressed(sf::Keyboard::Down))
        map.move(Map::DOWN);
    if (_event.isKeyPressed(sf::Keyboard::Q) || _event.isKeyPressed(sf::Keyboard::Left))
        map.move(Map::LEFT);
    if (_event.isKeyPressed(sf::Keyboard::D) || _event.isKeyPressed(sf::Keyboard::Right))
        map.move(Map::RIGHT);
    map.selectTile();
    map.draw();
    _window->display();
}

bool SFML::isWorking() const
{
    return _isWorking;
}

void SFML::_eventHandling()
{
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            _window->close();
            _isWorking = false;
        }
        if (event.type == sf::Event::KeyPressed) {
            _event.keyPressed(event.key.code);
            if (event.key.alt)
                _event.altPressed();
            if (event.key.control)
                _event.ctrlPressed();
            if (event.key.shift)
                _event.shiftPressed();
        }
        if (event.type == sf::Event::KeyReleased) {
            _event.keyReleased();
            if (event.key.alt)
                _event.altReleased();
            if (event.key.control)
                _event.ctrlReleased();
            if (event.key.shift)
                _event.shiftReleased();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            _event.mousePressed(event.mouseButton.button);
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            _event.mouseReleased();
        }
        if (event.type == sf::Event::MouseWheelScrolled)
            _event.wheelScroll(event.mouseWheelScroll.delta);
    }
}

SFML::Event::Event()
{
    _keyPressed = false;
    _mousePressed = false;
    _altPressed = false;
    _ctrlPressed = false;
    _shiftPressed = false;
    _wheelScrolled = false;
    _key = sf::Keyboard::A;
    _button = sf::Mouse::Left;
    _delta = 0;
}

void SFML::Event::altPressed()
{
    _altPressed = true;
}

void SFML::Event::altReleased()
{
    _altPressed = false;
}

void SFML::Event::ctrlPressed()
{
    _ctrlPressed = true;
}

void SFML::Event::ctrlReleased()
{
    _ctrlPressed = false;
}

void SFML::Event::shiftPressed()
{
    _shiftPressed = true;
}

void SFML::Event::shiftReleased()
{
    _shiftPressed = false;
}

void SFML::Event::keyPressed(sf::Keyboard::Key key)
{
    _keyPressed = true;
    _key = key;
}

void SFML::Event::keyReleased()
{
    _keyPressed = false;
}

void SFML::Event::mousePressed(sf::Mouse::Button button)
{
    _mousePressed = true;
    _button = button;
}

void SFML::Event::mouseReleased()
{
    _mousePressed = false;
}

void SFML::Event::wheelScroll(float delta)
{
    _wheelScrolled = true;
    _delta = delta;
}

SFML::~SFML()
{
    delete _window;
}
