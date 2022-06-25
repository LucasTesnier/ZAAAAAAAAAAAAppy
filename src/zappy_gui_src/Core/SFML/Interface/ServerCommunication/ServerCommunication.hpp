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
#include "Entity.hpp"

/// \brief The path of the font to be used.
#define FONT_PATH "assets/arial.ttf"

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

            /// \brief The setBackgroundColor function set the background color of the server communication menu.
            /// \param color The color to be set.
            inline void setBackgroundColor(const sf::Color &color) {
                _body.setFillColor(color);
            };

            /// \brief The setButtonColor function set the button color of the server communication menu.
            /// \param color The color to be set.
            inline void setButtonColor(const sf::Color &color) {
                _button.setFillColor(color);
            };

            /// \brief Add a player at the end of a vector of players. It updates also the text on the left menu.
            /// \param player The player to be added.
            inline void addPlayer(gui::entity::Player &player) {
                _players.push_back(player);
                _updateText();
            };

            /// \brief Add a tile at the end of a vector of tiles. It updates also the text on the left menu.
            /// \param tile The tile to be added.
            inline void addTilesInfo(gui::entity::Tile &tile) {
                _tiles.push_back(tile);
                _updateText();
            };

            /// \brief Add an egg at the end of a vector of eggs. It updates also the text on the left menu.
            /// \param egg The egg to be added.
            inline void addEgg(gui::entity::Egg &egg) {
                _eggs.push_back(egg);
                _updateText();
            };

            /// \brief Remove all entities depending on the type.
            /// \note Type value available are: `player`, `egg`, `tile`.
            /// \param type The type of the entity.
            void removeEntities(std::string &type);

            /// \brief Use the scroll value to move the text up and down on the menu.
            /// \param scrollValue Positive value to move down the text, negatif value to move up the text, and null value do nothing.
            void scroll(const float &scrollValue);
        private:

            /// \brief It converts an inventory's vector to a string.
            /// \param inventory The inventory to be converted.
            /// \return The new string which represents the inventory.
            std::string _inventoryToString(const std::vector<int> &inventory);

            /// \brief It updates the text on the left menu depending on informations in players, eggs, and tiles vectors.
            void _updateText();

            /// \brief The _updateBody function is a private function to update the global shape depending of it's status.
            void _updateBody();

            /// \brief It's the shared pointer of the SFML window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief It's the background shape of the server communication. It define the global shape.
            sf::RectangleShape _body;

            /// \brief It's the button to open or close the server communication menu.
            sf::ConvexShape _button;

            /// \brief It's the status of the server communication. It's true if the server communication is open, false otherwise.
            bool _isOpen;

            /// \brief It's the clock to update the server communication action. If there is not enough time spended, it's not update (0.2s).
            sf::Clock _clock;

            /// \brief It's the text to display on the server communication menu.
            sf::Text _text;

            /// \brief It's the font used for the text.
            sf::Font _font;

            /// \brief String which represent the information that will be displayed on the left menu.
            std::string _serverInformation;

            /// \brief A vector which contains all players that are updated by the server.
            std::vector<entity::Player> _players;

            /// \brief A vector which contains all tiles that are updated by the server.
            std::vector<entity::Tile> _tiles;

            /// \brief A vector which contains all eggs that are updated by the server.
            std::vector<entity::Egg> _eggs;
    };
} // namespace gui

#endif /* !SERVERCOMMUNICATION_HPP_ */
