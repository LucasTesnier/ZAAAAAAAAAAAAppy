/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui/Core/Core.hpp

#ifndef CORE_HPP_
#define CORE_HPP_

#include <exception>
#include <string>

/// \brief The core of the zappy_gui. It's the most important part of the project.
class Core {
    public:
        class CoreException : std::exception {
            public:
                CoreException(std::string title __attribute__((unused)), std::string description __attribute__((unused))) {};
                const char *what() const noexcept override {};
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
};

#endif /* !CORE_HPP_ */
