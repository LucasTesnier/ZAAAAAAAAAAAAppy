/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Interface
*/

/// \file src/zappy_gui_src/Core/Interface/Interface.cpp

#include "Interface.hpp"

using namespace gui;

Interface::Interface()
{
    _server.setBackgroundColor(BACKGROUND_COLOR);
    _server.setButtonColor(BUTTON_COLOR);
    _inventory.setBackgroundColor(BACKGROUND_COLOR);
    _inventory.setButtonColor(BUTTON_COLOR);
}

void Interface::updateAndDisplay()
{
    _minimap.setBottomMenuPosition(_inventory.getPosition());
    _inventory.setAreaServer(_server.getPosition(), _server.getSize());
    _minimap.display();
    _inventory.display();
    _server.display();
    if (_event->isKeyPressed(sf::Keyboard::M))
        _minimap.switchSize(true);
    if (!_event->isKeyPressed(sf::Keyboard::M))
        _minimap.switchSize(false);
    if (_event->isKeyPressed(sf::Keyboard::Down) || _event->isKeyPressed(sf::Keyboard::Up))
        _inventory.update(true);
    if (_event->isKeyPressed(sf::Keyboard::Left) || _event->isKeyPressed(sf::Keyboard::Right))
        _server.update(true);
    if (_event->isButtonPressed()) {
        _inventory.update();
        _server.update();
    }
    _inventory.scroll(_event.get()->getMouseScrollValue());
    _server.scroll(_event.get()->getMouseScrollValue());
}
