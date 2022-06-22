/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui_src/Core/Core.hpp

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include "SFML.hpp"
#include "Unpack.hpp"

extern "C" {
    #include "api.h"
}

namespace gui {
    /// \brief The core of the zappy_gui. It's the most important part of the project.
    class Core {
        public:

            /// \brief Constructor of the Core.
            Core();

            /// \brief Destructor of the Core.
            ~Core();

            /// \brief Run the core. It's the main loop of the program.
            void run();

            /// \brief Setup the core with the given parameters.
            void setup(int ac, char **av);
        private:
            /// \brief remove entities depending on the type given
            /// \param type string representating the type of entities to remove
            void _removeEntities(std::string &type);

            /// \brief Check if an entity need to be updated. It also fill the `entityAsString` variable.
            /// \param entityAsString A vector of string which contains the representation of all entity of a type.
            /// \param type The type of the entity as a string (player, egg or tile).
            /// \param response The response of the server to get from the string information of an entity type.
            /// \return true if the entity need to be updated.
            /// \return false if the entity don't need to be updated.
            bool _canEntityUpdate(std::vector<std::string> &entityAsString, std::string &type, std::string &response);

            /// \brief Update the entity corresponding on his type.
            /// \param type The type of the entity as a string (player, egg or tile).
            /// \param response The response of the server to get from the string information of an entity type.
            void _updateEntities(std::string &type, std::string &response);

            /// \brief update entities depending on the response of the server
            /// \param response string representating the packed response of the server
            void _updateEntities(std::string &response);

            /// \brief Update informations about the corresponding entity, depending on the server answer.
            /// \param entity The entity on which put informations to update.
            /// \param type The type of the entity. It's usefull to find the correct information inside the `response` parameter.
            /// \param response Information from the server to update the entity with.
            void _updateEntity(gui::entity::Tile entity, std::string &type, std::string &response);

            /// \brief Update informations about the corresponding entity, depending on the server answer.
            /// \param entity The entity on which put informations to update.
            /// \param type The type of the entity. It's usefull to find the correct information inside the `response` parameter.
            /// \param response Information from the server to update the entity with.
            void _updateEntity(gui::entity::Player entity, std::string &type, std::string &response);

            /// \brief Update informations about the corresponding entity, depending on the server answer.
            /// \param entity The entity on which put informations to update.
            /// \param type The type of the entity. It's usefull to find the correct information inside the `response` parameter.
            /// \param response Information from the server to update the entity with.
            void _updateEntity(gui::entity::Egg entity, std::string &type, std::string &response);

            /// \brief Start the connection with the server.
            /// \throw CoreException if the connection can't be established.
            void _connectToServer();

            /// \brief Wait while the server don't send a response.
            void _waitForServerAnswer();

            /// \brief Resolve the hostname to ip address to connect the client to the server.
            void _resolveMachineHostname();

            /// \brief Get the parameters of the program and set the core with them.
            /// \param ac The number of parameters.
            /// \param av The parameters.
            void _getArgs(int ac, char **av);

            /// \brief Parse all entities comming from the server and add them to the SFML object
            /// \param str the string of packed entities
            void _parseEntities(std::string &str);
            /// \brief Convert a string to a vector.
            /// \param text The string in which find the vector.
            /// \param delim The delimiter.
            /// \return The vector found in the string.
            std::vector<std::string> _stringToVector(std::string text, std::string delim);

            /// \brief The port of the server.
            std::string _port;

            /// \brief The ip of the server. It store temporarly the name of the machine, that is replaced by the IP address.
            std::string _machine;

            /// \brief An instance of the sfml graphical part.
            std::unique_ptr<SFML> _sfml;

            /// \brief Instance of the unpack object
            std::unique_ptr<unpack::Unpack> _unpackObject;

            /// \brief The starting data
            std::unique_ptr<unpack::Start> _startData;
    };
} // namespace gui

#endif /* !CORE_HPP_ */
