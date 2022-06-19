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
}

void Interface::updateAndDisplay()
{
    _minimap.setBottomMenuPosition(_inventory.getPosition());
    _inventory.display();
    _minimap.display();
    if (_event->isKeyPressed(sf::Keyboard::M))
        _minimap.switchSize(true);
    if (!_event->isKeyPressed(sf::Keyboard::M))
        _minimap.switchSize(false);
    if (_event->isKeyPressed(sf::Keyboard::Down) || _event->isKeyPressed(sf::Keyboard::Up))
        _inventory.update(true);
    if (_event->isButtonPressed()) {
        _inventory.update();
    }
    /// This function will call class which should display something, like minimap class.
}
