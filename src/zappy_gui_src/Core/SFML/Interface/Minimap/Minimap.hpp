/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Minimap
*/

#ifndef MINIMAP_HPP_
#define MINIMAP_HPP_

#include <vector>
#include <tuple>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

namespace gui {
    class Minimap {
        public:
            Minimap();
            ~Minimap() = default;
            void display();
            inline void addPlayer(const std::string &name, const sf::Vector2f &position) {
                _playerList.push_back(std::tuple(name, position));
            };
            void removePlayer(const std::string &name);
            inline void setMapSize(const sf::Vector2f &size) {
                _mapSize = size;
                _updateConvexShape();
            };
            void switchSize();
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
            };
        private:
            void _updateConvexShape();
            sf::Vector2f _toIsometric(sf::Vector2f vector, sf::Vector2f angle);
            std::shared_ptr<sf::RenderWindow> _window;
            std::vector<std::tuple<std::string, sf::Vector2f>> _playerList;
            sf::RectangleShape _minimap;
            sf::ConvexShape _map;
            sf::CircleShape _player;
            sf::Vector2f _mapSize;
            sf::Vector2f _minimapSize;
    };
}

#endif /* !MINIMAP_HPP_ */
