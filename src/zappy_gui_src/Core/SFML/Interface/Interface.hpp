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
#include "ServerCommunication.hpp"
#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

/// \brief The color for backgrounds menus.
#define BACKGROUND_COLOR sf::Color(150, 170, 183)

/// \brief The color for buttons.
#define BUTTON_COLOR sf::Color(43, 89, 72)

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
                _server.setWindow(_window);
            };

            /// \brief Set the map size.
            /// \param mapSize The map size.
            inline void setMapSize(const sf::Vector2f &mapSize) {
                _mapSize = mapSize;
                _minimap.setMapSize(_mapSize);
            };

            /// \brief call the inventory object and set the position
            /// \param pos the position to set
            inline void setInventoryTilePos(const sf::Vector2f &pos) {
                _inventory.setTilePosition(pos);
            }

            /// \brief call the inventory object and set inventory
            /// \param pos the inventory to set
            inline void setInventoryTileInv(const std::vector<int> &inv) {
                _inventory.setTileInventory(inv);
            }

            /// \brief call the inventory object and set inventory
            /// \param pos the inventory to set
            inline void setInventoryPlayers(const std::vector<gui::entity::Player> &p) {
                _inventory.setPlayers(p);
            }

            /// \brief call the inventory object and set inventory
            /// \param pos the inventory to set
            inline void setInventoryEggs(const std::vector<gui::entity::Egg> &e) {
                _inventory.setEggs(e);
            }

        private:
            /// \brief The window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief The event to be used and update by the SFML part.
            std::shared_ptr<Event> _event;

            /// \brief An instance of the minimap.
            Minimap _minimap;

            /// \brief An instance of the inventory.
            Inventory _inventory;

            /// \brief An instance of the server communication.
            ServerCommunication _server;

            /// \brief The map size.
            sf::Vector2f _mapSize;
    };
} // namespace gui

#endif /* !INTERFACE_HPP_ */
