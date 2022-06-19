/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Inventory
*/

#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

namespace gui {
    class Inventory {
        public:
            Inventory();
            Inventory(std::shared_ptr<sf::RenderWindow> window);
            ~Inventory();
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
                initialize_shapes();
            };
            void display();
            void initialize_shapes();
            inline const sf::Vector2f &getPosition() const {
                return _body.getPosition();
            };
            void update(bool forceUpdate = false);
        private:
            void _updateBody();
            std::shared_ptr<sf::RenderWindow> _window;
            sf::RectangleShape _body;
            bool _isOpen;
            sf::RectangleShape _button;
            sf::Clock _clock;
    };
}

#endif /* !INVENTORY_HPP_ */