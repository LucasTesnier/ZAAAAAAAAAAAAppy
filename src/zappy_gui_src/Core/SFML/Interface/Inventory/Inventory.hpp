/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Inventory
*/

/// \file src/zappy_gui_src/Core/SFML/Interface/Inventory/Inventory.hpp

#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include "Entity.hpp"

#define FONT_PATH "assets/arial.ttf"

namespace gui {
    class Inventory {
        public:
            /// \brief constructor of the object
            Inventory();
            /// \brief constructor of the object containing the window
            /// \param window the window to set
            Inventory(std::shared_ptr<sf::RenderWindow> window);
            /// \brief default destructor
            ~Inventory() = default;
            /// \brief set the window and init all shapes, sprites and texts
            /// \param window the window to set
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
                initShapes();
                initTextTilePosition();
                initTextTileInventory();
                initTextPlayer();
                initTextEgg();
            };
            /// \brief the main display function with all the displayable objects drawn in the window
            void display();
            /// \brief initialize all the text relative to display the tile position
            void initTextTilePosition();
            /// \brief initialize all the text relative to display the tile inventory
            void initTextTileInventory();
            /// \brief initialize all the text relative to display the players
            void initTextPlayer();
            /// \brief initialize all the text relative to display the eggs
            void initTextEgg();
            /// \brief initialize all the text relative to display the entities
            std::vector<sf::Text> initTextEntities(std::string string);
            /// \brief set all the positions of the texts of the inventory
            void setPosTextsInv();
            /// \brief set all the positions of the sprites of the inventory
            void setPosSpritesInv();
            /// \brief set all the positions of the texts of the players
            void setPosTextsPlayer(int x, int y, int offset);
            /// \brief set all the positions of the texts of the eggs
            void setPosTextsEgg(int x, int y, int offset);
            /// \brief initialize all the shapes of the class
            void initShapes();
            /// \brief get the position of the body
            /// \return a Vector2f containing the position x and y of the body
            inline const sf::Vector2f &getPosition() const {
                return _body.getPosition();
            };
            /// \brief update the body from the clicks of the mouse on the button
            /// \param forceUpdate false by default, forcing the resize of the body
            void update(bool forceUpdate = false);
            /// \brief set the FloatRect area of the server with a position and a size
            /// \param position the position of the area
            /// \param size the size of the area
            inline void setAreaServer(const sf::Vector2f &position, const sf::Vector2f &size) {
                sf::FloatRect temp;
                temp.left = position.x;
                temp.top = position.y;
                temp.width = size.x;
                temp.height = size.y;
                _areaServer = temp;
                _updateBody();
            };
            /// \brief set the color of the background of the body
            /// \param color the color to set
            inline void setBackgroundColor(const sf::Color &color) {
                _body.setFillColor(color);
            };
            /// \brief set the color of the button
            /// \param color the color to set
            inline void setButtonColor(const sf::Color &color) {
                _button.setFillColor(color);
            };
            /// \brief set position of the tile selected
            /// \param tile the vector2f containing the position x and y
            inline void setTilePosition(const sf::Vector2f &tilePosition) {
                _tilePosition = tilePosition;
            }
            /// \brief set inventory of the tile selected
            /// \param tile the vector containing the values of each item of the inventory
            inline void setTileInventory(const std::vector<int> &tileInventory) {
                _tileInventory = tileInventory;
            }
            /// \brief add a player which is on the tile selected
            /// \param player the player to add
            inline void setPlayers(const std::vector<gui::entity::Player> &players) {
                _players = players;
            }
            /// \brief add a player which is on the tile selected
            /// \param player the player to add
            inline void setEggs(const std::vector<gui::entity::Egg> &eggs) {
                _eggs = eggs;
            }
            /// \brief It updates the index of the player's vector and the egg's vector.
            /// \param scroll The value of the mouseWheel's scroll.
            void scroll(const float &scroll);
        private:
            /// \brief resize the body and all the shapes on it
            void _updateBody();
            /// \brief detect if the button is clicked
            /// \return true if clicked, false either
            /// \param mouse the position of the mouse
            bool _isButtonClicked(sf::Vector2i mouse);
            /// \brief the SFML window from the Core
            std::shared_ptr<sf::RenderWindow> _window;
            /// \brief the rectangle containing all the shapes
            sf::RectangleShape _body;
            /// \brief the bool relative to the extension of the body or not
            bool _isOpen;
            /// \brief the shape of the button
            sf::ConvexShape _button;
            /// \brief the clock restarting each time the button or the key is clicked
            sf::Clock _clock;
            /// \brief the area of the body
            sf::FloatRect _areaServer;
            /// \brief the title of the body
            sf::Text _title;
            /// \brief the x and y text
            sf::Text _textPos;
            /// \brief the font of the texts
            sf::Font _font;
            /// \brief the vector of text containing the value of each items of the inventory
            std::vector<sf::Text> _textsInv;
            /// \brief the vector of text containing the informations of each players
            std::vector<sf::Text> _textsPlayer;
            /// \brief the vector of text containing the informations of each eggs
            std::vector<sf::Text> _textsEgg;
            /// \brief the vector of sprites of the representations of the inventory
            std::vector<sf::Sprite> _spritesInv;
            /// \brief the selected tile position
            sf::Vector2f _tilePosition;
            /// \brief the selected tile inventory
            std::vector<int> _tileInventory;
            /// \brief the players on the selected tile
            std::vector<gui::entity::Player> _players;
            /// \brief the eggs on the selected tile
            std::vector<gui::entity::Egg> _eggs;
            /// \brief The index where the player's vector need to start.
            std::size_t _startPlayerText;
            /// \brief The index where the egg's vector need to start.
            std::size_t _startEggText;
    };
}

#endif /* !INVENTORY_HPP_ */
