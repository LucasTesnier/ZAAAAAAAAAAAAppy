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
        class Event {
            public:
                Event();
                void keyPressed(sf::Keyboard::Key key);
                void keyReleased();
                void mousePressed(sf::Mouse::Button button);
                void mouseReleased();
                void wheelScroll(float delta);
                void altPressed();
                void altReleased();
                void ctrlPressed();
                void ctrlReleased();
                void shiftPressed();
                void shiftReleased();
                inline sf::Keyboard::Key getKeyPressed(void) const {
                    return _key;
                };
                inline sf::Mouse::Button getButtonPressed(void) const {
                    return _button;
                };
                inline bool isKeyPressed() const {
                    return _keyPressed;
                };
                inline bool isKeyPressed(sf::Keyboard::Key key) const {
                    if (key == _key)
                        return _keyPressed;
                    return false;
                };
                inline bool isButtonPressed() const {
                    return _mousePressed;
                };
                inline bool isButtonPressed(sf::Mouse::Button button) const {
                    if (_button == button)
                        return _mousePressed;
                    return false;
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
                ~Event() = default;
            private:
                bool _keyPressed;
                bool _mousePressed;
                bool _altPressed;
                bool _ctrlPressed;
                bool _shiftPressed;
                bool _wheelScrolled;
                sf::Keyboard::Key _key;
                sf::Mouse::Button _button;
                float _delta;
        };
    private:
        Event _event;
        void _eventHandling();
        Map map;
        sf::RenderWindow *_window;
        bool _isWorking;
};

#endif /* !SFML_HPP_ */
