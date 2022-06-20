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
            inline void setAreaServer(const sf::Vector2f &position, const sf::Vector2f &size) {
                sf::FloatRect temp;
                temp.left = position.x;
                temp.top = position.y;
                temp.width = size.x;
                temp.height = size.y;
                _areaServer = temp;
                _updateBody();
            };
        private:
            void _updateBody();
            std::shared_ptr<sf::RenderWindow> _window;
            sf::RectangleShape _body;
            bool _isOpen;
            sf::RectangleShape _button;
            sf::Clock _clock;
            sf::FloatRect _areaServer;
    };
}

#endif /* !INVENTORY_HPP_ */
