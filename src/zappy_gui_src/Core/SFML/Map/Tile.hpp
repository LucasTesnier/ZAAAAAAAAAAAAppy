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

class Tile {
    public:
        enum status_e {
            NONE,
            HOVER,
            SELECTED
        };
        Tile();
        Tile(const Tile &tile);
        ~Tile();
        Tile operator=(const Tile &tile);
        void setConvexShape(const sf::ConvexShape &shape);
        const sf::ConvexShape &getConvexShape() const;
        void setSize(const sf::Vector2f size);
        const sf::Vector2f &getSize() const;
        void setPosition(const sf::Vector2f position);
        const sf::Vector2f &getPosition() const;
        void setOrigin(const sf::Vector2f origin);
        const sf::Vector2f &getOrigin() const;
    private:
        int _onRight(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2i mouse);
        sf::Vector2f _toIsoProjection(sf::Vector2f point, sf::Vector2f angles);
        sf::ConvexShape _shape;
        sf::Vector2f _size;
        status_e _status;
};

#endif /* !TILE_HPP_ */
