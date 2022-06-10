/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ZappyGuiException
*/

#include "ZappyGuiException.hpp"

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