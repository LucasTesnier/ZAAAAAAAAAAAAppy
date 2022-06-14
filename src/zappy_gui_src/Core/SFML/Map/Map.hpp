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
    class Map {
        public:

            /// \brief Constructor of the Map.
            Map();

            /// \brief Destructor of the Map.
            ~Map();
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
            };
            inline void setEvent(std::shared_ptr<Event> event) {
                _event = event;
            };
            inline void setMapSize(sf::Vector2f mapSize) {
                _mapSize = mapSize;
                _updateTileVectorSize();
            };
            void display();
        private:
            void _updateMoveMap(sf::Vector2f &moveMap);
            void _updateTileVectorSize();
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<Event> _event;
            std::vector<std::unique_ptr<Tile>> _tile;
            std::size_t _tileSelected;
            std::size_t _tileHover;
            sf::Vector2f _mapSize;
            float _zoom;
    };
} // namespace gui

#endif /* !MAP_HPP_ */
