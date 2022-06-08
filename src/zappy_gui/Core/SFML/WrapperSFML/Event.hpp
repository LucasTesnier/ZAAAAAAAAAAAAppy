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
        /// \brief Constructor of the Event. Set all variables to false or 0;
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
        inline bool isKeyPressed() const {
            return _keyPressed;
        };
        inline bool isKeyPressed(sf::Keyboard::Key key) const {
            return (_keyPressed && key == _key) ? true : false;
        };
        inline bool isButtonPressed() const {
            return _buttonPressed;
        }
        inline bool isButtonPressed(sf::Mouse::Button button) const {
            return (_buttonPressed && button == _button) ? true : false;
        };
        inline bool isAltPressed() const {
            return _altPressed;
        };
        inline bool isCtrlPressed() const {
            return _ctrlPressed;
        };
        inline bool isShiftPressed() const {
            return _shiftPressed;
        };
        inline sf::Keyboard::Key getKey() const {
            return _key;
        };
        inline sf::Mouse::Button getButton() const {
            return _button;
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
