/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Event
*/

/// \file src/zappy_gui/Core/SFML/WrapperSFML/Event.hpp

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <SFML/Graphics.hpp>

/// \brief The class event handle events from SFML to be use anywhere in the zappy_gui.
/// It will simplify the use of all event from keyboard and mouse button.
class Event {
    public:
        Event() : _keyPressed(false), _buttonPressed(false), _altPressed(false), _ctrlPressed(false), _shiftPressed(false), _key(sf::Keyboard::A), _button(sf::Mouse::Left) {};
        inline void keyPressed(sf::Keyboard::Key key = sf::Keyboard::A) {
            _key = key;
            _keyPressed = true;
        };
        inline void keyReleased() {
            _keyPressed = false;
        };
        inline void buttonPressed(sf::Mouse::Button button = sf::Mouse::Left) {
            _button = button;
            _buttonPressed = true;
        };
        inline void buttonReleased() {
            _buttonPressed = false;
        };
        inline void altPressed() {
            _altPressed = true;
        };
        inline void altReleased() {
            _altPressed = false;
        };
        inline void ctrlPressed() {
            _ctrlPressed = true;
        };
        inline void ctrlReleased() {
            _ctrlPressed = false;
        };
        inline void shiftPressed() {
            _shiftPressed = true;
        };
        inline void shiftReleased() {
            _shiftPressed = false;
        };
        ~Event() = default;
    private:
        bool _keyPressed;
        bool _buttonPressed;
        bool _altPressed;
        bool _ctrlPressed;
        bool _shiftPressed;
        sf::Keyboard::Key _key;
        sf::Mouse::Button _button;
};

#endif /* !EVENT_HPP_ */
