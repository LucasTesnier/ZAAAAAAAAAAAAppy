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
        private:

            /// \brief Update the position of the map depending on events.
            /// \param moveMap The vector use to move the map.
            void _updateMoveMap(sf::Vector2f &moveMap);

            /// \brief Update the size of the vector.
            void _updateTileVectorSize();

            /// \brief The window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief The event class.
            std::shared_ptr<Event> _event;

            /// \brief The tile's vector in the map.
            std::vector<std::unique_ptr<Tile>> _tile;

            /// \brief The selected tile.
            std::size_t _tileSelected;

            /// \brief The hovered tile.
            std::size_t _tileHover;

            /// \brief The vector size of the map.
            sf::Vector2f _mapSize;

            /// \brief Zoom to be applied.
            float _zoom;
    };
} // namespace gui

#endif /* !MAP_HPP_ */
