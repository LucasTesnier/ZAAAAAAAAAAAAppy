/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ServerCommunication
*/

#ifndef SERVERCOMMUNICATION_HPP_
#define SERVERCOMMUNICATION_HPP_

#include <memory>
#include <SFML/Graphics.hpp>

namespace gui {
    class ServerCommunication {
        public:
            ServerCommunication() = default;
            ServerCommunication(std::shared_ptr<sf::RenderWindow> window);
            ~ServerCommunication() = default;
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
                initializeShapes();
            };
            void display();
            void initializeShapes();
            inline const sf::Vector2f &getPosition() const {
                return _body.getPosition();
            };
            inline const sf::Vector2f &getSize() const {
                return _body.getSize();
            };
            void update(bool forceUpdate = false);

        private:
            void _updateBody();
            std::shared_ptr<sf::RenderWindow> _window;
            sf::RectangleShape _body;
            sf::RectangleShape _button;
            bool _isOpen;
            sf::Clock _clock;
    };
} // namespace gui

#endif /* !SERVERCOMMUNICATION_HPP_ */
