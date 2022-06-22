/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui_src/Core/SFML/Map/Map.hpp

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Tile.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Event.hpp"
#include "Entity.hpp"
#include <iostream>

namespace gui {
    /// \brief Class for the map of the zappy. It contain all informations that will be display.
    class Map {
        public:

            /// \brief Constructor of the Map.
            Map();

            /// \brief Destructor of the Map.
            ~Map();

            /// \brief Set the render window to display on.
            /// \param window The window to be set.
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
            };

            /// \brief Set the event class to be used.
            /// \param event The event to be set.
            inline void setEvent(std::shared_ptr<Event> event) {
                _event = event;
            };

            /// \brief Set the size of the map.
            /// \param mapSize The size of the map.
            inline void setMapSize(sf::Vector2f mapSize) {
                _mapSize = mapSize;
                _updateTileVectorSize();
            };

            /// \brief Display the map on the window. Update all information of the map if necessary.
            void display();

             /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            inline const std::vector<gui::entity::Player> &getPlayers() const {
                return _players;
            };

            /// \brief add a player object to the vector
            /// \param player the player object to add
            inline void addPlayer(gui::entity::Player &player) {
                _players.emplace_back(player);
                _tile[itop(sf::Vector2f(player.getPosition().first, player.getPosition().second))]->addPlayer(player);
            }

            /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            inline const std::vector<gui::entity::Tile> &getTilesInfo() const {
                return _tilesInfo;
            };

            /// \brief add a tile object to the vector
            /// \param tileInfo the tile object to set
            inline void addTilesInfo(gui::entity::Tile &tileInfo) {
                _tilesInfo.emplace_back(tileInfo);
                _tile[itop(sf::Vector2f(tileInfo.getPosition().first, tileInfo.getPosition().second))]->setTileInfo(tileInfo);
            }

            /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            inline const std::vector<gui::entity::Egg> &getEggs() const {
                return _eggs;
            };

            /// \brief add a player object to the vector
            /// \param tileInfo the player object to add
            inline void addEgg(gui::entity::Egg &egg) {
                _eggs.emplace_back(egg);
                _tile[itop(sf::Vector2f(egg.getPosition().first, egg.getPosition().second))]->addEgg(egg);
            }

            /// \brief remove entities depending on the type given
            /// \param type string representating the type of entities to remove
            void removeEntities(std::string &type);

            /// \brief get the posititon of the selected tile
            /// \return the position of the tile selected by the user
            inline const sf::Vector2f &getSelectedTilePos() const {
                if (int(_tileSelected) == -1)
                    return _noTileSelected;
                return _tile[_tileSelected].get()->getPosition();
            };

            /// \brief get the actual selected tile
            /// \return the tile selected by the user
            inline const std::vector<int> &getSelectedTileInventory() const {
                if (int(_tileSelected) == -1)
                    return _noTileSelectedInv;
                return _tile[_tileSelected].get()->getTileInfo().getInventory();
            };
        private:

            /// \brief Display the actual selected and hover tile if it's different to index -1.
            void _displaySelectedAndHoverTiles(sf::CircleShape &entityRepresentation);

            /// \brief Find if the selected or hover tile must be update.
            /// \param i The actual index of the tile to find if it need to be update.
            /// \param mouse The mouse cursor position on the window.
            void _findSelectedAndHoverTiles(std::size_t &i, const sf::Vector2i &mouse);

            /// \brief Update the position of the map depending on events.
            void _updateMoveMap();

            /// \brief Transform a vector position to an index.
            /// \param pos The position to be transform.
            /// \return The corresponding index of the pos.
            inline std::size_t itop(sf::Vector2f pos) {
                return pos.y * _mapSize.x + pos.x;
            };

            /// \brief Transfom an index to a position.
            /// \param index The index to be transfom.
            /// \return The corresponding pos of the index.
            inline sf::Vector2f ptoi(std::size_t index) {
                return sf::Vector2f(index % int(_mapSize.y), index / _mapSize.y);
            };

            void _pushEntityInTile();
            /// \brief Find if the tile should be displayed on the screen.
            /// \param area The global bound of the tile.
            /// \param windowSize The size of the window.
            /// \param tmp A value use to keep a previous value.
            /// \param mapSize The size of the map.
            /// \param i The index in the tile vector.
            /// \return true if it should be displayed, false otherwise.
            bool _tileMustBeDisplayed(const sf::FloatRect &area, const sf::Vector2u windowSize, std::size_t &tmp, sf::Vector2f &mapSize, std::size_t &i);

            /// \brief Update the size of the vector.
            void _updateTileVectorSize();

            /// \brief Display players that are in the tile, if there is at least one player.
            void _displayPlayers(Tile &tile, sf::CircleShape &playerRepresentation);
            void _displayResources(Tile &tile, sf::CircleShape &resourcesRpresentation);
            void _displayEggs(Tile &tile, sf::CircleShape &eggRpresentation);

            /// \brief The window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief The event class.
            std::shared_ptr<Event> _event;

            /// \brief The tile's vector in the map.
            std::vector<std::unique_ptr<Tile>> _tile;

            /// \brief The selected tile.
            std::size_t _tileSelected;

            /// \brief the default pos of no tile selected
            sf::Vector2f _noTileSelected;

            /// \brief the default vector of no tile selected
            std::vector<int> _noTileSelectedInv;

            /// \brief The hovered tile.
            std::size_t _tileHover;

            /// \brief The vector size of the map.
            sf::Vector2f _mapSize;

            /// \brief Zoom to be applied.
            float _zoom;

            /// \brief vector of tiles info
            std::vector<gui::entity::Tile> _tilesInfo;

            /// \brief vector of players to be displayed on the tile
            std::vector<gui::entity::Player> _players;

            /// \brief vector of eggs to be displayed on the tile
            std::vector<gui::entity::Egg> _eggs;
    };
} // namespace gui

#endif /* !MAP_HPP_ */
