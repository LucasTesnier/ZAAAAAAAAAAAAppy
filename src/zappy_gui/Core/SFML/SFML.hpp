/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include "Map.hpp"

class SFML {
    public:
        SFML();
        void display();
        bool isWorking() const;
        ~SFML();
    private:
        Map map;
        sf::RenderWindow *_window;
        bool _isWorking;
        sf::Event _event;
};

#endif /* !SFML_HPP_ */
