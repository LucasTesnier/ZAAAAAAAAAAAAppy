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
        /// \brief Constructor of the Map.
        Map();
        /// \brief Destructor of the Map.
        ~Map();
        /// \warning Be carefull, this function will remove tiles if the total
        /// size is less than the previous
        void setSize(int x, int y);
        /// \warning Be carefull, this function will remove tiles if the total
        /// size is less than the previous
        void setSize(sf::Vector2f size);
        sf::Vector2f getSize() const;
        void setWindow(sf::RenderWindow *window);
        void draw();
        void move(sf::Keyboard::Key key);
    private:
        class Tile {
            public:
                Tile(const sf::Vector2f &position = {0, 0}, const sf::Vector2f &size = {0, 0});
                Tile(const Tile &tile);
                Tile operator=(const Tile &tile);
                const sf::ConvexShape &getConvexShape() const;
                void setConvexShape(const sf::ConvexShape &shape);
                const sf::Vector2f &getSize() const;
                void setSize(const sf::Vector2f &size);
                const sf::Vector2f &getPosition() const;
                void setPosition(const sf::Vector2f &position);
                const sf::Vector2f &getOrigin() const;
                void setOrigin(const sf::Vector2f &origin);
                ~Tile() = default;
            private:
                sf::Vector2f _toIsoProjection(sf::Vector2f point, sf::Vector2f angles);
                sf::ConvexShape _shape;
                sf::Vector2f _size;
        };
        void _drawRotation0();
        void _updateTilesPosition();
        void _updateTilesVectorSize();
        sf::Vector2f _indexToPosition(std::size_t index);
        std::size_t _positionToIndex(sf::Vector2f position);
        sf::RenderWindow *_window;
        std::vector<Map::Tile> _tiles;
        sf::Vector2f _mapSize;
        sf::Vector2f _tileSize;
        sf::Vector2f _tileOrigin;
        std::size_t _rotation;
};

#endif /* !MAP_HPP_ */
