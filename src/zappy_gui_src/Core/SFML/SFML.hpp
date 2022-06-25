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

            /// \brief add a player object to the map
            /// \param player the player object to add
            inline void addPlayer(gui::entity::Player &player) {
                _map.addPlayer(player);
                _interface.addPlayer(player);
            }

            /// \brief remove a player object from the map
            /// \param player the player object to remove
            inline void removePlayer(gui::entity::Player &player) {
                _map.removePlayer(player);
                _interface.removePlayer(player);
            }

            /// \brief remove an egg object from the map
            /// \param egg the egg object to remove
            inline void removeEgg(gui::entity::Egg &egg) {
                _map.removeEgg(egg);
                _interface.removeEgg(egg);
            }

            /// \brief add a tileInfo object to the map
            /// \param tileInfo the tileInfo object to add
            inline void addTilesInfo(gui::entity::Tile &tileInfo) {
                _map.addTilesInfo(tileInfo);
                _interface.addTilesInfo(tileInfo);
            }

            /// \brief add a egg object to the map
            /// \param egg the egg object to add
            inline void addEgg(gui::entity::Egg &egg){
                _map.addEgg(egg);
                _interface.addEgg(egg);
            }

            /// \brief add a status object to the map
            /// \param status the status object to add
            inline void addStatus(gui::entity::Status &status) {
                _map.addStatus(status);
            }

            /// \brief remove entities depending on the type given
            /// \param type string representating the type of entities to remove
            void removeEntities(std::string &type);

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
