/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Event
*/

/// \file src/zappy_gui_src/Core/SFML/WrapperSFML/Event.hpp

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <SFML/Graphics.hpp>

/// \brief The class event handle events from SFML to be use anywhere in the zappy_gui.
/// It will simplify the use of all event from keyboard and mouse button.
class Event {
    public:
        /// \brief Constructor of the Event. Set all variables to false or 0;
        Event() : _keyPressed(false), _buttonPressed(false), _altPressed(false), _ctrlPressed(false), _shiftPressed(false), _key(sf::Keyboard::A), _button(sf::Mouse::Left) {};

        /// \brief Destructor of the Event. Set to default destructor.
        ~Event() = default;

        /// \brief Set the key pressed status to true. Store the key pressed.
        /// \param key The key pressed.
        inline void keyPressed(sf::Keyboard::Key key = sf::Keyboard::A) {
            _key = key;
            _keyPressed = true;
        };

        /// \brief Set the key pressed status to false. Keep the last key pressed in the variable.
        inline void keyReleased() {
            _keyPressed = false;
        };

        /// \brief Set the button pressed status to true. Store the button pressed.
        /// \param button The button pressed.
        inline void buttonPressed(sf::Mouse::Button button = sf::Mouse::Left) {
            _button = button;
            _buttonPressed = true;
        };

        /// \brief Set the button pressed status to false. Keep the last button pressed in the variable.
        inline void buttonReleased() {
            _buttonPressed = false;
        };

        /// \brief Set the alt pressed status to true.
        inline void altPressed() {
            _altPressed = true;
        };

        /// \brief Set the alt pressed status to false.
        inline void altReleased() {
            _altPressed = false;
        };

        /// \brief Set the ctrl pressed status to true.
        inline void ctrlPressed() {
            _ctrlPressed = true;
        };

        /// \brief Set the ctrl pressed status to false.
        inline void ctrlReleased() {
            _ctrlPressed = false;
        };

        /// \brief Set the shift pressed status to true.
        inline void shiftPressed() {
            _shiftPressed = true;
        };

        /// \brief Set the shift pressed status to false.
        inline void shiftReleased() {
            _shiftPressed = false;
        };

        /// \brief Return the key pressed status.
        /// \return True if the key is pressed, false otherwise.
        inline bool isKeyPressed() const {
            return _keyPressed;
        };

        /// \brief Return the key pressed status.
        /// \return True if the key is pressed and correspond to the specify key, false otherwise.
        inline bool isKeyPressed(sf::Keyboard::Key key) const {
            return (_keyPressed && key == _key) ? true : false;
        };

        /// \brief Return the button pressed status.
        /// \return True if the button is pressed, false otherwise.
        inline bool isButtonPressed() const {
            return _buttonPressed;
        }

        /// \brief Return the button pressed status.
        /// \return True if the button is pressed and correspond to the specify button, false otherwise.
        inline bool isButtonPressed(sf::Mouse::Button button) const {
            return (_buttonPressed && button == _button) ? true : false;
        };

        /// \brief Return the alt pressed status.
        /// \return True if the alt is pressed, false otherwise.
        inline bool isAltPressed() const {
            return _altPressed;
        };

        /// \brief Return the ctrl pressed status.
        /// \return True if the ctrl is pressed, false otherwise.
        inline bool isCtrlPressed() const {
            return _ctrlPressed;
        };

        /// \brief Return the shift pressed status.
        /// \return True if the shift is pressed, false otherwise.
        inline bool isShiftPressed() const {
            return _shiftPressed;
        };

        /// \brief Return the key pressed.
        /// \return The key pressed.
        inline sf::Keyboard::Key getKey() const {
            return _key;
        };

        /// \brief Return the button pressed.
        /// \return The button pressed.
        inline sf::Mouse::Button getButton() const {
            return _button;
        };
    private:
        /// \brief The key pressed status.
        bool _keyPressed;

        /// \brief The button pressed status.
        bool _buttonPressed;

        /// \brief The alt pressed status.
        bool _altPressed;

        /// \brief The ctrl pressed status.
        bool _ctrlPressed;

        /// \brief The shift pressed status.
        bool _shiftPressed;

        /// \brief The last key pressed.
        sf::Keyboard::Key _key;

        /// \brief The last button pressed.
        sf::Mouse::Button _button;
};

#endif /* !EVENT_HPP_ */
