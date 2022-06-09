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
        class CoreException : std::exception {
            public:
                CoreException(std::string title = "", std::string description = "");
                const char *what() const noexcept override;
            private:
                std::string _title;
                std::string _description;
                std::string _what;
        };
        /// \brief Constructor of the Core.
        Core() = default;
        /// \brief Destructor of the Core.
        ~Core() = default;
        void run();
        void setup(int ac, char **av);
    private:
        void _getArgs(int ac, char **av);
        std::string _port;
        std::string _machine;
        SFML _sfml;
};

#endif /* !CORE_HPP_ */
