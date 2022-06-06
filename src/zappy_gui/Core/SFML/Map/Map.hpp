/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui/Core/SFML/Map/Map.hpp

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include "SFML/Graphics.hpp"

class Map {
    public:
        Map();
        ~Map();
        /// \warning Be carefull, this function will remove tiles if the total
        /// size is less than the previous
        void setSize(int x, int y);
        /// \warning Be carefull, this function will remove tiles if the total
        /// size is less than the previous
        void setSize(sf::Vector2f size);
        void setWindow(sf::RenderWindow *window);
        void draw();
    private:
        void _updateTilesVectorSize();
        sf::Vector2f _indexToPosition(std::size_t index);
        sf::Vector2f _toIsoProjection(sf::Vector2f point, sf::Vector2f angles);
        sf::RenderWindow *_window;
        std::vector<sf::ConvexShape> _tiles;
        sf::Vector2f _mapSize;
};

#endif /* !MAP_HPP_ */
