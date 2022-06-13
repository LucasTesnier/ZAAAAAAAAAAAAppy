/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_

#include <SFML/Graphics.hpp>

namespace gui {
    class Tile {
        public:
            Tile();
            Tile(Tile &tile);
            Tile &operator=(const Tile &tile);
            ~Tile();
            inline void setShape(const sf::ConvexShape &shape) {
                _shape = shape;
            };
            inline const sf::ConvexShape &getShape() const {
                return _shape;
            };
            inline void setSize(const sf::Vector2f &size) {
                _size = size;
            };
            inline const sf::Vector2f &getSize() const {
                return _size;
            };
            inline void setPosition(const sf::Vector2f &position) {
                _position = position;
                _setShape();
            };
            inline const sf::Vector2f &getPosition() const {
                return _position;
            };
            inline void setOrigin(const sf::Vector2f &origin) {
                _shape.setOrigin(origin);
            };
            inline const sf::Vector2f &getOrigin() const {
                return _shape.getOrigin();
            };
            inline void setTexture(const sf::Texture &texture) {
                _shape.setTexture(&texture);
            };
            inline void setColor(const sf::Color &color) {
                _shape.setFillColor(color);
            };
            inline const sf::Color &getColor() const {
                return _shape.getFillColor();
            };
            void setTexture(const std::string &texturePath);
            bool isOnTile(sf::Vector2i mouse);
        private:
            void _setShape();
            sf::Vector2f _toIsometric(sf::Vector2f vector, sf::Vector2f angle, int zoom);
            sf::ConvexShape _shape;
            sf::Vector2f _position;
            sf::Texture _texture;
            sf::Vector2f _size;
            std::string _texturePath;
    };
}
#endif /* !TILE_HPP_ */
