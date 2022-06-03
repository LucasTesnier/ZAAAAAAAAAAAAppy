/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** GUI
*/

/// \file GUI class functions

#include "GUI.hpp"

gui::GUI::GUI(size_t width, size_t height) : _width(width), _height(height)
{
    initWindow();
}

gui::GUI::~GUI()
{
}

void gui::GUI::closeWindow()
{
    _window.close();
}

void gui::GUI::clearScreen()
{
    _window.clear();
}

void gui::GUI::initWindow(std::string const &name)
{
    _window.create(sf::VideoMode(1920, 1080), name.c_str());
}

void gui::GUI::displayScreen()
{
    _window.display();
}

void gui::GUI::displayGUI()
{
    sf::Event event;

    while (_window.isOpen()) {
        clearScreen();
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                closeWindow();
        }
    }
}