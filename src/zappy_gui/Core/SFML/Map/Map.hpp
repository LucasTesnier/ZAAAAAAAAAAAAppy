/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui/Core/SFML/Map/Map.hpp

#ifndef MAP_HPP_
#define MAP_HPP_

#include "SFML/Graphics.hpp"

class Map {
    public:
        Map();
        ~Map();
        void setWindow(sf::RenderWindow *window);
        void draw();
        // sf::Vector2f isoProjection(int x, int y, int z, sf::Vector2f angles);
    private:
        sf::RenderWindow *_window;
        sf::Vector2f _toIsoProjection(sf::Vector2f point, sf::Vector2f angles);
        sf::ConvexShape _shape;
};

#endif /* !MAP_HPP_ */
