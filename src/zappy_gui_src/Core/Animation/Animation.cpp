/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation
*/

#include "Animation.hpp"

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
    if (_clock.getElapsedTime().asMilliseconds() > _duration) {
        _textureUsed++;
        if (_textureUsed >= _textures.size())
            _textureUsed = 0;
        _sprite.setTexture(_textures[_textureUsed]);
        _clock.restart();
    }
}

void Animation::addTexture(const std::string &texturePath, const sf::Vector2f &position, const sf::Vector2f &size)
{
    sf::Image image;
    sf::Texture texture;

    if (!image.loadFromFile(texturePath))
        throw std::exception();
    texture.loadFromImage(image, sf::IntRect(position.x, position.y, size.x, size.y));
    _textures.push_back(texture);
}

const sf::Sprite &Animation::getSprite() const
{
    return _sprite;
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
    _sprite.setPosition(position);
}

