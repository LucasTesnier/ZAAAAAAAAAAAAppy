/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ZappyGuiException
*/

#include "ZappyGuiException.hpp"

using namespace gui;

ZappyGuiException::ZappyGuiException(std::string title, std::string description)
{
    _title = title;
    _description = description;
    _what = _title + ": " + description;
}

const char *ZappyGuiException::what() const noexcept
{
    return _what.c_str();
}

CoreException::CoreException(std::string title, std::string description) : ZappyGuiException(title, description)
{
}

ServerCommunicationException::ServerCommunicationException(std::string title, std::string description) : ZappyGuiException(title, description)
{
}

TileException::TileException(std::string title, std::string description) : ZappyGuiException(title, description)
{
}

AnimationException::AnimationException(std::string title, std::string description) : ZappyGuiException(title, description)
{
}
