/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Minimap
*/

/// \file src/zappy_gui_src/Core/SFML/Interface/Minimap.hpp

#ifndef MINIMAP_HPP_
#define MINIMAP_HPP_

#include <vector>
#include <tuple>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

namespace gui {
    /// \brief A class for the minimap.
    class Minimap {
        public:
            /// \brief Constructor of the Minimap.
            Minimap();

            /// \brief Destructor of the Minimap.
            ~Minimap() = default;

            /// \brief Display the minimap.
            void display();

            /// \brief Add a player from the minimap.
            /// \param name The name of the player.
            /// \param position The position of the player.
            void addPlayer(const std::string &name, const sf::Vector2f &position);

            /// \brief Remove a player from the minimap.
            /// \param name The name of the player.
            void removePlayer(const std::string &name);

            /// \brief Set the map size.
            /// \param mapSize The map size.
            inline void setMapSize(const sf::Vector2f &size) {
                _mapSize = size;
                _updateConvexShape();
            };

            /// \brief Switch the minimap size.
            /// \param state True to switch the size, false to be able to switch another time.
            void switchSize(bool state);

            /// \brief Set the window.
            /// \param window The window to be set.
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
                _bottomMenuPosition = sf::Vector2f(_window->getSize());
            };

            inline void setBottomMenuPosition(const sf::Vector2f &position) {
                _bottomMenuPosition = position;
                _updateConvexShape();
            };
        private:
            /// \brief Update the size and position of the minimap.
            void _updateConvexShape();

            /// \brief Converts a vector to his isometric equivalent.
            /// \param vector The vector to convert.
            /// \param angle The angle of the map.
            /// \return The isometric equivalent of the vector.
            sf::Vector2f _toIsometric(sf::Vector2f vector, sf::Vector2f angle);

            /// \brief The window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief A vector of players.
            std::vector<std::tuple<std::string, sf::Vector2f>> _playerList;

            /// \brief The background of the minimap.
            sf::RectangleShape _minimap;

            /// \brief The map in the minimap.
            sf::ConvexShape _map;

            /// \brief The shape to display players
            sf::CircleShape _player;

            /// \brief The map size.
            sf::Vector2f _mapSize;

            /// \brief The minimap size.
            sf::Vector2f _minimapSize;

            /// \brief The state of the switch function.
            bool isSwitch;

            /// \brief position of the inventory menu
            sf::Vector2f _bottomMenuPosition;
            std::vector<sf::Color> _teamsColors;
            std::vector<std::string> _teamsNames;
    };
} // namepsace gui

#endif /* !MINIMAP_HPP_ */
