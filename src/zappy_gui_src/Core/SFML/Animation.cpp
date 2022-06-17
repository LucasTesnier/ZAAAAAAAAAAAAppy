/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** Animation
*/

#include "Animation.hpp"

using namespace gui;

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::update()
{

}

const sf::Sprite &Animation::getSprite() const
{
    return _sprite;
}

void Animation::setDuration(std::size_t duration)
{
    _duration = sf::milliseconds(duration);
}

const std::size_t &Animation::getDuration() const
{
    return _duration.asMilliseconds();
}

void Animation::addTexture(const std::string &texturePath, const sf::Vector2f &position, const sf::Vector2f &size)
{

}

void Animation::setPosition(const sf::Vector2f &position)
{
    _sprite.setPosition(position);
}

const sf::Vector2f &Animation::getPosition() const
{
    return _sprite.getPosition();
}

void Animation::setSize(const sf::Vector2f &size)
{
    // TODO change size
    _sprite.setScale(size);
}

const sf::Vector2f &Animation::getSize() const
{
    // TODO get size
    return _sprite.getScale();
}