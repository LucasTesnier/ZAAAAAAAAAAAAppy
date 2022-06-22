/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation
*/

/// \file src/zappy_gui_src/Core/Animation/Animation.cpp

#include "Animation.hpp"
#include "ZappyGuiException.hpp"

using namespace gui;

Animation::Animation()
{
    _textures.clear();
    _clock.restart();
    _duration = 0;
    _textureUsed = 0;
}

void Animation::udpate()
{
    if (std::size_t(_clock.getElapsedTime().asMilliseconds()) > _duration) {
        _textureUsed++;
        if (_textureUsed >= _textures.size())
            _textureUsed = 0;
        _shape.setTexture(&_textures[_textureUsed]);
        _clock.restart();
    }
}

void Animation::addTexture(const std::string &texturePath, const sf::Vector2f &position, const sf::Vector2f &size)
{
    sf::Image image;

    if (!image.loadFromFile(texturePath))
        throw AnimationException("Animation Exception", "Load image with file path failed");
    addTexture(image, position, size);
}

void Animation::addTexture(const sf::Image &image, const sf::Vector2f &position, const sf::Vector2f &size)
{
    sf::Texture texture;

    if (!texture.loadFromImage(image, sf::IntRect(position.x, position.y, size.x, size.y)))
        throw AnimationException("Animation Exception", "Load texture with image failed");
    _textures.push_back(texture);
    _shape.setTexture(&_textures.back());
}

const sf::RectangleShape &Animation::getShape() const
{
    return _shape;
}

void Animation::setDuration(std::size_t duration)
{
    _duration = duration;
}

const std::size_t &Animation::getDuration() const
{
    return _duration;
}

void Animation::setPosition(const sf::Vector2f &position)
{
    _shape.setPosition(position);
}

const sf::Vector2f &Animation::getPosition() const
{
    return _shape.getPosition();
}

void Animation::setSize(const sf::Vector2f &size)
{
    _shape.setSize(size);
}

const sf::Vector2f &Animation::getSize() const
{
    return _shape.getSize();
}
