/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui_src/Core/Core.hpp

#ifndef CORE_HPP_
#define CORE_HPP_

#include <exception>
#include <string>
#include "SFML.hpp"

/// \brief The core of the zappy_gui. It's the most important part of the project.
class Core {
    public:
        /// \brief Exception for the Core.
        class CoreException : std::exception {
            public:

                /// \brief Constructor of the CoreException.
                /// \param title The title of the exception.
                /// \param description The description of the exception.
                CoreException(std::string title = "", std::string description = "");

                /// \brief Destructor of the CoreException.
                /// \return The exception.
                const char *what() const noexcept override;
            private:

                /// \brief The title of the exception.
                std::string _title;

                /// \brief The description of the exception.
                std::string _description;

                /// \brief The message of the exception.
                std::string _what;
        };

        /// \brief Constructor of the Core.
        Core() = default;

        /// \brief Destructor of the Core.
        ~Core() = default;

        /// \brief Run the core. It's the main loop of the program.
        void run();

        /// \brief Setup the core with the given parameters.
        void setup(int ac, char **av);
    private:

        /// \brief Get the parameters of the program and set the core with them.
        /// \param ac The number of parameters.
        /// \param av The parameters.
        void _getArgs(int ac, char **av);

        /// \brief The port of the server.
        std::string _port;

        /// \brief The ip of the server.
        std::string _machine;

        /// \brief An instance of the sfml graphical part.
        SFML _sfml;
};

#endif /* !CORE_HPP_ */
