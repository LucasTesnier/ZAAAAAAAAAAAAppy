/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui/Core/Core.hpp

#ifndef CORE_HPP_
#define CORE_HPP_

#include "SFML.hpp"

/// \brief The core of the zappy_gui. It's the most important part of the project.
class Core {
    public:

        /// \brief Constructor of the Core.
        Core(int ac, char **av);

        /// \brief Run the client. It's the main loop.
        void run();

        /// \brief Destructor of the Core.
        ~Core();
    private:
        SFML _sfml;
};

#endif /* !CORE_HPP_ */