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

#define FONT_PATH "assets/arial.ttf"

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
                _areaServer = {position.x, position.y, size.x, size.y};
                _updateBody();
            };
            inline void setBackgroundColor(const sf::Color &color) {
                _body.setFillColor(color);
            };
            inline void setButtonColor(const sf::Color &color) {
                _button.setFillColor(color);
            };
        private:
            void _updateBody();
            std::shared_ptr<sf::RenderWindow> _window;
            sf::RectangleShape _body;
            bool _isOpen;
            sf::ConvexShape _button;
            sf::Clock _clock;
            sf::FloatRect _areaServer;
            sf::Text _text;
            sf::Font _font;
    };
}

#endif /* !INVENTORY_HPP_ */
