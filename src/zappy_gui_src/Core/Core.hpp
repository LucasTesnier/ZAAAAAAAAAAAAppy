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
