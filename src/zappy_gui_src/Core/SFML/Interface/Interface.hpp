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

            /// \brief Add the player passed as parameter to the server menu.
            /// \param player The player to be added.
            inline void addPlayer(gui::entity::Player &player) {
                _server.addPlayer(player);
                _minimap.addPlayer(player._uuid, sf::Vector2f(player._position.first, player._position.second));
            };

            /// \brief Remove the player passed as parameter from the server menu.
            /// \param player The player to be removed.
            inline void removePlayer(gui::entity::Player &player) {
                _server.removePlayer(player);
            };

            /// \brief Remove the egg passed as parameter from the server menu.
            /// \param egg The egg to be removed.
            inline void removeEgg(gui::entity::Egg &egg) {
                _server.removeEgg(egg);
            };

            /// \brief Add the tile passed as parameter to the server menu.
            /// \param tile The tile to be added.
            inline void addTilesInfo(gui::entity::Tile &tile) {
                _server.addTilesInfo(tile);
            };

            /// \brief Add the egg passed as parameter to the server menu.
            /// \param egg The egg to be added.
            inline void addEgg(gui::entity::Egg &egg) {
                _server.addEgg(egg);
            };

            /// \brief Remove all entities depending on the type.
            /// \note Type value available are: `player`, `egg`, `tile`.
            /// \param type The type of the entity
            inline void removeEntities(std::string &type) {
                _server.removeEntities(type);
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

            /// \brief call the inventory object and set players
            /// \param p the player to set
            inline void setInventoryPlayers(const std::vector<gui::entity::Player> &p) {
                _inventory.setPlayers(p);
            }

            /// \brief call the inventory object and set eggs
            /// \param e the eggs to set
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
