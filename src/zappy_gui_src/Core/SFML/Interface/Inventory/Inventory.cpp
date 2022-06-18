/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Inventory
*/

#include "Inventory.hpp"

using namespace gui;

Inventory::Inventory()
{
}

Inventory::Inventory(std::shared_ptr<sf::RenderWindow> window)
{
    setWindow(window);
}

void Inventory::initialize_shapes()
{
    sf::Vector2u windowSize = _window->getSize();

    _body.setSize(sf::Vector2f(windowSize.x, windowSize.y / 5));
    _body.setPosition(sf::Vector2f(0, windowSize.y / 5 * 4));
    _body.setFillColor(sf::Color::Cyan);
    _button.setPosition(sf::Vector2f(_body.getPosition().x + 10, _body.getPosition().y + 10));
    _button.setSize(sf::Vector2f(10, 10));
    _button.setFillColor(sf::Color::Magenta);
}

void Inventory::display()
{
    _window->draw(_body);
    _window->draw(_button);
}

Inventory::~Inventory()
{
}

