/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui/Core/Core.cpp

#include "Core.hpp"

Core::Core(int ac, char **av)
{
    (void)ac;
    (void)av;
}

void Core::run()
{
    while (_sfml.isWorking()) {
        _sfml.display();
    }
}

Core::~Core()
{

}