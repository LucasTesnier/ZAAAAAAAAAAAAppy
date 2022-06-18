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

void Interface::display()
{
    _minimap.setBottomMenuPosition(_inventory.getPosition());
    _inventory.display();
    _minimap.display();
    if (_event->isKeyPressed(sf::Keyboard::M))
        _minimap.switchSize(true);
    if (!_event->isKeyPressed(sf::Keyboard::M))
        _minimap.switchSize(false);
    /// This function will call class which should display something, like minimap class.
}
