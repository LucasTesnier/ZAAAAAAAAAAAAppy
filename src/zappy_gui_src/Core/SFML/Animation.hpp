/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

namespace gui {
    class Animation {
        public:
            /// \brief The default constructor. It will set all variable with a default NULL value
            Animation();
            /// \brief The default destructor
            ~Animation() = default;
            /// \brief Update the state of the animation. Increment the index of the texture use, if necessary, and restart the clock
            void update();
            /// \brief Get the sprite of the animation to be drawn.
            /// \return The return value is a const sf::Sprite reference of the sprite use in the class
            const sf::Sprite &getSprite() const;
            /// \brief Set the duration of the animation
            /// \return The duration as millisecond
            void setDuration(std::size_t duration);
            /// \brief Get the duration of the animation
            /// \return The return value is the duration of the animation as millisecond
            const std::size_t &getDuration() const;
            /// \brief Add a texture to the texture's vector. The texture is created from the texturePath, and use the position inside the image loaded and a side to get the texture. If it is set to 0, it will not used.
            /// \param texturePath The path of the texture
            /// \param position The position in the image
            /// \param size The size in the image
            void addTexture(const std::string &texturePath, const sf::Vector2f &position, const sf::Vector2f &size);
            /// \brief Set the position of the sprite
            /// \return The position
            void setPosition(const sf::Vector2f &position);
            /// \brief Get the position of the sprite
            /// \return the position
            const sf::Vector2f &getPosition() const;
            /// \brief Set the size of the sprite
            /// \param size The size
            void setSize(const sf::Vector2f &size);
            /// \brief Get the size of the sprite
            /// \return the size
            const sf::Vector2f &getSize() const;
        protected:
        private:
            /// \brief The sprite to be display on the screen
            sf::Sprite _sprite;
            /// \brief The vector of texture to be set to the sprite
            std::vector<sf::Texture> _textures;
            /// \brief The clock of the animation
            sf::Clock _clock;
            /// \brief Time between each texture update
            sf::Time _duration;
    };
}

#endif /* !ANIMATION_HPP_ */
