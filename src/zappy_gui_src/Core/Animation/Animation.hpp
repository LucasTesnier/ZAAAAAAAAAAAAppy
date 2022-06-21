/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>

namespace gui {
    class Animation {
        public:
            Animation();
            ~Animation() = default;
            void udpate();
            void addTexture(const std::string &texturePath, const sf::Vector2f &position, const sf::Vector2f &size);
            void addTexture(const sf::Image &image, const sf::Vector2f &position, const sf::Vector2f &size);
            const sf::RectangleShape &getShape() const;
            void setDuration(std::size_t duration);
            const std::size_t &getDuration() const;
            void setPosition(const sf::Vector2f &position);
            const sf::Vector2f &getPosition() const;
            void setSize(const sf::Vector2f &size);
            const sf::Vector2f &getSize() const;
        private:
            sf::RectangleShape _shape;
            std::vector<sf::Texture> _textures;
            sf::Clock _clock;
            std::size_t _duration;
            std::size_t _textureUsed;
    };
} // namespace gui

#endif /* !ANIMATION_HPP_ */
