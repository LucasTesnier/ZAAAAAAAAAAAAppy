/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SFML
*/

/// \file src/zappy_gui/Core/SFML/SFML.hpp

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include "Map.hpp"

class SFML {
    public:
        /// \brief Constructor of the SFML.
        SFML();
        void display();
        bool isWorking() const;
        /// \brief Destructor of the SFML.
        ~SFML();
    private:
        Map map;
        sf::RenderWindow *_window;
        bool _isWorking;
        sf::Event _event;
};

#endif /* !SFML_HPP_ */
