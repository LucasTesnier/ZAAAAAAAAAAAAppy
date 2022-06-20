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
#include <memory>
#include <iostream>
#include "Entity.hpp"

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

            /// \brief Get the global position of the shape when it is in isometric view.
            /// \return The global bound of the shape.
            inline const sf::FloatRect getIsoPosition() {
                return _shape.getGlobalBounds();
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
            /// \param texture The texture of the tile as shared pointer.
            inline void setTexture(std::shared_ptr<sf::Texture> texture) {
                _texture = texture;
                _shape.setTexture(_texture.get());
            };

            /// \brief Set the texture of the tile.
            /// \param texture The texture of the tile.
            inline void setTexture(const sf::Texture &texture) {
                _texture = std::make_shared<sf::Texture>(texture);
                _shape.setTexture(_texture.get());
            };

            /// \brief Set the texture of the tile.
            /// \param texturePath The path of the texture to be load.
            void setTexture(const std::string &texturePath);

            // \brief Set the textures of the inventory.
            /// \param texturePath The path of the texture to be load.
            // void setTexturesInventory(const std::string &texturePath);

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

            /// \brief Get the path of the texture of the tile.
            /// \return The path of the texture.
            const std::string &getTexturePath() const {
                return _texturePath;
            };

            /// \brief Get the shared pointer of the texture.
            /// \return The shared pointer.
            std::shared_ptr<sf::Texture> getTexture() const {
                return _texture;
            };

            /// \brief Check if the mouse is on the tile.
            /// \param mouse The mouse to check.
            /// \return True if the mouse is on the tile, false otherwise.
            bool isOnTile(sf::Vector2i mouse);

            /// \brief Check if the mouse is on the right of the two vectors.
            /// \param point1 The first vector.
            /// \param point2 The second vector.
            /// \param mouse The mouse position.
            /// \return 1 if on right, 0 otherwise.
            int isOnRight(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2i mouse);

            /// \brief Set the zoom of the map.
            /// \param zoom The zoom value to be set.
            void setZoom(float zoom);

            /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            const std::vector<gui::entity::Player> &getPlayers() const {
                return _players;
            };

            /// \brief add a player object to the vector
            /// \param tileInfo the player object to add
            void addPlayer(gui::entity::Player &player) {
                _players.emplace_back(player);
            }

            /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            const gui::entity::Tile &getTileInfo() const {
                return _tileInfo;
            };

            /// \brief set the tile object with the one given
            /// \param tileInfo the tile object to set
            void setTileInfo(gui::entity::Tile &tileInfo) {
                _tileInfo = tileInfo;
            }

            /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            const std::vector<gui::entity::Egg> &getEggs() const {
                return _eggs;
            };

            /// \brief add a player object to the vector
            /// \param tileInfo the player object to add
            void addEgg(gui::entity::Egg &egg) {
                _eggs.emplace_back(egg);
            }
        private:

            /// \brief Set the points of the tile.
            void _setShape();

            /// \brief Move a point to an isometric view.
            /// \param vector The point to move.
            /// \param angle The angle of the view.
            /// \param zoom The zoom of the view.
            sf::Vector2f _toIsometric(sf::Vector2f vector, sf::Vector2f angle);

            /// \brief Convex shape of the tile.
            sf::ConvexShape _shape;

            /// \brief Position of the tile.
            sf::Vector2f _position;

            /// \brief Texture of the tile.
            std::shared_ptr<sf::Texture> _texture;

            /// \brief Size of the tile.
            sf::Vector2f _size;

            /// \brief Texture path of the tile.
            std::string _texturePath;

            /// \brief The zoom.
            float _zoom;

            /// \brief object Tile
            gui::entity::Tile _tileInfo;

            /// \brief vector of players to be displayed on the tile
            std::vector<gui::entity::Player> _players;

            /// \brief vector of eggs to be displayed on the tile
            std::vector<gui::entity::Egg> _eggs;
    };
} // gui namespace

#endif /* !TILE_HPP_ */
