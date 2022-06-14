/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Tile
*/

/// \file src/zappy_gui_src/Core/SFML/Map/Tile.hpp

#ifndef TILE_HPP_
#define TILE_HPP_

#include <SFML/Graphics.hpp>

namespace gui {
    /// \brief Class for the tile that will be display on the map.
    class Tile {
        public:

            /// \brief Constructor of the tile.
            Tile();

            /// \brief Copy constructor of the tile.
            /// \param tile The tile to copy.
            Tile(Tile &tile);

            /// \brief Copy constructor of the tile.
            /// \param tile The tile to copy.
            /// \return The new tile.
            Tile operator=(const Tile &tile);

            /// \brief Destructor of the tile.
            ~Tile();

            /// \brief Set the convex shape of the tile.
            /// \param shape The shape of the tile.
            inline void setShape(const sf::ConvexShape &shape) {
                _shape = shape;
            };

            /// \brief Get the convex shape of the tile.
            /// \return The shape of the tile.
            inline const sf::ConvexShape &getShape() const {
                return _shape;
            };

            /// \brief Set the size of the tile.
            /// \param size The size of the tile.
            inline void setSize(const sf::Vector2f &size) {
                _size = size;
                _setShape();
            };

            /// \brief Get the size of the tile.
            /// \return The size of the tile.
            inline const sf::Vector2f &getSize() const {
                return _size;
            };

            /// \brief Set the position of the tile.
            /// \param position The position of the tile.
            inline void setPosition(const sf::Vector2f &position) {
                _position = position;
                _setShape();
            };

            /// \brief Get the position of the tile.
            /// \return The position of the tile.
            inline const sf::Vector2f &getPosition() const {
                return _position;
            };

            /// \brief Set the origin of the tile.
            /// \param origin The origin of the tile.
            inline void setOrigin(const sf::Vector2f &origin) {
                _shape.setOrigin(origin);
            };

            /// \brief Get the origin of the tile.
            /// \return The origin of the tile.
            inline const sf::Vector2f &getOrigin() const {
                return _shape.getOrigin();
            };

            /// \brief Set the texture of the tile.
            /// \param texture The texture of the tile.
            inline void setTexture(const sf::Texture &texture) {
                _shape.setTexture(&texture);
            };

            /// \brief Set the color of the tile.
            /// \param color The color of the tile.
            inline void setColor(const sf::Color &color) {
                _shape.setFillColor(color);
            };

            /// \brief Get the color of the tile.
            /// \return The color of the tile.
            inline const sf::Color &getColor() const {
                return _shape.getFillColor();
            };

            /// \brief Set the texture of the tile.
            /// \param texturePath The path of the texture to be load.
            void setTexture(const std::string &texturePath);

            /// \brief Check if the mouse is on the tile.
            /// \param mouse The mouse to check.
            /// \return True if the mouse is on the tile, false otherwise.
            bool isOnTile(sf::Vector2i mouse);
            int isOnRight(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2i mouse);
        private:

            /// \brief Set the points of the tile.
            void _setShape();

            /// \brief Move a point to an isometric view.
            /// \param vector The point to move.
            /// \param angle The angle of the view.
            /// \param zoom The zoom of the view.
            sf::Vector2f _toIsometric(sf::Vector2f vector, sf::Vector2f angle, int zoom);

            /// \brief Convex shape of the tile.
            sf::ConvexShape _shape;

            /// \brief Position of the tile.
            sf::Vector2f _position;

            /// \brief Texture of the tile.
            sf::Texture _texture;

            /// \brief Size of the tile.
            sf::Vector2f _size;

            /// \brief Texture path of the tile.
            std::string _texturePath;
    };
} // gui namespace

#endif /* !TILE_HPP_ */
