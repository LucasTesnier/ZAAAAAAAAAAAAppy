/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Interface
*/

/// \file src/zappy_gui_src/Core/Interface/Interface.hpp

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include "Minimap.hpp"
#include "Inventory.hpp"
#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace gui {
    class Interface {
        public:
            /// \brief Constructor of the Interface.
            Interface();

            /// \brief Destructor of the Interface.
            ~Interface() = default;

            /// \brief Update and display interface.
            void updateAndDisplay();

            /// \brief Set the shared pointer for the event.
            /// \param event The event to be set.
            inline void setEvent(std::shared_ptr<Event> event) {
                _event = event;
            };

            /// \brief Set the shared pointer for the window.
            /// \param window The window to be set.
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
                _inventory.setWindow(_window);
                _minimap.setWindow(_window);
            };

            /// \brief Set the map size.
            /// \param mapSize The map size.
            inline void setMapSize(const sf::Vector2f &mapSize) {
                _mapSize = mapSize;
                _minimap.setMapSize(_mapSize);
            };
        private:
            /// \brief The window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief The event to be used and update by the SFML part.
            std::shared_ptr<Event> _event;

            /// \brief An instance of the minimap
            Minimap _minimap;

            Inventory _inventory;

            /// \brief The map size.
            sf::Vector2f _mapSize;
    };
} // namespace gui

#endif /* !INTERFACE_HPP_ */
