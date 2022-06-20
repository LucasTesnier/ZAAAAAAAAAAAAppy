/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SFML
*/

/// \file src/zappy_gui_src/Core/SFML/SFML.hpp

#ifndef SFML_HPP_
#define SFML_HPP_

#include "Event.hpp"
#include "Map.hpp"
#include "Interface.hpp"
#include "Minimap/Minimap.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace gui {
    /// \brief Class for the SFML. This class is used to display the GUI.
    class SFML {
        public:

            /// \brief Construct a new SFML object
            SFML(const sf::Vector2f mapSize);

            /// \brief Destructor of the SFML.
            ~SFML() = default;

            /// \brief Return if the SFML is running.
            /// \return True if the SFML is running, false otherwise.
            inline bool isRunning() const {
                return _run;
            };

            /// \brief Display the SFML.
            void display();

            /// \brief Change the size of the map
            /// \param mapSize The map size
            void _changeMapSize(const sf::Vector2f mapSize);

        private:

            void _getEvent();
            /// \brief The status of the SFML.
            bool _run;

            /// \brief SFML event manager.
            std::shared_ptr<Event> _event;

            /// \brief SFML window.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief SFML map.
            Map _map;

            /// \brief SFML interface.
            Interface _interface;
    };
} // namespace gui

#endif /* !SFML_HPP_ */
