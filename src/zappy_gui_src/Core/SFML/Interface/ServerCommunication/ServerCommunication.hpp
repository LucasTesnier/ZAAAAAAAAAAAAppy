/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ServerCommunication
*/

/// \file src/zappy_gui_src/Core/SFML/Interface/ServerCommunication/ServerCommunication.hpp

#ifndef SERVERCOMMUNICATION_HPP_
#define SERVERCOMMUNICATION_HPP_

#include <memory>
#include <SFML/Graphics.hpp>

namespace gui {
    /// \brief Class which show the communication with the server.
    class ServerCommunication {
        public:
            /// \brief The server communication constructor.
            ServerCommunication();

            /// \brief The server communication constructor, with the shared pointer of the window to be used.
            /// \param window The shared pointer of the SFML window to be used. It will use to display some shape and texts on the screen.
            ServerCommunication(std::shared_ptr<sf::RenderWindow> window);

            /// \brief The server communication destructor. It's set to default.
            ~ServerCommunication() = default;

            /// \brief The setWindow function set the shared pointer of the SFML window to be used. It also initialize shapes and texts depending to the window size.
            /// \param window The shared pointer of the SFML window to be used. It will use to display some shape and texts on the screen.
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
                initializeShapes();
            };

            /// \brief The display function display the shapes and texts on the screen. It can also update some information if needed.
            void display();

            /// \brief The initializeShapes function initialize the shapes and texts depending to the window size. This function is usefull only at the beginning of the program.
            void initializeShapes();

            /// \brief The getPosition function return the position of global shape of the server communication.
            /// \return The position of global shape of the server communication.
            inline const sf::Vector2f &getPosition() const {
                return _body.getPosition();
            };

            /// \brief The getSize function return the size of global shape of the server communication.
            /// \return The size of global shape of the server communication.
            inline const sf::Vector2f &getSize() const {
                return _body.getSize();
            };

            /// \brief The update function update the server communication shape and texts size and position, depending on others menus and it's own status.
            /// If the mouse position is not inside the button, there is no update, except if forceUpdate is true.
            /// \param forceUpdate If true, it update the status even the mouse is not on the button.
            void update(bool forceUpdate = false);

        private:
            /// \brief The _updateBody function is a private function to update the global shape depending of it's status.
            void _updateBody();

            /// \brief It's the shared pointer of the SFML window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief It's the background shape of the server communication. It define the global shape.
            sf::RectangleShape _body;

            /// \brief It's the button to open or close the server communication menu.
            sf::RectangleShape _button;

            /// \brief It's the status of the server communication. It's true if the server communication is open, false otherwise.
            bool _isOpen;

            /// \brief It's the clock to update the server communication action. If there is not enough time spended, it's not update (0.2s).
            sf::Clock _clock;
    };
} // namespace gui

#endif /* !SERVERCOMMUNICATION_HPP_ */
