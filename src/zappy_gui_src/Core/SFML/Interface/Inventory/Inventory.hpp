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
#include <utility>

#define FONT_PATH "assets/arial.ttf"
#define FOOD_PATH "assets/burger.png"

namespace gui {
    class Inventory {
        public:
            Inventory();
            Inventory(std::shared_ptr<sf::RenderWindow> window);
            ~Inventory();
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
                initShapes();
                initTilePosition();
                initTileInventory();
            };
            void display();
            void initTilePosition();
            void initTileInventory();
            void setPosTextsInv();
            void setPosSpritesInv();
            void initShapes();
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
            inline void setBackgroundColor(const sf::Color &color) {
                _body.setFillColor(color);
            };
            inline void setButtonColor(const sf::Color &color) {
                _button.setFillColor(color);
            };
            inline void setTilePosition(const sf::Vector2f &tilePosition) {
                _tilePosition = tilePosition;
            }
            inline void setTileInventory(std::vector<int> tileInventory) {
                _tileInventory = tileInventory;
            }
        private:
            void _updateBody();
            std::shared_ptr<sf::RenderWindow> _window;
            sf::RectangleShape _body;
            bool _isOpen;
            sf::ConvexShape _button;
            sf::Clock _clock;
            sf::FloatRect _areaServer;
            sf::Text _text;
            sf::Text _textPos;
            sf::Font _font;
            std::vector<sf::Text> _textsInv;
            std::vector<sf::Sprite> _spritesInv;
            sf::Vector2f _tilePosition;
            std::vector<int> _tileInventory;
            std::vector<std::string> _players;
            std::vector<std::string> _eggs;
    };
}

#endif /* !INVENTORY_HPP_ */
